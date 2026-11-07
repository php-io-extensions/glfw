<?php

declare(strict_types=1);

if (! extension_loaded('glfw')) {
    throw new RuntimeException('The glfw extension is not loaded; run ./install-macos.sh or ./install-debian-trixie.sh');
}

/**
 * The loader's vkGetInstanceProcAddr address, 0 when ext-vulkan or FFI is missing. GLFW searches the
 * dynamic linker's path for the loader, which Homebrew's is not on: the address is how it finds it.
 */
function vulkanLoader(): int
{
    if (! function_exists('vk_loader_path') || ! extension_loaded('ffi') || vk_loader_path() === null) {
        return 0;
    }
    $ffi = FFI::cdef('void *vkGetInstanceProcAddr(void *instance, const char *name);', vk_loader_path());

    return $ffi->cast('uintptr_t', $ffi->vkGetInstanceProcAddr)->cdata;
}

/** macOS and Linux signal numbers a kept refusal's probe dies by. */
const PROBE_SIGBUS = PHP_OS_FAMILY === 'Darwin' ? 10 : 7;
const PROBE_SIGSEGV = 11;

/** Skips a tests/Probes test unless the loaded ext-glfw is a probe build (--enable-glfw-probes). */
function requireProbeBuild(): void
{
    if (! defined('GLFW_PROBES')) {
        test()->markTestSkipped('ext-glfw is not a probe build (configure --enable-glfw-probes): GLFW_PROBES is undefined');
    }
}

/**
 * Runs $code in a child of this PHP with only ext-glfw loaded, GLFW initialised and windows hidden.
 * $siteOff names the kept site GLFW_PROBE_OFF turns off, null keeps every site. $gmalloc runs the
 * child under libgmalloc (macOS) with Zend's allocator off, so an over-read faults at the guard page.
 *
 * @return array{signal: ?int, stdout: string}
 */
function glfwProbe(string $code, ?string $siteOff, bool $gmalloc = false): array
{
    $script = "<?php\ndeclare(strict_types=1);\nglfwInit();\nglfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);\ntry {\n".$code."\n} catch (Throwable \$t) {\n    echo 'REFUSED ', get_class(\$t), ': ', \$t->getMessage(), \"\\n\";\n}\necho \"SURVIVED\\n\";\n";
    $file = tempnam(sys_get_temp_dir(), 'glfw-probe');
    file_put_contents($file, $script);

    $env = getenv();
    unset($env['GLFW_PROBE_OFF'], $env['DYLD_INSERT_LIBRARIES'], $env['USE_ZEND_ALLOC']);
    $env['XDEBUG_MODE'] = 'off';
    if ($siteOff !== null) {
        $env['GLFW_PROBE_OFF'] = $siteOff;
    }
    if ($gmalloc && PHP_OS_FAMILY === 'Darwin') {
        $env['DYLD_INSERT_LIBRARIES'] = '/usr/lib/libgmalloc.dylib';
        $env['USE_ZEND_ALLOC'] = '0';
    }

    $command = [PHP_BINARY, '-n', '-d', 'memory_limit=128M', '-d', 'extension='.ini_get('extension_dir').'/glfw.so', $file];
    $process = proc_open($command, [0 => ['file', '/dev/null', 'r'], 1 => ['pipe', 'w'], 2 => ['file', '/dev/null', 'w']], $pipes, null, $env);
    $stdout = (string) stream_get_contents($pipes[1]);
    fclose($pipes[1]);
    do {
        $status = proc_get_status($process);
        if ($status['running']) {
            usleep(20_000);
        }
    } while ($status['running']);
    proc_close($process);
    @unlink($file);

    return ['signal' => $status['signaled'] ? $status['termsig'] : null, 'stdout' => $stdout];
}

/** GLFW up for the whole run; tests that terminate it bring it back with this. */
function glfw(): void
{
    static $shutdown = false;
    if (glfwGetPlatform() === 0) {
        glfwInitVulkanLoader(vulkanLoader());
        glfwInit() || throw new RuntimeException('glfwInit: ' . glfwGetError($description) . ' ' . $description);
    }
    if (! $shutdown) {
        register_shutdown_function('glfwTerminate');
        $shutdown = true;
    }
}

/** A window that stays off screen unless a test shows it, with no client API unless $hints says so. */
function hiddenWindow(int $width = 320, int $height = 200, array $hints = []): GLFWwindow
{
    glfw();
    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    foreach ($hints as $hint => $value) {
        glfwWindowHint($hint, $value);
    }

    return glfwCreateWindow($width, $height, 'ext-glfw test') ?? throw new RuntimeException('glfwCreateWindow: ' . glfwGetError($description) . ' ' . $description);
}

/** Process events until $until() holds or $seconds pass; true when it held. */
function pumpUntil(callable $until, float $seconds): bool
{
    $limit = microtime(true) + $seconds;
    while (! $until()) {
        if (microtime(true) >= $limit) {
            return false;
        }
        glfwWaitEventsTimeout(0.01);
    }

    return true;
}

function pumpFor(float $seconds): void
{
    $limit = microtime(true) + $seconds;
    while (microtime(true) < $limit) {
        glfwWaitEventsTimeout(0.01);
    }
}

/** A hidden GL window: a 4.1 core context on macOS, the 3.1 every Linux desktop and the Pi 5's V3D offer elsewhere. */
function glWindow(): GLFWwindow
{
    return hiddenWindow(160, 120, PHP_OS_FAMILY === 'Darwin' ? [
        GLFW_CLIENT_API => GLFW_OPENGL_API,
        GLFW_CONTEXT_VERSION_MAJOR => 4,
        GLFW_CONTEXT_VERSION_MINOR => 1,
        GLFW_OPENGL_PROFILE => GLFW_OPENGL_CORE_PROFILE,
        GLFW_OPENGL_FORWARD_COMPAT => GLFW_TRUE,
    ] : [
        GLFW_CLIENT_API => GLFW_OPENGL_API,
        GLFW_CONTEXT_VERSION_MAJOR => 3,
        GLFW_CONTEXT_VERSION_MINOR => 1,
    ]);
}

/**
 * Wayland leaves the window's position, opacity and icon, and the monitor's gamma, to the
 * compositor: GLFW answers GLFW_FEATURE_UNAVAILABLE. It cannot learn that a window was iconified,
 * and a size the program sets is not called back; sizes the compositor sets (maximize) are.
 */
function onWayland(): bool
{
    return glfwGetPlatform() === GLFW_PLATFORM_WAYLAND;
}

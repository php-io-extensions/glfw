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

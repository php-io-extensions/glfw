<?php
/**
 * glfw extension — visual window proof
 *
 * Opens a real window and animates the clear color + a bouncing scissor
 * rect entirely through the glfw/OpenGL extension bindings (no FFI).
 *
 * Controls:
 *   ESC or close button — quit
 *
 * Usage:
 *   php -d extension=ext/modules/glfw.so examples/proof_window.php
 */

declare(strict_types=1);

use Glfw\GLFW\GLFW;
use Glfw\GLFW\GLFWError;
use Glfw\GLFW\Window\GLFWWindow;
use Glfw\GLFW\Context\GLFWContext;
use Glfw\GLFW\Input\GLFWInput;
use Glfw\GLFW\GL\GLFWGL;

// GLFW / OpenGL tokens (microscrap enums later)
const GLFW_KEY_ESCAPE = 256;
const GLFW_PRESS = 1;
const GLFW_CONTEXT_VERSION_MAJOR = 0x00022002;
const GLFW_CONTEXT_VERSION_MINOR = 0x00022003;
const GLFW_OPENGL_FORWARD_COMPAT = 0x00022006;
const GLFW_OPENGL_PROFILE = 0x00022008;
const GLFW_OPENGL_CORE_PROFILE = 0x00032001;
const GLFW_OPENGL_ANY_PROFILE = 0;
const GLFW_RESIZABLE = 0x00020003;

const GL_COLOR_BUFFER_BIT = 0x00004000;
const GL_SCISSOR_TEST = 0x0C11;
const GL_VENDOR = 0x1F00;
const GL_RENDERER = 0x1F01;
const GL_VERSION = 0x1F02;

function hsv_to_rgb(float $h, float $s, float $v): array
{
    $i = (int) floor($h * 6.0);
    $f = $h * 6.0 - $i;
    $p = $v * (1.0 - $s);
    $q = $v * (1.0 - $f * $s);
    $t = $v * (1.0 - (1.0 - $f) * $s);

    return match ($i % 6) {
        0 => [$v, $t, $p],
        1 => [$q, $v, $p],
        2 => [$p, $v, $t],
        3 => [$p, $q, $v],
        4 => [$t, $p, $v],
        default => [$v, $p, $q],
    };
}

if (!extension_loaded('glfw')) {
    fwrite(STDERR, "glfw extension is NOT loaded.\n");
    exit(1);
}

if (!GLFW::glfwInit()) {
    $err = GLFWError::glfwGetError();
    fwrite(STDERR, "glfwInit failed: {$err['description']}\n");
    exit(1);
}

// Prefer a simple compatibility-friendly context so desktop GL 1.x entry
// points (glClear/glScissor) are available everywhere we target.
GLFWWindow::glfwDefaultWindowHints();
GLFWWindow::glfwWindowHint(GLFW_RESIZABLE, 1);
GLFWWindow::glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
GLFWWindow::glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
GLFWWindow::glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

try {
    $window = GLFWWindow::glfwCreateWindow(960, 540, 'GLFW go brr — php-io-extensions/glfw');
} catch (Throwable $e) {
    fwrite(STDERR, $e->getMessage() . "\n");
    GLFW::glfwTerminate();
    exit(1);
}

GLFWContext::glfwMakeContextCurrent($window);
GLFWContext::glfwSwapInterval(1);

$vendor = GLFWGL::glGetString(GL_VENDOR);
$renderer = GLFWGL::glGetString(GL_RENDERER);
$version = GLFWGL::glGetString(GL_VERSION);
echo "OpenGL vendor   : {$vendor}\n";
echo "OpenGL renderer : {$renderer}\n";
echo "OpenGL version  : {$version}\n";
echo "Window is live. Press ESC or close the window to quit.\n";

$fb = GLFWWindow::glfwGetFramebufferSize($window);
$fbW = max(1, (int) $fb['width']);
$fbH = max(1, (int) $fb['height']);
GLFWGL::glViewport(0, 0, $fbW, $fbH);

GLFWWindow::glfwSetFramebufferSizeCallback($window, function (int $win, int $w, int $h) use (&$fbW, &$fbH): void {
    $fbW = max(1, $w);
    $fbH = max(1, $h);
    GLFWContext::glfwMakeContextCurrent($win);
    GLFWGL::glViewport(0, 0, $fbW, $fbH);
});

GLFWInput::glfwSetKeyCallback($window, function (int $win, int $key, int $scancode, int $action, int $mods): void {
    if ($key === GLFW_KEY_ESCAPE && $action === GLFW_PRESS) {
        GLFWWindow::glfwSetWindowShouldClose($win, 1);
    }
});

$rectW = 160;
$rectH = 120;
$x = 80.0;
$y = 60.0;
$vx = 280.0;
$vy = 220.0;
$frames = 0;
$fpsT0 = GLFWInput::glfwGetTime();
$last = $fpsT0;
$autoQuit = getenv('GLFW_PROOF_SECONDS');
$autoQuitAt = ($autoQuit !== false && $autoQuit !== '')
    ? $fpsT0 + (float) $autoQuit
    : null;

while (!GLFWWindow::glfwWindowShouldClose($window)) {
    $now = GLFWInput::glfwGetTime();
    if (!is_null($autoQuitAt) && $now >= $autoQuitAt) {
        break;
    }
    $dt = max(0.0, min(0.05, $now - $last));
    $last = $now;

    // Rainbow clear
    $hue = fmod($now * 0.15, 1.0);
    [$r, $g, $b] = hsv_to_rgb($hue, 0.55, 0.35);
    GLFWGL::glDisable(GL_SCISSOR_TEST);
    GLFWGL::glClearColor($r, $g, $b, 1.0);
    GLFWGL::glClear(GL_COLOR_BUFFER_BIT);

    // Bounce a bright scissor rect around the framebuffer
    $x += $vx * $dt;
    $y += $vy * $dt;
    if ($x < 0) {
        $x = 0;
        $vx = abs($vx);
    } elseif ($x + $rectW > $fbW) {
        $x = $fbW - $rectW;
        $vx = -abs($vx);
    }
    if ($y < 0) {
        $y = 0;
        $vy = abs($vy);
    } elseif ($y + $rectH > $fbH) {
        $y = $fbH - $rectH;
        $vy = -abs($vy);
    }

    [$rr, $rg, $rb] = hsv_to_rgb(fmod($hue + 0.45, 1.0), 0.9, 1.0);
    GLFWGL::glEnable(GL_SCISSOR_TEST);
    GLFWGL::glScissor((int) $x, (int) $y, $rectW, $rectH);
    GLFWGL::glClearColor($rr, $rg, $rb, 1.0);
    GLFWGL::glClear(GL_COLOR_BUFFER_BIT);

    GLFWContext::glfwSwapBuffers($window);
    GLFWWindow::glfwPollEvents();

    $frames++;
    if ($now - $fpsT0 >= 0.5) {
        $fps = $frames / ($now - $fpsT0);
        GLFWWindow::glfwSetWindowTitle(
            $window,
            sprintf('GLFW go brr — %.0f FPS — ESC to quit', $fps)
        );
        $frames = 0;
        $fpsT0 = $now;
    }
}

GLFWWindow::glfwDestroyWindow($window);
GLFW::glfwTerminate();
echo "Window closed cleanly.\n";
exit(0);

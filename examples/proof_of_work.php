<?php
/**
 * glfw extension — proof-of-work script
 *
 * Creates a hidden window, polls once, then tears down.
 *
 * Usage:
 *   php -d extension=ext/modules/glfw.so examples/proof_of_work.php
 */

declare(strict_types=1);

use Glfw\GLFW\GLFW;
use Glfw\GLFW\GLFWError;
use Glfw\GLFW\Window\GLFWWindow;
use Glfw\GLFW\Context\GLFWContext;
use Glfw\GLFW\Monitor\GLFWMonitor;

function pass(string $label): void
{
    echo "  [PASS] {$label}\n";
}

function fail(string $label, string $detail = ''): void
{
    $msg = "  [FAIL] {$label}";
    if ($detail !== '') {
        $msg .= ": {$detail}";
    }
    echo $msg . "\n";
}

function section(string $title): void
{
    echo "\n── {$title} ──\n";
}

$errors = 0;

section('Extension check');
if (extension_loaded('glfw')) {
    pass('glfw extension is loaded');
} else {
    echo "  [FATAL] glfw extension is NOT loaded. Aborting.\n";
    exit(1);
}

section('Library metadata');
$version = GLFW::glfwGetVersion();
$versionString = GLFW::glfwGetVersionString();
if (($version['major'] ?? 0) >= 3) {
    pass("glfwGetVersion => {$version['major']}.{$version['minor']}.{$version['rev']}");
} else {
    fail('glfwGetVersion', json_encode($version));
    $errors++;
}
pass("glfwGetVersionString => {$versionString}");

section('Init');
if (!GLFW::glfwInit()) {
    $err = GLFWError::glfwGetError();
    fail('glfwInit', $err['description'] ?? 'unknown');
    exit(1);
}
pass('glfwInit');

$platform = GLFW::glfwGetPlatform();
pass("glfwGetPlatform => {$platform}");

section('Monitors');
$monitors = GLFWMonitor::glfwGetMonitors();
$primary = GLFWMonitor::glfwGetPrimaryMonitor();
pass('glfwGetMonitors count=' . count($monitors));
if ($primary !== 0) {
    $name = GLFWMonitor::glfwGetMonitorName($primary);
    pass("glfwGetPrimaryMonitor name={$name}");
} else {
    fail('glfwGetPrimaryMonitor', 'null handle');
    $errors++;
}

section('Window (hidden)');
// GLFW_VISIBLE = 0x00020004
GLFWWindow::glfwWindowHint(0x00020004, 0);
try {
    $window = GLFWWindow::glfwCreateWindow(640, 480, 'glfw proof_of_work');
    pass("glfwCreateWindow => {$window}");
} catch (Throwable $e) {
    fail('glfwCreateWindow', $e->getMessage());
    GLFW::glfwTerminate();
    exit(1);
}

$size = GLFWWindow::glfwGetWindowSize($window);
pass("glfwGetWindowSize => {$size['width']}x{$size['height']}");

GLFWContext::glfwMakeContextCurrent($window);
pass('glfwMakeContextCurrent');

GLFWWindow::glfwPollEvents();
pass('glfwPollEvents');

GLFWContext::glfwSwapBuffers($window);
pass('glfwSwapBuffers');

GLFWWindow::glfwDestroyWindow($window);
pass('glfwDestroyWindow');

GLFW::glfwTerminate();
pass('glfwTerminate');

echo "\n";
if ($errors > 0) {
    echo "Completed with {$errors} failure(s).\n";
    exit(1);
}
echo "All proof_of_work checks passed.\n";
exit(0);

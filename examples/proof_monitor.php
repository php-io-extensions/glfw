<?php
/**
 * glfw extension — monitor / video-mode proof (adapted from sdl3 proof_video)
 *
 * Usage:
 *   php -d extension=ext/modules/glfw.so examples/proof_monitor.php
 */

declare(strict_types=1);

use Glfw\GLFW\GLFW;
use Glfw\GLFW\GLFWError;
use Glfw\GLFW\Monitor\GLFWMonitor;

function pass(string $label): void
{
    echo "  [PASS] {$label}\n";
}

function fail(string $label, string $detail = ''): void
{
    echo "  [FAIL] {$label}" . ($detail !== '' ? ": {$detail}" : '') . "\n";
}

function section(string $title): void
{
    echo "\n── {$title} ──\n";
}

$errors = 0;

section('Extension check');
if (!extension_loaded('glfw')) {
    echo "  [FATAL] glfw extension is NOT loaded.\n";
    exit(1);
}
pass('glfw extension is loaded');

section('Init');
if (!GLFW::glfwInit()) {
    $err = GLFWError::glfwGetError();
    fail('glfwInit', $err['description'] ?? 'unknown');
    exit(1);
}
pass('glfwInit');

section('Monitors');
$monitors = GLFWMonitor::glfwGetMonitors();
$primary = GLFWMonitor::glfwGetPrimaryMonitor();
pass('glfwGetMonitors count=' . count($monitors));

if ($primary === 0) {
    fail('glfwGetPrimaryMonitor', 'null handle');
    $errors++;
} else {
    pass('glfwGetPrimaryMonitor');
    pass('name=' . GLFWMonitor::glfwGetMonitorName($primary));
    $pos = GLFWMonitor::glfwGetMonitorPos($primary);
    pass("pos={$pos['xpos']},{$pos['ypos']}");
    $work = GLFWMonitor::glfwGetMonitorWorkarea($primary);
    pass("workarea={$work['width']}x{$work['height']} @ {$work['xpos']},{$work['ypos']}");
    $phys = GLFWMonitor::glfwGetMonitorPhysicalSize($primary);
    pass("physical={$phys['widthMM']}x{$phys['heightMM']} mm");
    $scale = GLFWMonitor::glfwGetMonitorContentScale($primary);
    pass("contentScale={$scale['xscale']}x{$scale['yscale']}");
    $mode = GLFWMonitor::glfwGetVideoMode($primary);
    if ($mode === []) {
        fail('glfwGetVideoMode', 'empty');
        $errors++;
    } else {
        pass("videoMode={$mode['width']}x{$mode['height']}@{$mode['refreshRate']}Hz");
    }
    $modes = GLFWMonitor::glfwGetVideoModes($primary);
    pass('glfwGetVideoModes count=' . count($modes));
}

foreach ($monitors as $i => $monitor) {
    $name = GLFWMonitor::glfwGetMonitorName($monitor);
    pass("monitor[{$i}] {$name}");
}

GLFW::glfwTerminate();
pass('glfwTerminate');

echo "\n";
exit($errors > 0 ? 1 : 0);

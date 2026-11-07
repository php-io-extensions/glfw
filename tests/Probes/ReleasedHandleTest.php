<?php

declare(strict_types=1);

// Site glfw-released-handle (outcome 1): a destroyed window's pointer is NULL. GLFW checks it only with
// assert(), which a release build of GLFW compiles out, and then dereferences it.

beforeEach(fn () => requireProbeBuild());

it('refuses a destroyed window, which GLFW dereferences (SIGSEGV) without the refusal', function (string $call): void {
    $code = "\$window = glfwCreateWindow(64, 64, 'probe');\nglfwDestroyWindow(\$window);\n{$call};";

    $kept = glfwProbe($code, null);
    $off = glfwProbe($code, 'glfw-released-handle');

    expect($kept['signal'])->toBeNull()
        ->and($kept['stdout'])->toContain('REFUSED ValueError')
        ->and($kept['stdout'])->toContain('GLFWwindow has been destroyed')
        ->and($off['signal'])->toBeIn([PROBE_SIGSEGV, PROBE_SIGBUS]);
})->with([
    'title' => ["glfwSetWindowTitle(\$window, 'x')"],
    'position' => ['glfwGetWindowPos($window, $x, $y)'],
    'should close' => ['glfwWindowShouldClose($window)'],
]);

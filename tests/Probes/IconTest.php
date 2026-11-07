<?php

declare(strict_types=1);

// Sites glfw-icon-pixels-length and glfw-list-count (outcome 1): GLFW reads 4 × width × height bytes of
// each image's pixels, and count images. A short pixel string, or a count past the list, makes it read
// past PHP's memory. On macOS GLFW ignores window icons (Cocoa has none), so the crash shows on X11 and
// Wayland only: the probe runs on Linux.

beforeEach(fn () => requireProbeBuild());

it('refuses icon pixels shorter than 4 × width × height, which GLFW reads past (SIGSEGV) without the refusal', function (): void {
    $code = <<<'PHP'
        $window = glfwCreateWindow(64, 64, 'probe');
        glfwSetWindowIcon($window, 1, [new GLFWimage(1024, 1024, 'ab')]);
    PHP;

    $kept = glfwProbe($code, null);
    $off = glfwProbe($code, 'glfw-icon-pixels-length');

    expect($kept['signal'])->toBeNull()
        ->and($kept['stdout'])->toContain('REFUSED ValueError')
        ->and($off['signal'])->toBeIn([PROBE_SIGSEGV, PROBE_SIGBUS]);
})->skip(PHP_OS_FAMILY === 'Darwin', 'GLFW ignores window icons on macOS');

it('refuses an image count past the list, which GLFW reads past (SIGSEGV) without the refusal', function (): void {
    $code = <<<'PHP'
        $window = glfwCreateWindow(64, 64, 'probe');
        glfwSetWindowIcon($window, 1 << 20, [new GLFWimage(1, 1, "\xff\xff\xff\xff")]);
    PHP;

    $kept = glfwProbe($code, null);
    $off = glfwProbe($code, 'glfw-list-count');

    expect($kept['signal'])->toBeNull()
        ->and($kept['stdout'])->toContain('REFUSED ValueError: glfwSetWindowIcon(): Argument #2 ($count) must be between 0 and the length of argument #3 ($images)')
        ->and($off['signal'])->toBeIn([PROBE_SIGSEGV, PROBE_SIGBUS]);
})->skip(PHP_OS_FAMILY === 'Darwin', 'GLFW ignores window icons on macOS');

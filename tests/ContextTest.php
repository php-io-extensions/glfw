<?php

declare(strict_types=1);

beforeEach(fn () => glfw());

it('makes the window\'s context current, and none', function (): void {
    $window = glWindow();

    glfwMakeContextCurrent($window);
    expect(glfwGetCurrentContext())->toBe($window)
        ->and(glfwGetWindowAttrib($window, GLFW_CLIENT_API))->toBe(GLFW_OPENGL_API)
        ->and(glfwGetWindowAttrib($window, GLFW_CONTEXT_VERSION_MAJOR))->toBe(PHP_OS_FAMILY === 'Darwin' ? 4 : 3);

    glfwMakeContextCurrent(null);
    expect(glfwGetCurrentContext())->toBeNull();

    glfwDestroyWindow($window);
});

it('turns vsync off and on, and swaps', function (): void {
    $window = glWindow();
    glfwMakeContextCurrent($window);
    glfwGetError();

    glfwSwapInterval(0);
    glfwSwapBuffers($window);
    glfwSwapInterval(1);
    glfwSwapBuffers($window);

    expect(glfwGetError())->toBe(GLFW_NO_ERROR);

    glfwMakeContextCurrent(null);
    glfwDestroyWindow($window);
});

it('finds GL functions and extensions through the current context', function (): void {
    $window = glWindow();
    glfwMakeContextCurrent($window);

    $found = glfwGetProcAddress('glGetString');
    $missing = glfwGetProcAddress('glNoSuchFunction');
    $extension = glfwExtensionSupported('GL_NO_such_extension');
    glfwMakeContextCurrent(null);

    // NSGL looks names up and answers 0 for an unknown one; EGL may answer a dispatch stub for any name.
    expect($found)->toBeGreaterThan(0)
        ->and($extension)->toBeFalse();
    if (PHP_OS_FAMILY === 'Darwin') {
        expect($missing)->toBe(0);
    }

    glfwDestroyWindow($window);
});

it('shares objects with the context of another window', function (): void {
    $first = glWindow();
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    $second = glfwCreateWindow(80, 60, 'shared', null, $first);

    expect($second)->toBeInstanceOf(GLFWwindow::class);

    glfwDestroyWindow($second);
    glfwDestroyWindow($first);
});

it('has no context on a window made with no client API', function (): void {
    $window = hiddenWindow();
    glfwMakeContextCurrent(null);
    glfwGetError();

    glfwMakeContextCurrent($window);

    expect(glfwGetError())->toBe(GLFW_NO_WINDOW_CONTEXT)
        ->and(glfwGetCurrentContext())->toBeNull();

    glfwDestroyWindow($window);
});

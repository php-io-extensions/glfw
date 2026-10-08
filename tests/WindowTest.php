<?php

declare(strict_types=1);

beforeEach(fn () => glfw());

it('creates a window from hints, titles it, and destroys it', function (): void {
    $window = hiddenWindow(320, 200);

    expect($window)->toBeInstanceOf(GLFWwindow::class)
        ->and(glfwGetWindowTitle($window))->toBe('ext-glfw test')
        ->and(glfwGetWindowAttrib($window, GLFW_VISIBLE))->toBe(GLFW_FALSE)
        ->and(GLFWwindow::fromPointer($window->pointer()))->toBe($window);

    glfwSetWindowTitle($window, 'Renamed');
    expect(glfwGetWindowTitle($window))->toBe('Renamed');

    glfwDestroyWindow($window);
    expect(fn () => glfwGetWindowTitle($window))->toThrow(ValueError::class, 'GLFWwindow has been destroyed')
        ->and(fn () => $window->pointer())->toThrow(ValueError::class, 'GLFWwindow has been destroyed');
});

it('opens where the position hints say', function (): void {
    $window = hiddenWindow(200, 150, [GLFW_POSITION_X => 140, GLFW_POSITION_Y => 160]);

    glfwGetError();
    glfwGetWindowPos($window, $x, $y);
    if (onWayland()) {
        expect([$x, $y])->toBe([0, 0])
            ->and(glfwGetError())->toBe(GLFW_FEATURE_UNAVAILABLE);
    } else {
        // GLFW 3.4.0 on Cocoa places GLFW_POSITION_Y from the screen's bottom; X lands as given everywhere.
        expect($x)->toBe(140);
        if (PHP_OS_FAMILY !== 'Darwin') {
            expect($y)->toBe(160);
        }
    }

    glfwDestroyWindow($window);
    glfwWindowHint(GLFW_POSITION_X, GLFW_ANY_POSITION);
});

it('moves and resizes, measuring its framebuffer in pixels and its frame in screen units', function (): void {
    $window = hiddenWindow(320, 200, [GLFW_VISIBLE => GLFW_TRUE]);

    glfwSetWindowPos($window, 100, 120);
    glfwSetWindowSize($window, 400, 300);
    pumpFor(0.1);
    glfwGetWindowPos($window, $x, $y);
    glfwGetWindowSize($window, $w, $h);
    glfwGetFramebufferSize($window, $fw, $fh);
    glfwGetWindowContentScale($window, $sx, $sy);
    glfwGetWindowFrameSize($window, $left, $top, $right, $bottom);

    expect([$w, $h])->toBe([400, 300])
        ->and(onWayland() ? [0, 0] : [100, 120])->toBe([$x, $y])
        ->and([$fw, $fh])->toBe([(int) (400 * $sx), (int) (300 * $sy)])
        ->and([$left, $top, $right, $bottom])->each->toBeGreaterThanOrEqual(0);
    // A title bar the platform draws has a height; under Wayland the compositor draws it and GLFW sees none.
    if (! onWayland()) {
        expect($top)->toBeGreaterThan(0);
    }

    glfwDestroyWindow($window);
});

it('hands its size limits and aspect ratio to the window manager', function (): void {
    if (PHP_OS_FAMILY !== 'Darwin' || ! extension_loaded('appkit')) {
        $this->markTestSkipped('reads the limits back through ext-appkit: GLFW has no getter, and they bind the user\'s resizing, not glfwSetWindowSize()');
    }
    $window = hiddenWindow(400, 300);
    $native = NSWindow::fromPointer(glfwGetCocoaWindow($window));

    glfwSetWindowSizeLimits($window, 200, 150, 600, 450);
    expect($native->contentMinSize())->toEqual(new NSSize(200.0, 150.0))
        ->and($native->contentMaxSize())->toEqual(new NSSize(600.0, 450.0));

    glfwSetWindowAspectRatio($window, 16, 9);
    expect($native->contentAspectRatio())->toEqual(new NSSize(16.0, 9.0));

    glfwSetWindowSizeLimits($window, GLFW_DONT_CARE, GLFW_DONT_CARE, GLFW_DONT_CARE, GLFW_DONT_CARE);
    glfwSetWindowAspectRatio($window, GLFW_DONT_CARE, GLFW_DONT_CARE);
    expect($native->contentMinSize())->toEqual(new NSSize(0.0, 0.0));

    glfwDestroyWindow($window);
});

it('shows, hides, focuses and fades', function (): void {
    $window = hiddenWindow();

    glfwShowWindow($window);
    glfwFocusWindow($window);
    $focused = pumpUntil(fn (): bool => glfwGetWindowAttrib($window, GLFW_FOCUSED) === GLFW_TRUE, 3.0);
    expect(glfwGetWindowAttrib($window, GLFW_VISIBLE))->toBe(GLFW_TRUE);
    // macOS refuses activation while the user works in another app; when it grants it, the attribute follows.
    if ($focused) {
        expect(glfwGetWindowAttrib($window, GLFW_FOCUSED))->toBe(GLFW_TRUE);
    }

    glfwGetError();
    glfwSetWindowOpacity($window, 0.5);
    expect(glfwGetWindowOpacity($window))->toEqualWithDelta(onWayland() ? 1.0 : 0.5, 0.01)
        ->and(glfwGetError())->toBe(onWayland() ? GLFW_FEATURE_UNAVAILABLE : GLFW_NO_ERROR);
    glfwRequestWindowAttention($window);

    glfwHideWindow($window);
    expect(glfwGetWindowAttrib($window, GLFW_VISIBLE))->toBe(GLFW_FALSE);

    glfwDestroyWindow($window);
});

it('iconifies, restores and maximizes', function (): void {
    $window = hiddenWindow(300, 200, [GLFW_VISIBLE => GLFW_TRUE]);
    pumpFor(0.2);

    glfwGetError();
    glfwIconifyWindow($window);
    if (onWayland()) {
        // The request goes to the compositor; Wayland never tells a client it was iconified.
        expect(glfwGetError())->toBe(GLFW_NO_ERROR);
    } else {
        expect(pumpUntil(fn (): bool => glfwGetWindowAttrib($window, GLFW_ICONIFIED) === GLFW_TRUE, 3.0))->toBeTrue();
    }

    glfwRestoreWindow($window);
    expect(pumpUntil(fn (): bool => glfwGetWindowAttrib($window, GLFW_ICONIFIED) === GLFW_FALSE, 3.0))->toBeTrue();

    glfwMaximizeWindow($window);
    expect(pumpUntil(fn (): bool => glfwGetWindowAttrib($window, GLFW_MAXIMIZED) === GLFW_TRUE, 3.0))->toBeTrue();

    glfwRestoreWindow($window);
    expect(pumpUntil(fn (): bool => glfwGetWindowAttrib($window, GLFW_MAXIMIZED) === GLFW_FALSE, 3.0))->toBeTrue();

    glfwDestroyWindow($window);
});

it('changes its attributes after creation: borderless, always on top, click-through', function (): void {
    $window = hiddenWindow();

    foreach ([GLFW_DECORATED, GLFW_RESIZABLE, GLFW_FLOATING, GLFW_MOUSE_PASSTHROUGH, GLFW_AUTO_ICONIFY, GLFW_FOCUS_ON_SHOW] as $attrib) {
        $flipped = glfwGetWindowAttrib($window, $attrib) === GLFW_TRUE ? GLFW_FALSE : GLFW_TRUE;
        glfwSetWindowAttrib($window, $attrib, $flipped);
        expect(glfwGetWindowAttrib($window, $attrib))->toBe($flipped);
    }

    glfwDestroyWindow($window);
});

it('makes a transparent framebuffer when hinted', function (): void {
    $window = hiddenWindow(100, 100, [GLFW_TRANSPARENT_FRAMEBUFFER => GLFW_TRUE]);

    expect(glfwGetWindowAttrib($window, GLFW_TRANSPARENT_FRAMEBUFFER))->toBe(GLFW_TRUE);

    glfwDestroyWindow($window);
});

it('raises and lowers the should-close flag', function (): void {
    $window = hiddenWindow();

    expect(glfwWindowShouldClose($window))->toBeFalse();
    glfwSetWindowShouldClose($window, true);
    expect(glfwWindowShouldClose($window))->toBeTrue();
    glfwSetWindowShouldClose($window, false);
    expect(glfwWindowShouldClose($window))->toBeFalse();

    glfwDestroyWindow($window);
});

it('goes full screen on a monitor in a video mode, and back to a window', function (): void {
    $window = hiddenWindow(320, 200, [GLFW_VISIBLE => GLFW_TRUE]);
    $monitor = glfwGetPrimaryMonitor();
    $mode = glfwGetVideoMode($monitor);

    expect(glfwGetWindowMonitor($window))->toBeNull();

    glfwSetWindowMonitor($window, $monitor, 0, 0, $mode->width, $mode->height, $mode->refreshRate);
    pumpFor(1.0);
    expect(glfwGetWindowMonitor($window))->toBe($monitor);

    glfwSetWindowMonitor($window, null, 100, 100, 320, 200, GLFW_DONT_CARE);
    pumpFor(1.0);
    glfwGetWindowSize($window, $w, $h);
    // Leaving full screen, a Wayland compositor picks the windowed size itself.
    expect(glfwGetWindowMonitor($window))->toBeNull()
        ->and(onWayland() ? $w > 0 && $h > 0 : [$w, $h] === [320, 200])->toBeTrue();

    glfwDestroyWindow($window);
});

it('takes a window icon where the platform has one', function (): void {
    $window = hiddenWindow();
    glfwGetError();

    glfwSetWindowIcon($window, [new GLFWimage(2, 2, str_repeat("\xff\x00\x00\xff", 4)), new GLFWimage(1, 1, "\x00\xff\x00\xff")]);
    $error = glfwGetError();
    glfwSetWindowIcon($window, []);

    expect($error)->toBe(PHP_OS_FAMILY === 'Darwin' || onWayland() ? GLFW_FEATURE_UNAVAILABLE : GLFW_NO_ERROR)
        ->and(fn () => glfwSetWindowIcon($window, [new GLFWimage(2, 2, 'short')]))->toThrow(ValueError::class, '4 x width x height bytes')
        ->and(fn () => glfwSetWindowIcon($window, ['not an image']))->toThrow(TypeError::class, 'must be a list of GLFWimage');

    glfwGetError();
    glfwDestroyWindow($window);
});

it('answers null for a window GLFW cannot make', function (): void {
    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 99);

    expect(glfwCreateWindow(100, 100, 'never'))->toBeNull()
        ->and(glfwGetError())->not->toBe(GLFW_NO_ERROR);

    glfwDefaultWindowHints();
});

it('refuses ints past 32 bits', function (): void {
    $window = hiddenWindow();

    expect(fn () => glfwSetWindowSize($window, 1 << 40, 10))->toThrow(ValueError::class, 'must be a 32-bit int');

    glfwDestroyWindow($window);
});

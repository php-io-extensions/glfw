<?php

declare(strict_types=1);

beforeEach(fn () => glfw());

it('calls back on move, resize and framebuffer resize, with the window', function (): void {
    $window = hiddenWindow(300, 200, [GLFW_VISIBLE => GLFW_TRUE]);
    $calls = [];
    glfwSetWindowPosCallback($window, function (GLFWwindow $w, int $x, int $y) use (&$calls, $window): void { $calls['pos'] = [$w === $window, $x, $y]; });
    glfwSetWindowSizeCallback($window, function (GLFWwindow $w, int $width, int $height) use (&$calls): void { $calls['size'] = [$width, $height]; });
    glfwSetFramebufferSizeCallback($window, function (GLFWwindow $w, int $width, int $height) use (&$calls): void { $calls['framebuffer'] = [$width, $height]; });

    if (onWayland()) {
        // No position on Wayland, and a size the program sets is not called back: the compositor's maximize is.
        glfwMaximizeWindow($window);
        pumpUntil(function () use (&$calls): bool { return count($calls) === 2; }, 3.0);
        glfwGetWindowSize($window, $w, $h);
        glfwGetFramebufferSize($window, $fw, $fh);

        expect($calls)->not->toHaveKey('pos')
            ->and($calls['size'])->toBe([$w, $h])
            ->and($calls['framebuffer'])->toBe([$fw, $fh]);
    } else {
        glfwSetWindowPos($window, 150, 170);
        glfwSetWindowSize($window, 360, 240);
        pumpUntil(function () use (&$calls): bool { return count($calls) === 3; }, 2.0);

        // The move can carry the window to a screen of another scale: the framebuffer is checked as it ends up.
        glfwGetFramebufferSize($window, $fw, $fh);

        expect($calls['pos'])->toBe([true, 150, 170])
            ->and($calls['size'])->toBe([360, 240])
            ->and($calls['framebuffer'])->toBe([$fw, $fh]);
    }

    glfwDestroyWindow($window);
});

it('calls back on focus', function (): void {
    // Hidden until the callback is set: a window shown at creation takes focus before anyone listens.
    $window = hiddenWindow(300, 200);
    $events = [];
    glfwSetWindowFocusCallback($window, function (GLFWwindow $w, bool $focused) use (&$events): void { $events[] = $focused; });

    glfwShowWindow($window);
    glfwFocusWindow($window);
    if (! pumpUntil(fn (): bool => glfwGetWindowAttrib($window, GLFW_FOCUSED) === GLFW_TRUE, 3.0)) {
        glfwDestroyWindow($window);
        $this->markTestSkipped('the window manager kept focus elsewhere: macOS refuses activation while the user works in another app, and Wayland compositors give focus only on user input');
    }
    pumpUntil(function () use (&$events): bool { return $events !== []; }, 2.0);

    expect($events)->toContain(true);

    glfwDestroyWindow($window);
});

it('calls back on iconify and maximize', function (): void {
    $window = hiddenWindow(300, 200, [GLFW_VISIBLE => GLFW_TRUE]);
    $events = [];
    glfwSetWindowIconifyCallback($window, function (GLFWwindow $w, bool $iconified) use (&$events): void { $events[] = ['iconify', $iconified]; });
    glfwSetWindowMaximizeCallback($window, function (GLFWwindow $w, bool $maximized) use (&$events): void { $events[] = ['maximize', $maximized]; });
    pumpFor(0.2);

    // Each step waits for its own event: Dock animations take longer while earlier ones still run.
    $saw = function (array $event) use (&$events): Closure {
        return function () use (&$events, $event): bool { return in_array($event, $events, true); };
    };
    // Wayland never tells a client it was iconified: only maximize calls back there.
    if (! onWayland()) {
        glfwIconifyWindow($window);
        expect(pumpUntil($saw(['iconify', true]), 5.0))->toBeTrue('no iconify callback');

        glfwRestoreWindow($window);
        expect(pumpUntil($saw(['iconify', false]), 5.0))->toBeTrue('no restore callback');
    }

    glfwMaximizeWindow($window);
    expect(pumpUntil($saw(['maximize', true]), 5.0))->toBeTrue('no maximize callback');

    glfwDestroyWindow($window);
});

it('calls back when the window is asked to close and when it needs redrawing', function (): void {
    if (! extension_loaded('appkit')) {
        $this->markTestSkipped('needs ext-appkit to press the close button');
    }
    $window = hiddenWindow(300, 200);
    $calls = [];
    glfwSetWindowCloseCallback($window, function (GLFWwindow $w) use (&$calls): void { $calls[] = 'close'; });
    glfwSetWindowRefreshCallback($window, function (GLFWwindow $w) use (&$calls): void { $calls[] = 'refresh'; });

    glfwShowWindow($window);
    pumpUntil(function () use (&$calls): bool { return in_array('refresh', $calls, true); }, 2.0);
    NSWindow::fromPointer(glfwGetCocoaWindow($window))->performClose(null);
    pumpUntil(function () use (&$calls): bool { return in_array('close', $calls, true); }, 2.0);

    expect($calls)->toContain('refresh')
        ->and($calls)->toContain('close')
        ->and(glfwWindowShouldClose($window))->toBeTrue();

    glfwDestroyWindow($window);
});

it('stores and clears the content-scale callback', function (): void {
    $window = hiddenWindow();
    glfwSetWindowContentScaleCallback($window, function (GLFWwindow $w, float $x, float $y): void {});
    glfwSetWindowContentScaleCallback($window, null);

    expect(fn () => glfwSetWindowContentScaleCallback($window, 'no such function'))->toThrow(TypeError::class, 'must be a valid callback or null');

    glfwDestroyWindow($window);
});

it('stops calling back once cleared', function (): void {
    $window = hiddenWindow(300, 200, [GLFW_VISIBLE => GLFW_TRUE]);
    $calls = 0;
    glfwSetWindowSizeCallback($window, function () use (&$calls): void { $calls++; });
    glfwSetWindowSizeCallback($window, null);

    glfwSetWindowSize($window, 330, 220);
    pumpFor(0.2);

    expect($calls)->toBe(0);

    glfwDestroyWindow($window);
});

it('lets an exception thrown by a callback surface from the event pump', function (): void {
    $window = hiddenWindow(300, 200, [GLFW_VISIBLE => GLFW_TRUE]);
    glfwSetWindowSizeCallback($window, function (): void { throw new LogicException('from the callback'); });

    // Cocoa resizes synchronously and calls back inside glfwSetWindowSize(); other platforms do from the pump.
    expect(function () use ($window): void {
        onWayland() ? glfwMaximizeWindow($window) : glfwSetWindowSize($window, 310, 210);
        pumpFor(1.0);
    })->toThrow(LogicException::class, 'from the callback');

    glfwDestroyWindow($window);
});

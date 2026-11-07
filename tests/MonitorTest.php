<?php

declare(strict_types=1);

beforeEach(fn () => glfw());

it('lists the monitors, the primary first, one object per monitor', function (): void {
    $monitors = glfwGetMonitors();

    expect($monitors)->not->toBeEmpty()
        ->and($monitors)->each->toBeInstanceOf(GLFWmonitor::class)
        ->and($monitors[0])->toBe(glfwGetPrimaryMonitor())
        ->and(GLFWmonitor::fromPointer($monitors[0]->pointer()))->toBe($monitors[0]);
});

it('places and measures the primary monitor', function (): void {
    $monitor = glfwGetPrimaryMonitor();

    glfwGetMonitorPos($monitor, $x, $y);
    glfwGetMonitorWorkarea($monitor, $wx, $wy, $ww, $wh);
    glfwGetMonitorPhysicalSize($monitor, $mm_w, $mm_h);
    glfwGetMonitorContentScale($monitor, $sx, $sy);
    $mode = glfwGetVideoMode($monitor);

    expect([$x, $y])->toBe([0, 0])
        ->and($ww)->toBeGreaterThan(0)->toBeLessThanOrEqual($mode->width)
        ->and($wh)->toBeGreaterThan(0)->toBeLessThanOrEqual($mode->height)
        ->and($mm_w)->toBeGreaterThan(0)
        ->and($mm_h)->toBeGreaterThan(0)
        ->and($sx)->toBeGreaterThanOrEqual(1.0)
        ->and($sy)->toBe($sx)
        ->and(glfwGetMonitorName($monitor))->not->toBe('');
});

it('lists the video modes, the current one among them', function (): void {
    $monitor = glfwGetPrimaryMonitor();
    $current = glfwGetVideoMode($monitor);
    $modes = glfwGetVideoModes($monitor);

    expect($current)->toBeInstanceOf(GLFWvidmode::class)
        ->and($current->width)->toBeGreaterThan(0)
        ->and($current->redBits)->toBe(8)
        ->and($current->refreshRate)->toBeGreaterThan(0)
        ->and($modes)->not->toBeEmpty()
        ->and($modes)->each->toBeInstanceOf(GLFWvidmode::class)
        ->and(array_column(array_map(fn (GLFWvidmode $m): array => (array) $m, $modes), 'refreshRate'))->toContain($current->refreshRate);

    // Cocoa reports the current mode in the scaled (point) size and lists modes in pixels; elsewhere the current mode is listed.
    if (PHP_OS_FAMILY !== 'Darwin') {
        expect(array_map(fn (GLFWvidmode $m): array => [$m->width, $m->height, $m->refreshRate], $modes))->toContain([$current->width, $current->height, $current->refreshRate]);
    }
});

it('reads the gamma ramp, sets gamma, and puts the ramp back', function (): void {
    $monitor = glfwGetPrimaryMonitor();
    if (onWayland()) {
        glfwGetError();
        expect(glfwGetGammaRamp($monitor))->toBeNull()
            ->and(glfwGetError())->toBe(GLFW_FEATURE_UNAVAILABLE);

        return;
    }
    $saved = glfwGetGammaRamp($monitor);

    expect($saved)->toBeInstanceOf(GLFWgammaramp::class)
        ->and(count($saved->red))->toBeGreaterThan(1)
        ->and(count($saved->green))->toBe(count($saved->red))
        ->and(count($saved->blue))->toBe(count($saved->red));

    glfwSetGamma($monitor, 1.0);
    $linear = glfwGetGammaRamp($monitor);
    glfwSetGammaRamp($monitor, $saved);

    expect($linear->red[0])->toBe(0)
        ->and(end($linear->red))->toBeGreaterThan(65000)
        ->and(glfwGetGammaRamp($monitor)->red)->toBe($saved->red);
});

// A C GLFWgammaramp has one size for its three arrays.
it('refuses channels of unequal length, which have no one size', function (): void {
    expect(fn () => glfwSetGammaRamp(glfwGetPrimaryMonitor(), new GLFWgammaramp([0, 1], [0], [0, 1])))->toThrow(ValueError::class, 'one length')
        ->and(fn () => glfwSetGammaRamp(glfwGetPrimaryMonitor(), new GLFWgammaramp(['x'], [0], [0])))->toThrow(TypeError::class, 'must hold ints in $red');
});

it('stores and clears the monitor callback, returning the one it replaces', function (): void {
    $first = function (GLFWmonitor $monitor, int $event): void {};

    expect(glfwSetMonitorCallback($first))->toBeNull()
        ->and(glfwSetMonitorCallback(null))->toBe($first);

    expect(fn () => glfwSetMonitorCallback('no such function'))->toThrow(TypeError::class, 'must be a valid callback or null');
});

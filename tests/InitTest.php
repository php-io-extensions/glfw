<?php

declare(strict_types=1);

afterEach(function (): void {
    glfwSetErrorCallback(null);
    glfw();
});

it('reports the GLFW it runs on', function (): void {
    glfw();
    glfwGetVersion($major, $minor, $rev);

    expect([$major, $minor])->toBe([3, 4])
        ->and($rev)->toBeInt()
        ->and(glfwGetVersionString())->toStartWith("{$major}.{$minor}.{$rev}");
});

it('names the platform it chose, and the ones it was built for', function (): void {
    glfw();
    $platform = glfwGetPlatform();

    expect(glfwPlatformSupported(GLFW_PLATFORM_NULL))->toBeTrue()
        ->and(glfwPlatformSupported($platform))->toBeTrue();

    if (PHP_OS_FAMILY === 'Darwin') {
        expect($platform)->toBe(GLFW_PLATFORM_COCOA)
            ->and(glfwPlatformSupported(GLFW_PLATFORM_X11))->toBeFalse();
    } else {
        expect($platform)->toBeIn([GLFW_PLATFORM_WAYLAND, GLFW_PLATFORM_X11]);
    }
});

it('hands each error to the callback and keeps the last for glfwGetError()', function (): void {
    glfw();
    $errors = [];
    glfwSetErrorCallback(function (int $code, string $description) use (&$errors): void {
        $errors[] = [$code, $description];
    });

    glfwWindowHint(0x7FFF0000, 1);

    expect($errors)->toHaveCount(1)
        ->and($errors[0][0])->toBe(GLFW_INVALID_ENUM)
        ->and($errors[0][1])->toContain('0x7FFF0000')
        ->and(glfwGetError($description))->toBe(GLFW_INVALID_ENUM)
        ->and($description)->toContain('0x7FFF0000')
        ->and(glfwGetError($cleared))->toBe(GLFW_NO_ERROR)
        ->and($cleared)->toBeNull();
});

it('stops calling back once the callback is cleared', function (): void {
    glfw();
    $calls = 0;
    glfwSetErrorCallback(function () use (&$calls): void { $calls++; });
    glfwSetErrorCallback(null);

    glfwWindowHint(0x7FFF0000, 1);

    expect($calls)->toBe(0)
        ->and(glfwGetError())->toBe(GLFW_INVALID_ENUM);
});

it('lets an exception thrown by the error callback surface from the call', function (): void {
    glfw();
    glfwSetErrorCallback(function (): void { throw new LogicException('from the callback'); });

    expect(fn () => glfwWindowHint(0x7FFF0000, 1))->toThrow(LogicException::class, 'from the callback');
    glfwGetError();
});

it('terminates, leaving its windows and monitors stale, and starts again', function (): void {
    $window = hiddenWindow();
    $monitor = glfwGetPrimaryMonitor();

    glfwTerminate();

    expect(glfwGetPlatform())->toBe(0)
        ->and(fn () => glfwGetWindowTitle($window))->toThrow(ValueError::class, 'GLFWwindow has been destroyed')
        ->and(fn () => glfwGetMonitorName($monitor))->toThrow(ValueError::class, 'GLFWmonitor has been disconnected');

    glfwGetError();
    glfwInitHint(GLFW_COCOA_MENUBAR, GLFW_FALSE);
    glfw();
    expect(glfwGetPlatform())->not->toBe(0);
    glfwInitHint(GLFW_COCOA_MENUBAR, GLFW_TRUE);
});

it('refuses a callback that is not callable', function (): void {
    expect(fn () => glfwSetErrorCallback('no such function'))->toThrow(TypeError::class, 'must be a valid callback or null');
});

<?php

declare(strict_types=1);

/*
 * Every stub declaration is what the loaded extension exposes: the stubs are the source of truth,
 * so a binding missing from the build fails here. Native functions count on their platform only.
 */

function glfwStubDeclarations(): array
{
    $platform = PHP_OS_FAMILY === 'Darwin' ? '__APPLE__' : '__linux__';
    $declared = ['functions' => [], 'constants' => [], 'classes' => []];

    foreach (glob(__DIR__ . '/../stubs/*.stub.php') as $stub) {
        $active = true;
        foreach (file($stub) as $line) {
            if (preg_match('/^#ifdef (\w+)/', $line, $m)) {
                $active = $m[1] === $platform;
            } elseif (str_starts_with($line, '#endif')) {
                $active = true;
            } elseif (! $active) {
                continue;
            } elseif (preg_match('/^function (\w+)/', $line, $m)) {
                $declared['functions'][] = $m[1];
            } elseif (preg_match('/^const (\w+)/', $line, $m)) {
                $declared['constants'][] = $m[1];
            } elseif (preg_match('/^final class (\w+)/', $line, $m)) {
                $declared['classes'][] = $m[1];
            }
        }
    }

    return $declared;
}

it('exposes every function, constant and class the stubs declare', function (): void {
    $declared = glfwStubDeclarations();

    foreach ($declared['functions'] as $function) {
        expect(function_exists($function))->toBeTrue("{$function}() is missing");
    }
    foreach ($declared['constants'] as $constant) {
        expect(defined($constant))->toBeTrue("{$constant} is missing");
    }
    foreach ($declared['classes'] as $class) {
        expect(class_exists($class))->toBeTrue("{$class} is missing");
    }

    expect(count($declared['functions']))->toBe(PHP_OS_FAMILY === 'Darwin' ? 87 : 95);
});

it('reports its version', function (): void {
    expect(phpversion('glfw'))->toBe('0.10.0');
});

it('carries the header values of its constants', function (): void {
    expect([GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_TRUE, GLFW_FALSE, GLFW_DONT_CARE])->toBe([3, 4, 1, 0, -1])
        ->and([GLFW_FOCUSED, GLFW_VISIBLE, GLFW_FLOATING, GLFW_MOUSE_PASSTHROUGH, GLFW_POSITION_X])->toBe([0x20001, 0x20004, 0x20007, 0x2000D, 0x2000E])
        ->and([GLFW_NO_API, GLFW_OPENGL_API, GLFW_OPENGL_CORE_PROFILE, GLFW_ANY_POSITION])->toBe([0, 0x30001, 0x32001, 0x80000000])
        ->and([GLFW_PLATFORM_COCOA, GLFW_PLATFORM_WAYLAND, GLFW_PLATFORM_X11, GLFW_CONNECTED, GLFW_DISCONNECTED])->toBe([0x60002, 0x60003, 0x60004, 0x40001, 0x40002])
        ->and([GLFW_NO_ERROR, GLFW_INVALID_ENUM, GLFW_FEATURE_UNAVAILABLE])->toBe([0, 0x10003, 0x1000C]);
});

it('keeps handles opaque: no constructor, no clone, no serialize', function (): void {
    expect(fn () => (new ReflectionClass(GLFWwindow::class))->newInstance())->toThrow(ReflectionException::class)
        ->and((new ReflectionClass(GLFWwindow::class))->isFinal())->toBeTrue()
        ->and((new ReflectionClass(GLFWmonitor::class))->isFinal())->toBeTrue();

    $window = hiddenWindow();
    expect(fn () => clone $window)->toThrow(Error::class)
        ->and(fn () => serialize($window))->toThrow(Exception::class);
    glfwDestroyWindow($window);
});

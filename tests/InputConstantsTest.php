<?php

declare(strict_types=1);

/*
 * The key, modifier, mouse button and action constants are the values glfw3.h defines: read from the
 * header GLFW was built against, an alias resolved through the defines that name it.
 */

function glfwHeaderDefines(): array
{
    $dir = trim((string) shell_exec('pkg-config --variable=includedir glfw3'));
    $text = file_get_contents($dir . '/GLFW/glfw3.h') ?: throw new RuntimeException('glfw3.h not found under ' . $dir);
    preg_match_all('/^#define\s+(GLFW_\w+)\s+(\S+)/m', $text, $found, PREG_SET_ORDER);

    return array_column($found, 2, 1);
}

function glfwHeaderValue(array $defines, string $name): int
{
    $value = $defines[$name];

    return isset($defines[$value]) ? glfwHeaderValue($defines, $value) : intval($value, 0);
}

it('binds the action, key, modifier and mouse button constants with the header values', function (): void {
    $defines = glfwHeaderDefines();
    $names = array_filter(
        array_keys($defines),
        fn (string $name): bool => in_array($name, ['GLFW_RELEASE', 'GLFW_PRESS', 'GLFW_REPEAT', 'GLFW_MOD_SHIFT', 'GLFW_MOD_CONTROL', 'GLFW_MOD_ALT', 'GLFW_MOD_SUPER'], true)
            || str_starts_with($name, 'GLFW_KEY_')
            || preg_match('/^GLFW_MOUSE_BUTTON_[1-8]$/', $name) === 1,
    );

    expect($names)->toHaveCount(137);
    foreach ($names as $name) {
        expect(defined($name))->toBeTrue("$name is not defined")
            ->and(constant($name))->toBe(glfwHeaderValue($defines, $name), $name);
    }
});

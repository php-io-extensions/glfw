<?php

declare(strict_types=1);

/*
 * glfwGetKey: the last state GLFW reported for a key to a window. Opens a hidden window (a GUI run).
 */

const GLFW_MODIFIER_KEYS = [
    GLFW_KEY_LEFT_SHIFT, GLFW_KEY_RIGHT_SHIFT, GLFW_KEY_LEFT_CONTROL, GLFW_KEY_RIGHT_CONTROL,
    GLFW_KEY_LEFT_ALT, GLFW_KEY_RIGHT_ALT, GLFW_KEY_LEFT_SUPER, GLFW_KEY_RIGHT_SUPER,
];

it('answers GLFW_RELEASE for every modifier key of a window nothing has been typed in', function (): void {
    $window = hiddenWindow();

    foreach (GLFW_MODIFIER_KEYS as $key) {
        expect(glfwGetKey($window, $key))->toBe(GLFW_RELEASE);
    }

    glfwDestroyWindow($window);
});

it('reports a bad key through glfwGetError, not an exception', function (): void {
    $window = hiddenWindow();
    glfwGetError($description);

    $state = glfwGetKey($window, GLFW_KEY_UNKNOWN);

    expect($state)->toBe(GLFW_RELEASE)
        ->and(glfwGetError($description))->toBe(GLFW_INVALID_ENUM);

    glfwDestroyWindow($window);
});

it('refuses a destroyed window', function (): void {
    $window = hiddenWindow();
    glfwDestroyWindow($window);

    expect(fn () => glfwGetKey($window, GLFW_KEY_A))->toThrow(ValueError::class);
});

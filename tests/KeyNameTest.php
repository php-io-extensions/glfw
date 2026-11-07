<?php

declare(strict_types=1);

/*
 * glfwGetKeyName: the layout's name for a printable key, null for a key with none. GLFW needs to be
 * initialised, and opens no window.
 */

it('names a printable key and gives null for a key with no name', function (): void {
    glfw();

    expect(glfwGetKeyName(GLFW_KEY_A, 0))->toBeString()->not->toBeEmpty()
        ->and(glfwGetKeyName(GLFW_KEY_LEFT_SHIFT, 0))->toBeNull()
        ->and(glfwGetKeyName(GLFW_KEY_ENTER, 0))->toBeNull();
});

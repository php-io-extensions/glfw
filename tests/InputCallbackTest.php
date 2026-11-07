<?php

declare(strict_types=1);

/*
 * Opens a hidden window: a GUI run. The input callbacks store, replace and clear their callable like
 * every glfwSet*Callback: each returns the one it replaces, null when there was none.
 */

dataset('input callbacks', [
    'key' => 'glfwSetKeyCallback',
    'char' => 'glfwSetCharCallback',
    'mouse button' => 'glfwSetMouseButtonCallback',
    'cursor position' => 'glfwSetCursorPosCallback',
    'cursor enter' => 'glfwSetCursorEnterCallback',
    'scroll' => 'glfwSetScrollCallback',
]);

it('returns the callback it replaces', function (string $set): void {
    $window = hiddenWindow();
    $first = static function (): void {};
    $second = static function (): void {};

    expect($set($window, $first))->toBeNull()
        ->and($set($window, $second))->toBe($first)
        ->and($set($window, null))->toBe($second)
        ->and($set($window, null))->toBeNull();

    glfwDestroyWindow($window);
})->with('input callbacks');

it('refuses a callback that is not callable', function (string $set): void {
    $window = hiddenWindow();

    expect(fn () => $set($window, 'no_such_function'))->toThrow(TypeError::class);

    glfwDestroyWindow($window);
})->with('input callbacks');

it('writes the cursor position into two by-reference floats', function (): void {
    $window = hiddenWindow();

    glfwGetCursorPos($window, $x, $y);

    expect($x)->toBeFloat()
        ->and($y)->toBeFloat();

    glfwDestroyWindow($window);
});

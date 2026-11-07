<?php

declare(strict_types=1);

beforeEach(fn () => glfw());

it('wakes a wait with an empty event', function (): void {
    $window = hiddenWindow();

    glfwPostEmptyEvent();
    $started = microtime(true);
    glfwWaitEvents();

    glfwPostEmptyEvent();
    glfwWaitEventsTimeout(5.0);

    expect(microtime(true) - $started)->toBeLessThan(1.0);

    glfwPollEvents();
    glfwDestroyWindow($window);
});

it('times out a wait with nothing to do', function (): void {
    // Earlier tests leave events behind: once they are drained, a wait lasts its timeout.
    $longest = 0.0;
    for ($i = 0; $i < 200 && $longest < 0.09; $i++) {
        $started = microtime(true);
        glfwWaitEventsTimeout(0.1);
        $longest = max($longest, microtime(true) - $started);
    }

    expect($longest)->toBeGreaterThanOrEqual(0.09)->toBeLessThan(0.5);
});

// GLFW reports GLFW_INVALID_VALUE for these and waits for nothing.
it('passes a timeout GLFW does not accept to GLFW, which reports it', function (float $timeout): void {
    glfwGetError();
    glfwWaitEventsTimeout($timeout);

    expect(glfwGetError())->toBe(GLFW_INVALID_VALUE);
})->with(['negative' => -1.0, 'infinite' => INF, 'NaN' => NAN]);

it('keeps time, and sets it', function (): void {
    glfwSetTime(10.0);
    $before = glfwGetTime();
    usleep(20_000);
    $value = glfwGetTimerValue();

    expect($before)->toBeGreaterThanOrEqual(10.0)
        ->and(glfwGetTime())->toBeGreaterThan($before + 0.015)
        ->and(glfwGetTimerFrequency())->toBeGreaterThan(0)
        ->and(glfwGetTimerValue())->toBeGreaterThan($value);
});

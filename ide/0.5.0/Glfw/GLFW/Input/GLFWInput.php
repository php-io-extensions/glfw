<?php

namespace Glfw\GLFW\Input;

/**
 * GLFW input, joystick, gamepad, clipboard, and timer APIs.
 */
class GLFWInput
{


    /**
     * @param int $window
     * @param int $mode
     * @return int
     */
    public static function glfwGetInputMode(int $window, int $mode): int
    {
    }

    /**
     * @param int $window
     * @param int $mode
     * @param int $value
     * @return void
     */
    public static function glfwSetInputMode(int $window, int $mode, int $value): void
    {
    }

    /**
     * @return bool
     */
    public static function glfwRawMouseMotionSupported(): bool
    {
    }

    /**
     * @param int $key
     * @param int $scancode
     * @return string
     */
    public static function glfwGetKeyName(int $key, int $scancode): string
    {
    }

    /**
     * @param int $key
     * @return int
     */
    public static function glfwGetKeyScancode(int $key): int
    {
    }

    /**
     * @param int $window
     * @param int $key
     * @return int
     */
    public static function glfwGetKey(int $window, int $key): int
    {
    }

    /**
     * @param int $window
     * @param int $button
     * @return int
     */
    public static function glfwGetMouseButton(int $window, int $button): int
    {
    }

    /**
     * @param int $window
     * @return array
     */
    public static function glfwGetCursorPos(int $window): array
    {
    }

    /**
     * @param int $window
     * @param double $xpos
     * @param double $ypos
     * @return void
     */
    public static function glfwSetCursorPos(int $window, float $xpos, float $ypos): void
    {
    }

    /**
     * @param array $image ["width"=>int,"height"=>int,"pixels"=>string]
     * @param int $xhot
     * @param int $yhot
     * @return int
     */
    public static function glfwCreateCursor(array $image, int $xhot, int $yhot): int
    {
    }

    /**
     * @param int $shape
     * @return int
     */
    public static function glfwCreateStandardCursor(int $shape): int
    {
    }

    /**
     * @param int $cursor
     * @return void
     */
    public static function glfwDestroyCursor(int $cursor): void
    {
    }

    /**
     * @param int $window
     * @param mixed $cursor
     * @return void
     */
    public static function glfwSetCursor(int $window, $cursor = null): void
    {
    }

    /**
     * @param int $window
     * @param mixed $callback
     * @return void
     */
    public static function glfwSetKeyCallback(int $window, $callback = null): void
    {
    }

    /**
     * @param int $window
     * @param mixed $callback
     * @return void
     */
    public static function glfwSetCharCallback(int $window, $callback = null): void
    {
    }

    /**
     * @param int $window
     * @param mixed $callback
     * @return void
     */
    public static function glfwSetCharModsCallback(int $window, $callback = null): void
    {
    }

    /**
     * @param int $window
     * @param mixed $callback
     * @return void
     */
    public static function glfwSetMouseButtonCallback(int $window, $callback = null): void
    {
    }

    /**
     * @param int $window
     * @param mixed $callback
     * @return void
     */
    public static function glfwSetCursorPosCallback(int $window, $callback = null): void
    {
    }

    /**
     * @param int $window
     * @param mixed $callback
     * @return void
     */
    public static function glfwSetCursorEnterCallback(int $window, $callback = null): void
    {
    }

    /**
     * @param int $window
     * @param mixed $callback
     * @return void
     */
    public static function glfwSetScrollCallback(int $window, $callback = null): void
    {
    }

    /**
     * @param int $window
     * @param mixed $callback
     * @return void
     */
    public static function glfwSetDropCallback(int $window, $callback = null): void
    {
    }

    /**
     * @param int $jid
     * @return bool
     */
    public static function glfwJoystickPresent(int $jid): bool
    {
    }

    /**
     * @param int $jid
     * @return array
     */
    public static function glfwGetJoystickAxes(int $jid): array
    {
    }

    /**
     * @param int $jid
     * @return array
     */
    public static function glfwGetJoystickButtons(int $jid): array
    {
    }

    /**
     * @param int $jid
     * @return array
     */
    public static function glfwGetJoystickHats(int $jid): array
    {
    }

    /**
     * @param int $jid
     * @return string
     */
    public static function glfwGetJoystickName(int $jid): string
    {
    }

    /**
     * @param int $jid
     * @return string
     */
    public static function glfwGetJoystickGUID(int $jid): string
    {
    }

    /**
     * @param int $jid
     * @param int $pointer
     * @return void
     */
    public static function glfwSetJoystickUserPointer(int $jid, int $pointer): void
    {
    }

    /**
     * @param int $jid
     * @return int
     */
    public static function glfwGetJoystickUserPointer(int $jid): int
    {
    }

    /**
     * @param int $jid
     * @return bool
     */
    public static function glfwJoystickIsGamepad(int $jid): bool
    {
    }

    /**
     * @param mixed $callback
     * @return void
     */
    public static function glfwSetJoystickCallback($callback = null): void
    {
    }

    /**
     * @param string $mapping
     * @return bool
     */
    public static function glfwUpdateGamepadMappings(string $mapping): bool
    {
    }

    /**
     * @param int $jid
     * @return string
     */
    public static function glfwGetGamepadName(int $jid): string
    {
    }

    /**
     * @param int $jid
     * @return array
     */
    public static function glfwGetGamepadState(int $jid): array
    {
    }

    /**
     * @param mixed $window
     * @param string $value
     * @return void
     */
    public static function glfwSetClipboardString($window, string $value): void
    {
    }

    /**
     * @param mixed $window
     * @return string
     */
    public static function glfwGetClipboardString($window = null): string
    {
    }

    /**
     * @return float
     */
    public static function glfwGetTime(): float
    {
    }

    /**
     * @param double $time
     * @return void
     */
    public static function glfwSetTime(float $time): void
    {
    }

    /**
     * @return int
     */
    public static function glfwGetTimerValue(): int
    {
    }

    /**
     * @return int
     */
    public static function glfwGetTimerFrequency(): int
    {
    }
}

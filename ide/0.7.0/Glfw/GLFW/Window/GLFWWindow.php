<?php

namespace Glfw\GLFW\Window;

/**
 * GLFW window creation, attributes, and event loop.
 */
class GLFWWindow
{


    /**
     * @return void
     */
    public static function glfwDefaultWindowHints(): void
    {
    }

    /**
     * @param int $hint
     * @param int $value
     * @return void
     */
    public static function glfwWindowHint(int $hint, int $value): void
    {
    }

    /**
     * @param int $hint
     * @param string $value
     * @return void
     */
    public static function glfwWindowHintString(int $hint, string $value): void
    {
    }

    /**
     * @param int|null $monitor Fullscreen monitor handle, or null
     * @param int|null $share Context-share window handle, or null
     * @param int $width
     * @param int $height
     * @param string $title
     * @return int
     */
    public static function glfwCreateWindow(int $width, int $height, string $title, $monitor = null, $share = null): int
    {
    }

    /**
     * @param int $window
     * @return void
     */
    public static function glfwDestroyWindow(int $window): void
    {
    }

    /**
     * @param int $window
     * @return bool
     */
    public static function glfwWindowShouldClose(int $window): bool
    {
    }

    /**
     * @param int $window
     * @param int $value
     * @return void
     */
    public static function glfwSetWindowShouldClose(int $window, int $value): void
    {
    }

    /**
     * @param int $window
     * @return string
     */
    public static function glfwGetWindowTitle(int $window): string
    {
    }

    /**
     * @param int $window
     * @param string $title
     * @return void
     */
    public static function glfwSetWindowTitle(int $window, string $title): void
    {
    }

    /**
     * @param array $images list of ["width"=>int,"height"=>int,"pixels"=>string]
     * @param int $window
     * @return void
     */
    public static function glfwSetWindowIcon(int $window, array $images): void
    {
    }

    /**
     * @param int $window
     * @return array
     */
    public static function glfwGetWindowPos(int $window): array
    {
    }

    /**
     * @param int $window
     * @param int $xpos
     * @param int $ypos
     * @return void
     */
    public static function glfwSetWindowPos(int $window, int $xpos, int $ypos): void
    {
    }

    /**
     * @param int $window
     * @return array
     */
    public static function glfwGetWindowSize(int $window): array
    {
    }

    /**
     * @param int $window
     * @param int $minwidth
     * @param int $minheight
     * @param int $maxwidth
     * @param int $maxheight
     * @return void
     */
    public static function glfwSetWindowSizeLimits(int $window, int $minwidth, int $minheight, int $maxwidth, int $maxheight): void
    {
    }

    /**
     * @param int $window
     * @param int $numer
     * @param int $denom
     * @return void
     */
    public static function glfwSetWindowAspectRatio(int $window, int $numer, int $denom): void
    {
    }

    /**
     * @param int $window
     * @param int $width
     * @param int $height
     * @return void
     */
    public static function glfwSetWindowSize(int $window, int $width, int $height): void
    {
    }

    /**
     * @param int $window
     * @return array
     */
    public static function glfwGetFramebufferSize(int $window): array
    {
    }

    /**
     * @param int $window
     * @return array
     */
    public static function glfwGetWindowFrameSize(int $window): array
    {
    }

    /**
     * @param int $window
     * @return array
     */
    public static function glfwGetWindowContentScale(int $window): array
    {
    }

    /**
     * @param int $window
     * @return float
     */
    public static function glfwGetWindowOpacity(int $window): float
    {
    }

    /**
     * @param int $window
     * @param double $opacity
     * @return void
     */
    public static function glfwSetWindowOpacity(int $window, float $opacity): void
    {
    }

    /**
     * @param int $window
     * @return void
     */
    public static function glfwIconifyWindow(int $window): void
    {
    }

    /**
     * @param int $window
     * @return void
     */
    public static function glfwRestoreWindow(int $window): void
    {
    }

    /**
     * @param int $window
     * @return void
     */
    public static function glfwMaximizeWindow(int $window): void
    {
    }

    /**
     * @param int $window
     * @return void
     */
    public static function glfwShowWindow(int $window): void
    {
    }

    /**
     * @param int $window
     * @return void
     */
    public static function glfwHideWindow(int $window): void
    {
    }

    /**
     * @param int $window
     * @return void
     */
    public static function glfwFocusWindow(int $window): void
    {
    }

    /**
     * @param int $window
     * @return void
     */
    public static function glfwRequestWindowAttention(int $window): void
    {
    }

    /**
     * @param int $window
     * @return int
     */
    public static function glfwGetWindowMonitor(int $window): int
    {
    }

    /**
     * @param int $window
     * @param mixed $monitor
     * @param int $xpos
     * @param int $ypos
     * @param int $width
     * @param int $height
     * @param int $refreshRate
     * @return void
     */
    public static function glfwSetWindowMonitor(int $window, $monitor, int $xpos, int $ypos, int $width, int $height, int $refreshRate): void
    {
    }

    /**
     * @param int $window
     * @param int $attrib
     * @return int
     */
    public static function glfwGetWindowAttrib(int $window, int $attrib): int
    {
    }

    /**
     * @param int $window
     * @param int $attrib
     * @param int $value
     * @return void
     */
    public static function glfwSetWindowAttrib(int $window, int $attrib, int $value): void
    {
    }

    /**
     * @param int $window
     * @param int $pointer
     * @return void
     */
    public static function glfwSetWindowUserPointer(int $window, int $pointer): void
    {
    }

    /**
     * @param int $window
     * @return int
     */
    public static function glfwGetWindowUserPointer(int $window): int
    {
    }

    /**
     * @param int $window
     * @param mixed $callback
     * @return void
     */
    public static function glfwSetWindowPosCallback(int $window, $callback = null): void
    {
    }

    /**
     * @param int $window
     * @param mixed $callback
     * @return void
     */
    public static function glfwSetWindowSizeCallback(int $window, $callback = null): void
    {
    }

    /**
     * @param int $window
     * @param mixed $callback
     * @return void
     */
    public static function glfwSetWindowCloseCallback(int $window, $callback = null): void
    {
    }

    /**
     * @param int $window
     * @param mixed $callback
     * @return void
     */
    public static function glfwSetWindowRefreshCallback(int $window, $callback = null): void
    {
    }

    /**
     * @param int $window
     * @param mixed $callback
     * @return void
     */
    public static function glfwSetWindowFocusCallback(int $window, $callback = null): void
    {
    }

    /**
     * @param int $window
     * @param mixed $callback
     * @return void
     */
    public static function glfwSetWindowIconifyCallback(int $window, $callback = null): void
    {
    }

    /**
     * @param int $window
     * @param mixed $callback
     * @return void
     */
    public static function glfwSetWindowMaximizeCallback(int $window, $callback = null): void
    {
    }

    /**
     * @param int $window
     * @param mixed $callback
     * @return void
     */
    public static function glfwSetFramebufferSizeCallback(int $window, $callback = null): void
    {
    }

    /**
     * @param int $window
     * @param mixed $callback
     * @return void
     */
    public static function glfwSetWindowContentScaleCallback(int $window, $callback = null): void
    {
    }

    /**
     * @return void
     */
    public static function glfwPollEvents(): void
    {
    }

    /**
     * @return void
     */
    public static function glfwWaitEvents(): void
    {
    }

    /**
     * @param double $timeout
     * @return void
     */
    public static function glfwWaitEventsTimeout(float $timeout): void
    {
    }

    /**
     * @return void
     */
    public static function glfwPostEmptyEvent(): void
    {
    }
}

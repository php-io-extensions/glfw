<?php

namespace Glfw\GLFW\Monitor;

/**
 * GLFW monitor and video mode APIs.
 */
class GLFWMonitor
{


    /**
     * @return array
     */
    public static function glfwGetMonitors(): array
    {
    }

    /**
     * @return int
     */
    public static function glfwGetPrimaryMonitor(): int
    {
    }

    /**
     * @param int $monitor
     * @return array
     */
    public static function glfwGetMonitorPos(int $monitor): array
    {
    }

    /**
     * @param int $monitor
     * @return array
     */
    public static function glfwGetMonitorWorkarea(int $monitor): array
    {
    }

    /**
     * @param int $monitor
     * @return array
     */
    public static function glfwGetMonitorPhysicalSize(int $monitor): array
    {
    }

    /**
     * @param int $monitor
     * @return array
     */
    public static function glfwGetMonitorContentScale(int $monitor): array
    {
    }

    /**
     * @param int $monitor
     * @return string
     */
    public static function glfwGetMonitorName(int $monitor): string
    {
    }

    /**
     * @param int $monitor
     * @param int $pointer
     * @return void
     */
    public static function glfwSetMonitorUserPointer(int $monitor, int $pointer): void
    {
    }

    /**
     * @param int $monitor
     * @return int
     */
    public static function glfwGetMonitorUserPointer(int $monitor): int
    {
    }

    /**
     * @param callable|null $callback function(int $monitor, int $event): void
     * @return void
     */
    public static function glfwSetMonitorCallback($callback = null): void
    {
    }

    /**
     * @param int $monitor
     * @return array
     */
    public static function glfwGetVideoModes(int $monitor): array
    {
    }

    /**
     * @param int $monitor
     * @return array
     */
    public static function glfwGetVideoMode(int $monitor): array
    {
    }

    /**
     * @param int $monitor
     * @param double $gamma
     * @return void
     */
    public static function glfwSetGamma(int $monitor, float $gamma): void
    {
    }

    /**
     * @param int $monitor
     * @return array
     */
    public static function glfwGetGammaRamp(int $monitor): array
    {
    }

    /**
     * @param array $ramp ["red"=>int[], "green"=>int[], "blue"=>int[], "size"=>int]
     * @param int $monitor
     * @return void
     */
    public static function glfwSetGammaRamp(int $monitor, array $ramp): void
    {
    }
}

<?php

namespace Glfw\GLFW\Vulkan;

/**
 * GLFW Vulkan support APIs.
 */
class GLFWVulkan
{


    /**
     * @return bool
     */
    public static function glfwVulkanSupported(): bool
    {
    }

    /**
     * @return array
     */
    public static function glfwGetRequiredInstanceExtensions(): array
    {
    }

    /**
     * @param int $instance VkInstance as opaque pointer int (0 = NULL)
     * @param string $procname
     * @return int
     */
    public static function glfwGetInstanceProcAddress(int $instance, string $procname): int
    {
    }

    /**
     * @param int $instance
     * @param int $device
     * @param int $queuefamily
     * @return bool
     */
    public static function glfwGetPhysicalDevicePresentationSupport(int $instance, int $device, int $queuefamily): bool
    {
    }

    /**
     * @param int $instance VkInstance pointer
     * @param int $window GLFWwindow handle
     * @param int $allocator VkAllocationCallbacks pointer, or 0
     * @return array{result: int, surface: int}
     */
    public static function glfwCreateWindowSurface(int $instance, int $window, int $allocator = 0): array
    {
    }
}

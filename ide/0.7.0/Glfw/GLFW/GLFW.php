<?php

namespace Glfw\GLFW;

/**
 * GLFW initialization, version, and platform APIs.
 */
class GLFW
{


    /**
     * @return bool
     */
    public static function glfwInit(): bool
    {
    }

    /**
     * @return void
     */
    public static function glfwTerminate(): void
    {
    }

    /**
     * @param int $hint
     * @param int $value
     * @return void
     */
    public static function glfwInitHint(int $hint, int $value): void
    {
    }

    /**
     * Custom allocators are not exposed to PHP; pass null to restore defaults.
     *
     * @param mixed $allocator
     * @return void
     */
    public static function glfwInitAllocator($allocator = null): void
    {
    }

    /**
     * @param int $loader Pointer to PFN_vkGetInstanceProcAddr, or 0 for NULL.
     * @return void
     */
    public static function glfwInitVulkanLoader(int $loader = 0): void
    {
    }

    /**
     * @return array
     */
    public static function glfwGetVersion(): array
    {
    }

    /**
     * @return string
     */
    public static function glfwGetVersionString(): string
    {
    }

    /**
     * @param callable|null $callback function(int $errorCode, string $description): void
     * @return void
     */
    public static function glfwSetErrorCallback($callback = null): void
    {
    }

    /**
     * @return int
     */
    public static function glfwGetPlatform(): int
    {
    }

    /**
     * @param int $platform
     * @return bool
     */
    public static function glfwPlatformSupported(int $platform): bool
    {
    }
}

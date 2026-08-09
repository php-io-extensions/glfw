<?php

namespace Glfw\GLFW\Context;

/**
 * OpenGL context management APIs.
 */
class GLFWContext
{


    /**
     * @param int $window
     * @return void
     */
    public static function glfwMakeContextCurrent(int $window): void
    {
    }

    /**
     * @return int
     */
    public static function glfwGetCurrentContext(): int
    {
    }

    /**
     * @param int $window
     * @return void
     */
    public static function glfwSwapBuffers(int $window): void
    {
    }

    /**
     * @param int $interval
     * @return void
     */
    public static function glfwSwapInterval(int $interval): void
    {
    }

    /**
     * @param string $extension
     * @return bool
     */
    public static function glfwExtensionSupported(string $extension): bool
    {
    }

    /**
     * Returns a function pointer as int, or 0 if unavailable.
     *
     * @param string $procname
     * @return int
     */
    public static function glfwGetProcAddress(string $procname): int
    {
    }
}

<?php

namespace Glfw\GLFW\GL;

/**
 * Minimal OpenGL entry points for GLFW context demos.
 * Constants (GL_COLOR_BUFFER_BIT, etc.) live in the microscrap wrapper.
 */
class GLFWGL
{


    /**
     * @param float $red
     * @param float $green
     * @param float $blue
     * @param float $alpha
     * @return void
     */
    public static function glClearColor(float $red, float $green, float $blue, float $alpha): void
    {
    }

    /**
     * @param int $mask
     * @return void
     */
    public static function glClear(int $mask): void
    {
    }

    /**
     * @param int $x
     * @param int $y
     * @param int $width
     * @param int $height
     * @return void
     */
    public static function glViewport(int $x, int $y, int $width, int $height): void
    {
    }

    /**
     * @param int $x
     * @param int $y
     * @param int $width
     * @param int $height
     * @return void
     */
    public static function glScissor(int $x, int $y, int $width, int $height): void
    {
    }

    /**
     * @param int $cap
     * @return void
     */
    public static function glEnable(int $cap): void
    {
    }

    /**
     * @param int $cap
     * @return void
     */
    public static function glDisable(int $cap): void
    {
    }

    /**
     * @return int
     */
    public static function glGetError(): int
    {
    }

    /**
     * @param int $name
     * @return string
     */
    public static function glGetString(int $name): string
    {
    }
}

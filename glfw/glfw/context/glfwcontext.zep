namespace Glfw\GLFW\Context;

%{
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdint.h>
}%

/**
 * OpenGL context management APIs.
 */
class GLFWContext
{
    public static function glfwMakeContextCurrent(int window) -> void
    {
        %{
            glfwMakeContextCurrent(window ? (GLFWwindow *)(uintptr_t) window : NULL);
        }%
    }

    public static function glfwGetCurrentContext() -> int
    {
        int ptr;
        %{
            ptr = (zend_long)(uintptr_t) glfwGetCurrentContext();
        }%
        return ptr;
    }

    public static function glfwSwapBuffers(int window) -> void
    {
        %{
            glfwSwapBuffers((GLFWwindow *)(uintptr_t) window);
        }%
    }

    public static function glfwSwapInterval(int interval) -> void
    {
        %{
            glfwSwapInterval((int) interval);
        }%
    }

    public static function glfwExtensionSupported(string extension) -> bool
    {
        bool result;
        %{
            result = glfwExtensionSupported(Z_STRVAL(extension)) == GLFW_TRUE;
        }%
        return result;
    }

    /**
     * Returns a function pointer as int, or 0 if unavailable.
     */
    public static function glfwGetProcAddress(string procname) -> int
    {
        int ptr;
        %{
            ptr = (zend_long)(uintptr_t) glfwGetProcAddress(Z_STRVAL(procname));
        }%
        return ptr;
    }
}

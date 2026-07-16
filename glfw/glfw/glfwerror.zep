namespace Glfw\GLFW;

%{
#include <GLFW/glfw3.h>
#include <stdio.h>
}%

/**
 * GLFW error query helpers.
 */
class GLFWError
{
    /**
     * Returns ["code" => int, "description" => string].
     * description is "" when GLFW returns NULL.
     */
    public static function glfwGetError() -> array
    {
        int code;
        string description;

        %{
            const char *desc = NULL;
            code = (zend_long) glfwGetError(&desc);
            if (desc) {
                ZVAL_STRING(&description, desc);
            } else {
                ZVAL_STRING(&description, "");
            }
        }%

        return ["code": code, "description": description];
    }
}

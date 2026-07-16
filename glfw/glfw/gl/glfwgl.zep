namespace Glfw\GLFW\GL;

%{
#if defined(__APPLE__)
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#include <stdio.h>
}%

/**
 * Minimal OpenGL entry points for GLFW context demos.
 * Constants (GL_COLOR_BUFFER_BIT, etc.) live in the microscrap wrapper.
 */
class GLFWGL
{
    public static function glClearColor(float red, float green, float blue, float alpha) -> void
    {
        %{
            glClearColor((GLfloat) red, (GLfloat) green, (GLfloat) blue, (GLfloat) alpha);
        }%
    }

    public static function glClear(int mask) -> void
    {
        %{
            glClear((GLbitfield) mask);
        }%
    }

    public static function glViewport(int x, int y, int width, int height) -> void
    {
        %{
            glViewport((GLint) x, (GLint) y, (GLsizei) width, (GLsizei) height);
        }%
    }

    public static function glScissor(int x, int y, int width, int height) -> void
    {
        %{
            glScissor((GLint) x, (GLint) y, (GLsizei) width, (GLsizei) height);
        }%
    }

    public static function glEnable(int cap) -> void
    {
        %{
            glEnable((GLenum) cap);
        }%
    }

    public static function glDisable(int cap) -> void
    {
        %{
            glDisable((GLenum) cap);
        }%
    }

    public static function glGetError() -> int
    {
        int result;
        %{
            result = (zend_long) glGetError();
        }%
        return result;
    }

    public static function glGetString(int name) -> string
    {
        string result;
        %{
            const GLubyte *s = glGetString((GLenum) name);
            ZVAL_STRING(&result, s ? (const char *) s : "");
        }%
        return result;
    }
}

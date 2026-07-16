
#ifdef HAVE_CONFIG_H
#include "../../../ext_config.h"
#endif

#include <php.h>
#include "../../../php_ext.h"
#include "../../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/object.h"

#if defined(__APPLE__)
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#include <stdio.h>



/**
 * Minimal OpenGL entry points for GLFW context demos.
 * Constants (GL_COLOR_BUFFER_BIT, etc.) live in the microscrap wrapper.
 */
ZEPHIR_INIT_CLASS(Glfw_GLFW_GL_GLFWGL)
{
	ZEPHIR_REGISTER_CLASS(Glfw\\GLFW\\GL, GLFWGL, glfw, glfw_gl_glfwgl, glfw_glfw_gl_glfwgl_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Glfw_GLFW_GL_GLFWGL, glClearColor)
{
	zval *red_param = NULL, *green_param = NULL, *blue_param = NULL, *alpha_param = NULL;
	double red, green, blue, alpha;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_ZVAL(red)
		Z_PARAM_ZVAL(green)
		Z_PARAM_ZVAL(blue)
		Z_PARAM_ZVAL(alpha)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(4, 0, &red_param, &green_param, &blue_param, &alpha_param);
	red = zephir_get_doubleval(red_param);
	green = zephir_get_doubleval(green_param);
	blue = zephir_get_doubleval(blue_param);
	alpha = zephir_get_doubleval(alpha_param);
	
            glClearColor((GLfloat) red, (GLfloat) green, (GLfloat) blue, (GLfloat) alpha);
        
}

PHP_METHOD(Glfw_GLFW_GL_GLFWGL, glClear)
{
	zval *mask_param = NULL;
	zend_long mask;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(mask)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &mask_param);
	
            glClear((GLbitfield) mask);
        
}

PHP_METHOD(Glfw_GLFW_GL_GLFWGL, glViewport)
{
	zval *x_param = NULL, *y_param = NULL, *width_param = NULL, *height_param = NULL;
	zend_long x, y, width, height;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
		Z_PARAM_LONG(width)
		Z_PARAM_LONG(height)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(4, 0, &x_param, &y_param, &width_param, &height_param);
	
            glViewport((GLint) x, (GLint) y, (GLsizei) width, (GLsizei) height);
        
}

PHP_METHOD(Glfw_GLFW_GL_GLFWGL, glScissor)
{
	zval *x_param = NULL, *y_param = NULL, *width_param = NULL, *height_param = NULL;
	zend_long x, y, width, height;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
		Z_PARAM_LONG(width)
		Z_PARAM_LONG(height)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(4, 0, &x_param, &y_param, &width_param, &height_param);
	
            glScissor((GLint) x, (GLint) y, (GLsizei) width, (GLsizei) height);
        
}

PHP_METHOD(Glfw_GLFW_GL_GLFWGL, glEnable)
{
	zval *cap_param = NULL;
	zend_long cap;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(cap)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &cap_param);
	
            glEnable((GLenum) cap);
        
}

PHP_METHOD(Glfw_GLFW_GL_GLFWGL, glDisable)
{
	zval *cap_param = NULL;
	zend_long cap;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(cap)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &cap_param);
	
            glDisable((GLenum) cap);
        
}

PHP_METHOD(Glfw_GLFW_GL_GLFWGL, glGetError)
{
	zend_long result = 0;
	
            result = (zend_long) glGetError();
        
	RETURN_LONG(result);
}

PHP_METHOD(Glfw_GLFW_GL_GLFWGL, glGetString)
{
	zval result;
	zval *name_param = NULL;
	zend_long name;

	ZVAL_UNDEF(&result);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(name)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &name_param);
	
            const GLubyte *s = glGetString((GLenum) name);
            ZVAL_STRING(&result, s ? (const char *) s : "");
        
	RETURN_CTORW(&result);
}


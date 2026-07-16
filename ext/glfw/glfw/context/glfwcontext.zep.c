
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

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdint.h>



/**
 * OpenGL context management APIs.
 */
ZEPHIR_INIT_CLASS(Glfw_GLFW_Context_GLFWContext)
{
	ZEPHIR_REGISTER_CLASS(Glfw\\GLFW\\Context, GLFWContext, glfw, glfw_context_glfwcontext, glfw_glfw_context_glfwcontext_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Glfw_GLFW_Context_GLFWContext, glfwMakeContextCurrent)
{
	zval *window_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            glfwMakeContextCurrent(window ? (GLFWwindow *)(uintptr_t) window : NULL);
        
}

PHP_METHOD(Glfw_GLFW_Context_GLFWContext, glfwGetCurrentContext)
{
	zend_long ptr = 0;
	
            ptr = (zend_long)(uintptr_t) glfwGetCurrentContext();
        
	RETURN_LONG(ptr);
}

PHP_METHOD(Glfw_GLFW_Context_GLFWContext, glfwSwapBuffers)
{
	zval *window_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            glfwSwapBuffers((GLFWwindow *)(uintptr_t) window);
        
}

PHP_METHOD(Glfw_GLFW_Context_GLFWContext, glfwSwapInterval)
{
	zval *interval_param = NULL;
	zend_long interval;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(interval)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &interval_param);
	
            glfwSwapInterval((int) interval);
        
}

PHP_METHOD(Glfw_GLFW_Context_GLFWContext, glfwExtensionSupported)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *extension_param = NULL;
	zval extension;

	ZVAL_UNDEF(&extension);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(extension)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &extension_param);
	zephir_get_strval(&extension, extension_param);
	
            result = glfwExtensionSupported(Z_STRVAL(extension)) == GLFW_TRUE;
        
	RETURN_MM_BOOL(result);
}

/**
 * Returns a function pointer as int, or 0 if unavailable.
 */
PHP_METHOD(Glfw_GLFW_Context_GLFWContext, glfwGetProcAddress)
{
	zend_long ptr = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *procname_param = NULL;
	zval procname;

	ZVAL_UNDEF(&procname);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(procname)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &procname_param);
	zephir_get_strval(&procname, procname_param);
	
            ptr = (zend_long)(uintptr_t) glfwGetProcAddress(Z_STRVAL(procname));
        
	RETURN_MM_LONG(ptr);
}


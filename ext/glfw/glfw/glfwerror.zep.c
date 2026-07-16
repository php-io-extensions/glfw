
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/array.h"
#include "kernel/memory.h"
#include "kernel/object.h"

#include <GLFW/glfw3.h>
#include <stdio.h>



/**
 * GLFW error query helpers.
 */
ZEPHIR_INIT_CLASS(Glfw_GLFW_GLFWError)
{
	ZEPHIR_REGISTER_CLASS(Glfw\\GLFW, GLFWError, glfw, glfw_glfwerror, glfw_glfw_glfwerror_method_entry, 0);

	return SUCCESS;
}

/**
 * Returns ["code" => int, "description" => string].
 * description is "" when GLFW returns NULL.
 */
PHP_METHOD(Glfw_GLFW_GLFWError, glfwGetError)
{
	zval _0;
	zval description;
	zend_long code = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;

	ZVAL_UNDEF(&description);
	ZVAL_UNDEF(&_0);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	
            const char *desc = NULL;
            code = (zend_long) glfwGetError(&desc);
            if (desc) {
                ZVAL_STRING(&description, desc);
            } else {
                ZVAL_STRING(&description, "");
            }
        
	zephir_create_array(return_value, 2, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, code);
	zephir_array_update_string(return_value, SL("code"), &_0, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(return_value, SL("description"), &description, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}


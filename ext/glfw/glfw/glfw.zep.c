
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
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/array.h"

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdint.h>

/* Declared in libglfw even when Vulkan headers are absent at compile time. */
extern void glfwInitVulkanLoader(void *loader);

static zval php_glfw_error_callback;
static bool php_glfw_error_callback_set = false;

static void php_glfw_error_callback_bridge(int error_code, const char *description)
{
    zval retval;
    zval params[2];

    if (!php_glfw_error_callback_set || Z_TYPE(php_glfw_error_callback) == IS_UNDEF || Z_TYPE(php_glfw_error_callback) == IS_NULL) {
        return;
    }

    ZVAL_LONG(&params[0], (zend_long) error_code);
    if (description) {
        ZVAL_STRING(&params[1], description);
    } else {
        ZVAL_STRING(&params[1], "");
    }
    ZVAL_UNDEF(&retval);

    call_user_function(EG(function_table), NULL, &php_glfw_error_callback, &retval, 2, params);

    zval_ptr_dtor(&params[1]);
    if (!Z_ISUNDEF(retval)) {
        zval_ptr_dtor(&retval);
    }
}



/**
 * GLFW initialization, version, and platform APIs.
 */
ZEPHIR_INIT_CLASS(Glfw_GLFW_GLFW)
{
	ZEPHIR_REGISTER_CLASS(Glfw\\GLFW, GLFW, glfw, glfw_glfw, glfw_glfw_glfw_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Glfw_GLFW_GLFW, glfwInit)
{
	zend_bool result = 0;
	
            result = glfwInit() == GLFW_TRUE;
        
	RETURN_BOOL(result);
}

PHP_METHOD(Glfw_GLFW_GLFW, glfwTerminate)
{

	
            glfwTerminate();
        
}

PHP_METHOD(Glfw_GLFW_GLFW, glfwInitHint)
{
	zval *hint_param = NULL, *value_param = NULL;
	zend_long hint, value;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(hint)
		Z_PARAM_LONG(value)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &hint_param, &value_param);
	
            glfwInitHint((int) hint, (int) value);
        
}

/**
 * Custom allocators are not exposed to PHP; pass null to restore defaults.
 */
PHP_METHOD(Glfw_GLFW_GLFW, glfwInitAllocator)
{
	zval *allocator = NULL, allocator_sub, __$null;

	ZVAL_UNDEF(&allocator_sub);
	ZVAL_NULL(&__$null);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(allocator)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(0, 1, &allocator);
	if (!allocator) {
		allocator = &allocator_sub;
		allocator = &__$null;
	}
	
            (void) allocator;
            glfwInitAllocator(NULL);
        
}

/**
 * @param int loader Pointer to PFN_vkGetInstanceProcAddr, or 0 for NULL.
 */
PHP_METHOD(Glfw_GLFW_GLFW, glfwInitVulkanLoader)
{
	zval *loader_param = NULL;
	zend_long loader;

	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(loader)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(0, 1, &loader_param);
	if (!loader_param) {
		loader = 0;
	} else {
		}
	
            glfwInitVulkanLoader(loader ? (void *)(uintptr_t) loader : NULL);
        
}

PHP_METHOD(Glfw_GLFW_GLFW, glfwGetVersion)
{
	zval _0;
	zend_long major = 0, minor = 0, rev = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;

	ZVAL_UNDEF(&_0);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	
            int maj = 0, min = 0, r = 0;
            glfwGetVersion(&maj, &min, &r);
            major = (zend_long) maj;
            minor = (zend_long) min;
            rev = (zend_long) r;
        
	zephir_create_array(return_value, 3, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, major);
	zephir_array_update_string(return_value, SL("major"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, minor);
	zephir_array_update_string(return_value, SL("minor"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, rev);
	zephir_array_update_string(return_value, SL("rev"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Glfw_GLFW_GLFW, glfwGetVersionString)
{
	zval result;

	ZVAL_UNDEF(&result);
	
            const char *s = glfwGetVersionString();
            ZVAL_STRING(&result, s ? s : "");
        
	RETURN_CTORW(&result);
}

/**
 * @param callable|null callback function(int $errorCode, string $description): void
 */
PHP_METHOD(Glfw_GLFW_GLFW, glfwSetErrorCallback)
{
	zval *callback = NULL, callback_sub, __$null;

	ZVAL_UNDEF(&callback_sub);
	ZVAL_NULL(&__$null);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(callback)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(0, 1, &callback);
	if (!callback) {
		callback = &callback_sub;
		callback = &__$null;
	}
	
            if (Z_TYPE_P(callback) == IS_NULL || Z_TYPE_P(callback) == IS_UNDEF) {
                if (php_glfw_error_callback_set) {
                    zval_ptr_dtor(&php_glfw_error_callback);
                    ZVAL_UNDEF(&php_glfw_error_callback);
                    php_glfw_error_callback_set = false;
                }
                glfwSetErrorCallback(NULL);
            } else {
                if (php_glfw_error_callback_set) {
                    zval_ptr_dtor(&php_glfw_error_callback);
                }
                ZVAL_COPY(&php_glfw_error_callback, callback);
                php_glfw_error_callback_set = true;
                glfwSetErrorCallback(php_glfw_error_callback_bridge);
            }
        
}

PHP_METHOD(Glfw_GLFW_GLFW, glfwGetPlatform)
{
	zend_long result = 0;
	
            result = (zend_long) glfwGetPlatform();
        
	RETURN_LONG(result);
}

PHP_METHOD(Glfw_GLFW_GLFW, glfwPlatformSupported)
{
	zend_bool result = 0;
	zval *platform_param = NULL;
	zend_long platform;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(platform)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &platform_param);
	
            result = glfwPlatformSupported((int) platform) == GLFW_TRUE;
        
	RETURN_BOOL(result);
}


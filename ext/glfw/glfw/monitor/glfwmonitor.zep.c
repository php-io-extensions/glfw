
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
#include "kernel/memory.h"
#include "kernel/object.h"
#include "kernel/array.h"
#include "kernel/operators.h"

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

static zval php_glfw_monitor_callback;
static bool php_glfw_monitor_callback_set = false;

static void php_glfw_monitor_callback_bridge(GLFWmonitor *monitor, int event)
{
    zval retval;
    zval params[2];

    if (!php_glfw_monitor_callback_set || Z_TYPE(php_glfw_monitor_callback) == IS_NULL) {
        return;
    }

    ZVAL_LONG(&params[0], (zend_long)(uintptr_t) monitor);
    ZVAL_LONG(&params[1], (zend_long) event);
    ZVAL_UNDEF(&retval);
    call_user_function(EG(function_table), NULL, &php_glfw_monitor_callback, &retval, 2, params);
    if (!Z_ISUNDEF(retval)) {
        zval_ptr_dtor(&retval);
    }
}

static void php_glfw_vidmode_to_zval(const GLFWvidmode *mode, zval *out)
{
    array_init(out);
    add_assoc_long(out, "width", mode->width);
    add_assoc_long(out, "height", mode->height);
    add_assoc_long(out, "redBits", mode->redBits);
    add_assoc_long(out, "greenBits", mode->greenBits);
    add_assoc_long(out, "blueBits", mode->blueBits);
    add_assoc_long(out, "refreshRate", mode->refreshRate);
}



/**
 * GLFW monitor and video mode APIs.
 */
ZEPHIR_INIT_CLASS(Glfw_GLFW_Monitor_GLFWMonitor)
{
	ZEPHIR_REGISTER_CLASS(Glfw\\GLFW\\Monitor, GLFWMonitor, glfw, glfw_monitor_glfwmonitor, glfw_glfw_monitor_glfwmonitor_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Glfw_GLFW_Monitor_GLFWMonitor, glfwGetMonitors)
{
	zval result;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;

	ZVAL_UNDEF(&result);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&result);
	array_init(&result);
	
            int count = 0;
            GLFWmonitor **monitors = glfwGetMonitors(&count);
            array_init(&result);
            if (monitors && count > 0) {
                int i;
                for (i = 0; i < count; i++) {
                    add_next_index_long(&result, (zend_long)(uintptr_t) monitors[i]);
                }
            }
        
	RETURN_CTOR(&result);
}

PHP_METHOD(Glfw_GLFW_Monitor_GLFWMonitor, glfwGetPrimaryMonitor)
{
	zend_long ptr = 0;
	
            ptr = (zend_long)(uintptr_t) glfwGetPrimaryMonitor();
        
	RETURN_LONG(ptr);
}

PHP_METHOD(Glfw_GLFW_Monitor_GLFWMonitor, glfwGetMonitorPos)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *monitor_param = NULL, _0;
	zend_long monitor, xpos = 0, ypos = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(monitor)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &monitor_param);
	
            int x = 0, y = 0;
            glfwGetMonitorPos((GLFWmonitor *)(uintptr_t) monitor, &x, &y);
            xpos = (zend_long) x;
            ypos = (zend_long) y;
        
	zephir_create_array(return_value, 2, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, xpos);
	zephir_array_update_string(return_value, SL("xpos"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, ypos);
	zephir_array_update_string(return_value, SL("ypos"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Glfw_GLFW_Monitor_GLFWMonitor, glfwGetMonitorWorkarea)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *monitor_param = NULL, _0;
	zend_long monitor, xpos = 0, ypos = 0, width = 0, height = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(monitor)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &monitor_param);
	
            int x = 0, y = 0, w = 0, h = 0;
            glfwGetMonitorWorkarea((GLFWmonitor *)(uintptr_t) monitor, &x, &y, &w, &h);
            xpos = (zend_long) x;
            ypos = (zend_long) y;
            width = (zend_long) w;
            height = (zend_long) h;
        
	zephir_create_array(return_value, 4, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, xpos);
	zephir_array_update_string(return_value, SL("xpos"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, ypos);
	zephir_array_update_string(return_value, SL("ypos"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, width);
	zephir_array_update_string(return_value, SL("width"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, height);
	zephir_array_update_string(return_value, SL("height"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Glfw_GLFW_Monitor_GLFWMonitor, glfwGetMonitorPhysicalSize)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *monitor_param = NULL, _0;
	zend_long monitor, widthMM = 0, heightMM = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(monitor)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &monitor_param);
	
            int w = 0, h = 0;
            glfwGetMonitorPhysicalSize((GLFWmonitor *)(uintptr_t) monitor, &w, &h);
            widthMM = (zend_long) w;
            heightMM = (zend_long) h;
        
	zephir_create_array(return_value, 2, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, widthMM);
	zephir_array_update_string(return_value, SL("widthMM"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, heightMM);
	zephir_array_update_string(return_value, SL("heightMM"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Glfw_GLFW_Monitor_GLFWMonitor, glfwGetMonitorContentScale)
{
	double xscale = 0, yscale = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *monitor_param = NULL, _0;
	zend_long monitor;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(monitor)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &monitor_param);
	
            float xs = 0.0f, ys = 0.0f;
            glfwGetMonitorContentScale((GLFWmonitor *)(uintptr_t) monitor, &xs, &ys);
            xscale = (double) xs;
            yscale = (double) ys;
        
	zephir_create_array(return_value, 2, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_DOUBLE(&_0, xscale);
	zephir_array_update_string(return_value, SL("xscale"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_DOUBLE(&_0, yscale);
	zephir_array_update_string(return_value, SL("yscale"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Glfw_GLFW_Monitor_GLFWMonitor, glfwGetMonitorName)
{
	zval result;
	zval *monitor_param = NULL;
	zend_long monitor;

	ZVAL_UNDEF(&result);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(monitor)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &monitor_param);
	
            const char *name = glfwGetMonitorName((GLFWmonitor *)(uintptr_t) monitor);
            ZVAL_STRING(&result, name ? name : "");
        
	RETURN_CTORW(&result);
}

PHP_METHOD(Glfw_GLFW_Monitor_GLFWMonitor, glfwSetMonitorUserPointer)
{
	zval *monitor_param = NULL, *pointer_param = NULL;
	zend_long monitor, pointer;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(monitor)
		Z_PARAM_LONG(pointer)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &monitor_param, &pointer_param);
	
            glfwSetMonitorUserPointer((GLFWmonitor *)(uintptr_t) monitor, (void *)(uintptr_t) pointer);
        
}

PHP_METHOD(Glfw_GLFW_Monitor_GLFWMonitor, glfwGetMonitorUserPointer)
{
	zval *monitor_param = NULL;
	zend_long monitor, ptr = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(monitor)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &monitor_param);
	
            ptr = (zend_long)(uintptr_t) glfwGetMonitorUserPointer((GLFWmonitor *)(uintptr_t) monitor);
        
	RETURN_LONG(ptr);
}

/**
 * @param callable|null callback function(int $monitor, int $event): void
 */
PHP_METHOD(Glfw_GLFW_Monitor_GLFWMonitor, glfwSetMonitorCallback)
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
                if (php_glfw_monitor_callback_set) {
                    zval_ptr_dtor(&php_glfw_monitor_callback);
                    ZVAL_UNDEF(&php_glfw_monitor_callback);
                    php_glfw_monitor_callback_set = false;
                }
                glfwSetMonitorCallback(NULL);
            } else {
                if (php_glfw_monitor_callback_set) {
                    zval_ptr_dtor(&php_glfw_monitor_callback);
                }
                ZVAL_COPY(&php_glfw_monitor_callback, callback);
                php_glfw_monitor_callback_set = true;
                glfwSetMonitorCallback(php_glfw_monitor_callback_bridge);
            }
        
}

PHP_METHOD(Glfw_GLFW_Monitor_GLFWMonitor, glfwGetVideoModes)
{
	zval result;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *monitor_param = NULL;
	zend_long monitor;

	ZVAL_UNDEF(&result);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(monitor)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &monitor_param);
	ZEPHIR_INIT_VAR(&result);
	array_init(&result);
	
            int count = 0;
            const GLFWvidmode *modes = glfwGetVideoModes((GLFWmonitor *)(uintptr_t) monitor, &count);
            array_init(&result);
            if (modes && count > 0) {
                int i;
                for (i = 0; i < count; i++) {
                    zval mode;
                    php_glfw_vidmode_to_zval(&modes[i], &mode);
                    add_next_index_zval(&result, &mode);
                }
            }
        
	RETURN_CTOR(&result);
}

PHP_METHOD(Glfw_GLFW_Monitor_GLFWMonitor, glfwGetVideoMode)
{
	zval result;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *monitor_param = NULL;
	zend_long monitor;

	ZVAL_UNDEF(&result);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(monitor)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &monitor_param);
	ZEPHIR_INIT_VAR(&result);
	array_init(&result);
	
            const GLFWvidmode *mode = glfwGetVideoMode((GLFWmonitor *)(uintptr_t) monitor);
            if (mode) {
                php_glfw_vidmode_to_zval(mode, &result);
            } else {
                array_init(&result);
            }
        
	RETURN_CTOR(&result);
}

PHP_METHOD(Glfw_GLFW_Monitor_GLFWMonitor, glfwSetGamma)
{
	double gamma;
	zval *monitor_param = NULL, *gamma_param = NULL;
	zend_long monitor;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(monitor)
		Z_PARAM_ZVAL(gamma)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &monitor_param, &gamma_param);
	gamma = zephir_get_doubleval(gamma_param);
	
            glfwSetGamma((GLFWmonitor *)(uintptr_t) monitor, (float) gamma);
        
}

PHP_METHOD(Glfw_GLFW_Monitor_GLFWMonitor, glfwGetGammaRamp)
{
	zval result;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *monitor_param = NULL;
	zend_long monitor;

	ZVAL_UNDEF(&result);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(monitor)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &monitor_param);
	ZEPHIR_INIT_VAR(&result);
	array_init(&result);
	
            const GLFWgammaramp *ramp = glfwGetGammaRamp((GLFWmonitor *)(uintptr_t) monitor);
            array_init(&result);
            if (ramp && ramp->size > 0) {
                zval red, green, blue;
                unsigned int i;
                array_init(&red);
                array_init(&green);
                array_init(&blue);
                for (i = 0; i < ramp->size; i++) {
                    add_next_index_long(&red, (zend_long) ramp->red[i]);
                    add_next_index_long(&green, (zend_long) ramp->green[i]);
                    add_next_index_long(&blue, (zend_long) ramp->blue[i]);
                }
                add_assoc_zval(&result, "red", &red);
                add_assoc_zval(&result, "green", &green);
                add_assoc_zval(&result, "blue", &blue);
                add_assoc_long(&result, "size", (zend_long) ramp->size);
            }
        
	RETURN_CTOR(&result);
}

/**
 * @param array ramp ["red"=>int[], "green"=>int[], "blue"=>int[], "size"=>int]
 */
PHP_METHOD(Glfw_GLFW_Monitor_GLFWMonitor, glfwSetGammaRamp)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval ramp;
	zval *monitor_param = NULL, *ramp_param = NULL;
	zend_long monitor;

	ZVAL_UNDEF(&ramp);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(monitor)
		Z_PARAM_ARRAY(ramp)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &monitor_param, &ramp_param);
	zephir_get_arrval(&ramp, ramp_param);
	
            zval *red_z, *green_z, *blue_z, *size_z;
            GLFWgammaramp gramp;
            unsigned short *red = NULL, *green = NULL, *blue = NULL;
            unsigned int size = 0;
            unsigned int i;

            size_z = zend_hash_str_find(Z_ARRVAL_P(&ramp), "size", sizeof("size") - 1);
            red_z = zend_hash_str_find(Z_ARRVAL_P(&ramp), "red", sizeof("red") - 1);
            green_z = zend_hash_str_find(Z_ARRVAL_P(&ramp), "green", sizeof("green") - 1);
            blue_z = zend_hash_str_find(Z_ARRVAL_P(&ramp), "blue", sizeof("blue") - 1);

            if (!size_z || !red_z || !green_z || !blue_z) {
                return;
            }
            size = (unsigned int) zval_get_long(size_z);
            if (size == 0 || Z_TYPE_P(red_z) != IS_ARRAY) {
                return;
            }

            red = ecalloc(size, sizeof(unsigned short));
            green = ecalloc(size, sizeof(unsigned short));
            blue = ecalloc(size, sizeof(unsigned short));

            for (i = 0; i < size; i++) {
                zval *rv = zend_hash_index_find(Z_ARRVAL_P(red_z), i);
                zval *gv = zend_hash_index_find(Z_ARRVAL_P(green_z), i);
                zval *bv = zend_hash_index_find(Z_ARRVAL_P(blue_z), i);
                red[i] = rv ? (unsigned short) zval_get_long(rv) : 0;
                green[i] = gv ? (unsigned short) zval_get_long(gv) : 0;
                blue[i] = bv ? (unsigned short) zval_get_long(bv) : 0;
            }

            gramp.red = red;
            gramp.green = green;
            gramp.blue = blue;
            gramp.size = size;
            glfwSetGammaRamp((GLFWmonitor *)(uintptr_t) monitor, &gramp);
            efree(red);
            efree(green);
            efree(blue);
        
	ZEPHIR_MM_RESTORE();
}



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
#include "kernel/array.h"

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* Defined in glfwwindow.zep */
extern void php_glfw_key_bridge(GLFWwindow *w, int key, int scancode, int action, int mods);
extern void php_glfw_char_bridge(GLFWwindow *w, unsigned int codepoint);
extern void php_glfw_charmods_bridge(GLFWwindow *w, unsigned int codepoint, int mods);
extern void php_glfw_mousebutton_bridge(GLFWwindow *w, int button, int action, int mods);
extern void php_glfw_cursorpos_bridge(GLFWwindow *w, double xpos, double ypos);
extern void php_glfw_cursorenter_bridge(GLFWwindow *w, int entered);
extern void php_glfw_scroll_bridge(GLFWwindow *w, double xoffset, double yoffset);
extern void php_glfw_drop_bridge(GLFWwindow *w, int count, const char **paths);
extern void php_glfw_window_callback_set_field(GLFWwindow *window, const char *name, zval *callback);

static zval php_glfw_joystick_callback;
static bool php_glfw_joystick_callback_set = false;

static void php_glfw_joystick_callback_bridge(int jid, int event)
{
    zval retval;
    zval params[2];
    if (!php_glfw_joystick_callback_set || Z_TYPE(php_glfw_joystick_callback) == IS_NULL) {
        return;
    }
    ZVAL_LONG(&params[0], (zend_long) jid);
    ZVAL_LONG(&params[1], (zend_long) event);
    ZVAL_UNDEF(&retval);
    call_user_function(EG(function_table), NULL, &php_glfw_joystick_callback, &retval, 2, params);
    if (!Z_ISUNDEF(retval)) {
        zval_ptr_dtor(&retval);
    }
}



/**
 * GLFW input, joystick, gamepad, clipboard, and timer APIs.
 */
ZEPHIR_INIT_CLASS(Glfw_GLFW_Input_GLFWInput)
{
	ZEPHIR_REGISTER_CLASS(Glfw\\GLFW\\Input, GLFWInput, glfw, glfw_input_glfwinput, glfw_glfw_input_glfwinput_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwGetInputMode)
{
	zval *window_param = NULL, *mode_param = NULL;
	zend_long window, mode, result = 0;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_LONG(mode)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &window_param, &mode_param);
	
            result = (zend_long) glfwGetInputMode((GLFWwindow *)(uintptr_t) window, (int) mode);
        
	RETURN_LONG(result);
}

PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwSetInputMode)
{
	zval *window_param = NULL, *mode_param = NULL, *value_param = NULL;
	zend_long window, mode, value;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(window)
		Z_PARAM_LONG(mode)
		Z_PARAM_LONG(value)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &window_param, &mode_param, &value_param);
	
            glfwSetInputMode((GLFWwindow *)(uintptr_t) window, (int) mode, (int) value);
        
}

PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwRawMouseMotionSupported)
{
	zend_bool result = 0;
	
            result = glfwRawMouseMotionSupported() == GLFW_TRUE;
        
	RETURN_BOOL(result);
}

PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwGetKeyName)
{
	zval result;
	zval *key_param = NULL, *scancode_param = NULL;
	zend_long key, scancode;

	ZVAL_UNDEF(&result);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(key)
		Z_PARAM_LONG(scancode)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &key_param, &scancode_param);
	
            const char *name = glfwGetKeyName((int) key, (int) scancode);
            ZVAL_STRING(&result, name ? name : "");
        
	RETURN_CTORW(&result);
}

PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwGetKeyScancode)
{
	zval *key_param = NULL;
	zend_long key, result = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(key)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &key_param);
	
            result = (zend_long) glfwGetKeyScancode((int) key);
        
	RETURN_LONG(result);
}

PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwGetKey)
{
	zval *window_param = NULL, *key_param = NULL;
	zend_long window, key, result = 0;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_LONG(key)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &window_param, &key_param);
	
            result = (zend_long) glfwGetKey((GLFWwindow *)(uintptr_t) window, (int) key);
        
	RETURN_LONG(result);
}

PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwGetMouseButton)
{
	zval *window_param = NULL, *button_param = NULL;
	zend_long window, button, result = 0;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_LONG(button)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &window_param, &button_param);
	
            result = (zend_long) glfwGetMouseButton((GLFWwindow *)(uintptr_t) window, (int) button);
        
	RETURN_LONG(result);
}

PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwGetCursorPos)
{
	double xpos = 0, ypos = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *window_param = NULL, _0;
	zend_long window;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &window_param);
	
            double x = 0.0, y = 0.0;
            glfwGetCursorPos((GLFWwindow *)(uintptr_t) window, &x, &y);
            xpos = x; ypos = y;
        
	zephir_create_array(return_value, 2, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_DOUBLE(&_0, xpos);
	zephir_array_update_string(return_value, SL("xpos"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_DOUBLE(&_0, ypos);
	zephir_array_update_string(return_value, SL("ypos"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwSetCursorPos)
{
	double xpos, ypos;
	zval *window_param = NULL, *xpos_param = NULL, *ypos_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(window)
		Z_PARAM_ZVAL(xpos)
		Z_PARAM_ZVAL(ypos)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &window_param, &xpos_param, &ypos_param);
	xpos = zephir_get_doubleval(xpos_param);
	ypos = zephir_get_doubleval(ypos_param);
	
            glfwSetCursorPos((GLFWwindow *)(uintptr_t) window, xpos, ypos);
        
}

/**
 * @param array image ["width"=>int,"height"=>int,"pixels"=>string]
 */
PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwCreateCursor)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long xhot, yhot, ptr = 0;
	zval *image_param = NULL, *xhot_param = NULL, *yhot_param = NULL;
	zval image;

	ZVAL_UNDEF(&image);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_ARRAY(image)
		Z_PARAM_LONG(xhot)
		Z_PARAM_LONG(yhot)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &image_param, &xhot_param, &yhot_param);
	zephir_get_arrval(&image, image_param);
	
            GLFWimage img;
            zval *w, *h, *pixels;
            unsigned char *buf = NULL;
            memset(&img, 0, sizeof(img));
            w = zend_hash_str_find(Z_ARRVAL_P(&image), "width", sizeof("width") - 1);
            h = zend_hash_str_find(Z_ARRVAL_P(&image), "height", sizeof("height") - 1);
            pixels = zend_hash_str_find(Z_ARRVAL_P(&image), "pixels", sizeof("pixels") - 1);
            img.width = w ? (int) zval_get_long(w) : 0;
            img.height = h ? (int) zval_get_long(h) : 0;
            if (pixels && Z_TYPE_P(pixels) == IS_STRING) {
                size_t need = (size_t) img.width * (size_t) img.height * 4;
                buf = emalloc(need ? need : 1);
                memcpy(buf, Z_STRVAL_P(pixels), Z_STRLEN_P(pixels) < need ? Z_STRLEN_P(pixels) : need);
                img.pixels = buf;
            }
            GLFWcursor *cursor = glfwCreateCursor(&img, (int) xhot, (int) yhot);
            ptr = (zend_long)(uintptr_t) cursor;
            if (buf) efree(buf);
        
	RETURN_MM_LONG(ptr);
}

PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwCreateStandardCursor)
{
	zval *shape_param = NULL;
	zend_long shape, ptr = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(shape)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &shape_param);
	
            ptr = (zend_long)(uintptr_t) glfwCreateStandardCursor((int) shape);
        
	RETURN_LONG(ptr);
}

PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwDestroyCursor)
{
	zval *cursor_param = NULL;
	zend_long cursor;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(cursor)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &cursor_param);
	
            glfwDestroyCursor((GLFWcursor *)(uintptr_t) cursor);
        
}

PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwSetCursor)
{
	zval *window_param = NULL, *cursor = NULL, cursor_sub, __$null;
	zend_long window;

	ZVAL_UNDEF(&cursor_sub);
	ZVAL_NULL(&__$null);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(cursor)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 1, &window_param, &cursor);
	if (!cursor) {
		cursor = &cursor_sub;
		cursor = &__$null;
	}
	
            GLFWcursor *c = NULL;
            if (Z_TYPE_P(cursor) != IS_NULL && Z_TYPE_P(cursor) != IS_UNDEF) {
                c = (GLFWcursor *)(uintptr_t) zval_get_long(cursor);
            }
            glfwSetCursor((GLFWwindow *)(uintptr_t) window, c);
        
}

PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwSetKeyCallback)
{
	zval *window_param = NULL, *callback = NULL, callback_sub, __$null;
	zend_long window;

	ZVAL_UNDEF(&callback_sub);
	ZVAL_NULL(&__$null);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(callback)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 1, &window_param, &callback);
	if (!callback) {
		callback = &callback_sub;
		callback = &__$null;
	}
	
            GLFWwindow *win = (GLFWwindow *)(uintptr_t) window;
            php_glfw_window_callback_set_field(win, "key", callback);
            glfwSetKeyCallback(win, (Z_TYPE_P(callback) == IS_NULL || Z_TYPE_P(callback) == IS_UNDEF) ? NULL : php_glfw_key_bridge);
        
}

PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwSetCharCallback)
{
	zval *window_param = NULL, *callback = NULL, callback_sub, __$null;
	zend_long window;

	ZVAL_UNDEF(&callback_sub);
	ZVAL_NULL(&__$null);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(callback)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 1, &window_param, &callback);
	if (!callback) {
		callback = &callback_sub;
		callback = &__$null;
	}
	
            GLFWwindow *win = (GLFWwindow *)(uintptr_t) window;
            php_glfw_window_callback_set_field(win, "character", callback);
            glfwSetCharCallback(win, (Z_TYPE_P(callback) == IS_NULL || Z_TYPE_P(callback) == IS_UNDEF) ? NULL : php_glfw_char_bridge);
        
}

PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwSetCharModsCallback)
{
	zval *window_param = NULL, *callback = NULL, callback_sub, __$null;
	zend_long window;

	ZVAL_UNDEF(&callback_sub);
	ZVAL_NULL(&__$null);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(callback)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 1, &window_param, &callback);
	if (!callback) {
		callback = &callback_sub;
		callback = &__$null;
	}
	
            GLFWwindow *win = (GLFWwindow *)(uintptr_t) window;
            php_glfw_window_callback_set_field(win, "charmods", callback);
            glfwSetCharModsCallback(win, (Z_TYPE_P(callback) == IS_NULL || Z_TYPE_P(callback) == IS_UNDEF) ? NULL : php_glfw_charmods_bridge);
        
}

PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwSetMouseButtonCallback)
{
	zval *window_param = NULL, *callback = NULL, callback_sub, __$null;
	zend_long window;

	ZVAL_UNDEF(&callback_sub);
	ZVAL_NULL(&__$null);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(callback)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 1, &window_param, &callback);
	if (!callback) {
		callback = &callback_sub;
		callback = &__$null;
	}
	
            GLFWwindow *win = (GLFWwindow *)(uintptr_t) window;
            php_glfw_window_callback_set_field(win, "mouse_button", callback);
            glfwSetMouseButtonCallback(win, (Z_TYPE_P(callback) == IS_NULL || Z_TYPE_P(callback) == IS_UNDEF) ? NULL : php_glfw_mousebutton_bridge);
        
}

PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwSetCursorPosCallback)
{
	zval *window_param = NULL, *callback = NULL, callback_sub, __$null;
	zend_long window;

	ZVAL_UNDEF(&callback_sub);
	ZVAL_NULL(&__$null);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(callback)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 1, &window_param, &callback);
	if (!callback) {
		callback = &callback_sub;
		callback = &__$null;
	}
	
            GLFWwindow *win = (GLFWwindow *)(uintptr_t) window;
            php_glfw_window_callback_set_field(win, "cursor_pos", callback);
            glfwSetCursorPosCallback(win, (Z_TYPE_P(callback) == IS_NULL || Z_TYPE_P(callback) == IS_UNDEF) ? NULL : php_glfw_cursorpos_bridge);
        
}

PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwSetCursorEnterCallback)
{
	zval *window_param = NULL, *callback = NULL, callback_sub, __$null;
	zend_long window;

	ZVAL_UNDEF(&callback_sub);
	ZVAL_NULL(&__$null);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(callback)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 1, &window_param, &callback);
	if (!callback) {
		callback = &callback_sub;
		callback = &__$null;
	}
	
            GLFWwindow *win = (GLFWwindow *)(uintptr_t) window;
            php_glfw_window_callback_set_field(win, "cursor_enter", callback);
            glfwSetCursorEnterCallback(win, (Z_TYPE_P(callback) == IS_NULL || Z_TYPE_P(callback) == IS_UNDEF) ? NULL : php_glfw_cursorenter_bridge);
        
}

PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwSetScrollCallback)
{
	zval *window_param = NULL, *callback = NULL, callback_sub, __$null;
	zend_long window;

	ZVAL_UNDEF(&callback_sub);
	ZVAL_NULL(&__$null);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(callback)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 1, &window_param, &callback);
	if (!callback) {
		callback = &callback_sub;
		callback = &__$null;
	}
	
            GLFWwindow *win = (GLFWwindow *)(uintptr_t) window;
            php_glfw_window_callback_set_field(win, "scroll", callback);
            glfwSetScrollCallback(win, (Z_TYPE_P(callback) == IS_NULL || Z_TYPE_P(callback) == IS_UNDEF) ? NULL : php_glfw_scroll_bridge);
        
}

PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwSetDropCallback)
{
	zval *window_param = NULL, *callback = NULL, callback_sub, __$null;
	zend_long window;

	ZVAL_UNDEF(&callback_sub);
	ZVAL_NULL(&__$null);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(callback)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 1, &window_param, &callback);
	if (!callback) {
		callback = &callback_sub;
		callback = &__$null;
	}
	
            GLFWwindow *win = (GLFWwindow *)(uintptr_t) window;
            php_glfw_window_callback_set_field(win, "drop", callback);
            glfwSetDropCallback(win, (Z_TYPE_P(callback) == IS_NULL || Z_TYPE_P(callback) == IS_UNDEF) ? NULL : php_glfw_drop_bridge);
        
}

PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwJoystickPresent)
{
	zend_bool result = 0;
	zval *jid_param = NULL;
	zend_long jid;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(jid)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &jid_param);
	
            result = glfwJoystickPresent((int) jid) == GLFW_TRUE;
        
	RETURN_BOOL(result);
}

PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwGetJoystickAxes)
{
	zval result;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *jid_param = NULL;
	zend_long jid;

	ZVAL_UNDEF(&result);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(jid)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &jid_param);
	ZEPHIR_INIT_VAR(&result);
	array_init(&result);
	
            int count = 0;
            const float *axes = glfwGetJoystickAxes((int) jid, &count);
            array_init(&result);
            if (axes && count > 0) {
                int i;
                for (i = 0; i < count; i++) {
                    add_next_index_double(&result, (double) axes[i]);
                }
            }
        
	RETURN_CTOR(&result);
}

PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwGetJoystickButtons)
{
	zval result;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *jid_param = NULL;
	zend_long jid;

	ZVAL_UNDEF(&result);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(jid)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &jid_param);
	ZEPHIR_INIT_VAR(&result);
	array_init(&result);
	
            int count = 0;
            const unsigned char *buttons = glfwGetJoystickButtons((int) jid, &count);
            array_init(&result);
            if (buttons && count > 0) {
                int i;
                for (i = 0; i < count; i++) {
                    add_next_index_long(&result, (zend_long) buttons[i]);
                }
            }
        
	RETURN_CTOR(&result);
}

PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwGetJoystickHats)
{
	zval result;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *jid_param = NULL;
	zend_long jid;

	ZVAL_UNDEF(&result);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(jid)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &jid_param);
	ZEPHIR_INIT_VAR(&result);
	array_init(&result);
	
            int count = 0;
            const unsigned char *hats = glfwGetJoystickHats((int) jid, &count);
            array_init(&result);
            if (hats && count > 0) {
                int i;
                for (i = 0; i < count; i++) {
                    add_next_index_long(&result, (zend_long) hats[i]);
                }
            }
        
	RETURN_CTOR(&result);
}

PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwGetJoystickName)
{
	zval result;
	zval *jid_param = NULL;
	zend_long jid;

	ZVAL_UNDEF(&result);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(jid)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &jid_param);
	
            const char *name = glfwGetJoystickName((int) jid);
            ZVAL_STRING(&result, name ? name : "");
        
	RETURN_CTORW(&result);
}

PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwGetJoystickGUID)
{
	zval result;
	zval *jid_param = NULL;
	zend_long jid;

	ZVAL_UNDEF(&result);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(jid)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &jid_param);
	
            const char *guid = glfwGetJoystickGUID((int) jid);
            ZVAL_STRING(&result, guid ? guid : "");
        
	RETURN_CTORW(&result);
}

PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwSetJoystickUserPointer)
{
	zval *jid_param = NULL, *pointer_param = NULL;
	zend_long jid, pointer;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(jid)
		Z_PARAM_LONG(pointer)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &jid_param, &pointer_param);
	
            glfwSetJoystickUserPointer((int) jid, (void *)(uintptr_t) pointer);
        
}

PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwGetJoystickUserPointer)
{
	zval *jid_param = NULL;
	zend_long jid, ptr = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(jid)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &jid_param);
	
            ptr = (zend_long)(uintptr_t) glfwGetJoystickUserPointer((int) jid);
        
	RETURN_LONG(ptr);
}

PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwJoystickIsGamepad)
{
	zend_bool result = 0;
	zval *jid_param = NULL;
	zend_long jid;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(jid)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &jid_param);
	
            result = glfwJoystickIsGamepad((int) jid) == GLFW_TRUE;
        
	RETURN_BOOL(result);
}

PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwSetJoystickCallback)
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
                if (php_glfw_joystick_callback_set) {
                    zval_ptr_dtor(&php_glfw_joystick_callback);
                    ZVAL_UNDEF(&php_glfw_joystick_callback);
                    php_glfw_joystick_callback_set = false;
                }
                glfwSetJoystickCallback(NULL);
            } else {
                if (php_glfw_joystick_callback_set) {
                    zval_ptr_dtor(&php_glfw_joystick_callback);
                }
                ZVAL_COPY(&php_glfw_joystick_callback, callback);
                php_glfw_joystick_callback_set = true;
                glfwSetJoystickCallback(php_glfw_joystick_callback_bridge);
            }
        
}

PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwUpdateGamepadMappings)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *mapping_param = NULL;
	zval mapping;

	ZVAL_UNDEF(&mapping);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(mapping)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &mapping_param);
	zephir_get_strval(&mapping, mapping_param);
	
            result = glfwUpdateGamepadMappings(Z_STRVAL(mapping)) == GLFW_TRUE;
        
	RETURN_MM_BOOL(result);
}

PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwGetGamepadName)
{
	zval result;
	zval *jid_param = NULL;
	zend_long jid;

	ZVAL_UNDEF(&result);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(jid)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &jid_param);
	
            const char *name = glfwGetGamepadName((int) jid);
            ZVAL_STRING(&result, name ? name : "");
        
	RETURN_CTORW(&result);
}

PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwGetGamepadState)
{
	zval result;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *jid_param = NULL;
	zend_long jid;

	ZVAL_UNDEF(&result);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(jid)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &jid_param);
	ZEPHIR_INIT_VAR(&result);
	array_init(&result);
	
            GLFWgamepadstate state;
            array_init(&result);
            if (glfwGetGamepadState((int) jid, &state) == GLFW_TRUE) {
                zval buttons, axes;
                int i;
                array_init(&buttons);
                array_init(&axes);
                for (i = 0; i < 15; i++) {
                    add_next_index_long(&buttons, (zend_long) state.buttons[i]);
                }
                for (i = 0; i < 6; i++) {
                    add_next_index_double(&axes, (double) state.axes[i]);
                }
                add_assoc_zval(&result, "buttons", &buttons);
                add_assoc_zval(&result, "axes", &axes);
            }
        
	RETURN_CTOR(&result);
}

PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwSetClipboardString)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval value;
	zval *window, window_sub, *value_param = NULL;

	ZVAL_UNDEF(&window_sub);
	ZVAL_UNDEF(&value);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_ZVAL(window)
		Z_PARAM_STR(value)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &window, &value_param);
	zephir_get_strval(&value, value_param);
	
            GLFWwindow *win = NULL;
            if (Z_TYPE_P(window) != IS_NULL && Z_TYPE_P(window) != IS_UNDEF) {
                win = (GLFWwindow *)(uintptr_t) zval_get_long(window);
            }
            glfwSetClipboardString(win, Z_STRVAL(value));
        
	ZEPHIR_MM_RESTORE();
}

PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwGetClipboardString)
{
	zval result;
	zval *window = NULL, window_sub, __$null;

	ZVAL_UNDEF(&window_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&result);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(0, 1, &window);
	if (!window) {
		window = &window_sub;
		window = &__$null;
	}
	
            GLFWwindow *win = NULL;
            if (Z_TYPE_P(window) != IS_NULL && Z_TYPE_P(window) != IS_UNDEF) {
                win = (GLFWwindow *)(uintptr_t) zval_get_long(window);
            }
            const char *s = glfwGetClipboardString(win);
            ZVAL_STRING(&result, s ? s : "");
        
	RETURN_CTORW(&result);
}

PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwGetTime)
{
	double result = 0;
	
            result = glfwGetTime();
        
	RETURN_DOUBLE(result);
}

PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwSetTime)
{
	zval *time_param = NULL;
	double time;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(time)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &time_param);
	time = zephir_get_doubleval(time_param);
	
            glfwSetTime(time);
        
}

PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwGetTimerValue)
{
	zend_long result = 0;
	
            result = (zend_long) glfwGetTimerValue();
        
	RETURN_LONG(result);
}

PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwGetTimerFrequency)
{
	zend_long result = 0;
	
            result = (zend_long) glfwGetTimerFrequency();
        
	RETURN_LONG(result);
}


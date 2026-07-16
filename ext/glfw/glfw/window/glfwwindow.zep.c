
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
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/exception.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/concat.h"
#include "kernel/array.h"

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct _php_glfw_window_callbacks {
    zval pos;
    zval size;
    zval close;
    zval refresh;
    zval focus;
    zval iconify;
    zval maximize;
    zval framebuffer_size;
    zval content_scale;
    zval key;
    zval character;
    zval charmods;
    zval mouse_button;
    zval cursor_pos;
    zval cursor_enter;
    zval scroll;
    zval drop;
} php_glfw_window_callbacks;

static HashTable php_glfw_window_cb_map;
static bool php_glfw_window_cb_map_ready = false;

static void php_glfw_window_cb_map_init(void)
{
    if (!php_glfw_window_cb_map_ready) {
        zend_hash_init(&php_glfw_window_cb_map, 8, NULL, NULL, 0);
        php_glfw_window_cb_map_ready = true;
    }
}

static php_glfw_window_callbacks *php_glfw_window_cb_get(GLFWwindow *window, int create)
{
    zend_long key;
    php_glfw_window_callbacks *ctx;
    zval *zv;

    if (!window) {
        return NULL;
    }
    php_glfw_window_cb_map_init();
    key = (zend_long)(uintptr_t) window;
    zv = zend_hash_index_find(&php_glfw_window_cb_map, (zend_ulong) key);
    if (zv) {
        return (php_glfw_window_callbacks *) Z_PTR_P(zv);
    }
    if (!create) {
        return NULL;
    }
    ctx = ecalloc(1, sizeof(php_glfw_window_callbacks));
    ZVAL_UNDEF(&ctx->pos); ZVAL_UNDEF(&ctx->size); ZVAL_UNDEF(&ctx->close);
    ZVAL_UNDEF(&ctx->refresh); ZVAL_UNDEF(&ctx->focus); ZVAL_UNDEF(&ctx->iconify);
    ZVAL_UNDEF(&ctx->maximize); ZVAL_UNDEF(&ctx->framebuffer_size);
    ZVAL_UNDEF(&ctx->content_scale); ZVAL_UNDEF(&ctx->key); ZVAL_UNDEF(&ctx->character);
    ZVAL_UNDEF(&ctx->charmods); ZVAL_UNDEF(&ctx->mouse_button); ZVAL_UNDEF(&ctx->cursor_pos);
    ZVAL_UNDEF(&ctx->cursor_enter); ZVAL_UNDEF(&ctx->scroll); ZVAL_UNDEF(&ctx->drop);
    zend_hash_index_update_ptr(&php_glfw_window_cb_map, (zend_ulong) key, ctx);
    return ctx;
}

static void php_glfw_window_cb_free_one(php_glfw_window_callbacks *ctx)
{
    if (!ctx) return;
#define PHP_GLFW_DTOR(f) do { if (!Z_ISUNDEF(ctx->f) && Z_TYPE(ctx->f) != IS_UNDEF) { zval_ptr_dtor(&ctx->f); ZVAL_UNDEF(&ctx->f); } } while (0)
    PHP_GLFW_DTOR(pos); PHP_GLFW_DTOR(size); PHP_GLFW_DTOR(close); PHP_GLFW_DTOR(refresh);
    PHP_GLFW_DTOR(focus); PHP_GLFW_DTOR(iconify); PHP_GLFW_DTOR(maximize);
    PHP_GLFW_DTOR(framebuffer_size); PHP_GLFW_DTOR(content_scale); PHP_GLFW_DTOR(key);
    PHP_GLFW_DTOR(character); PHP_GLFW_DTOR(charmods); PHP_GLFW_DTOR(mouse_button);
    PHP_GLFW_DTOR(cursor_pos); PHP_GLFW_DTOR(cursor_enter); PHP_GLFW_DTOR(scroll); PHP_GLFW_DTOR(drop);
#undef PHP_GLFW_DTOR
    efree(ctx);
}

static void php_glfw_window_cb_remove(GLFWwindow *window)
{
    zend_long key;
    php_glfw_window_callbacks *ctx;
    if (!window || !php_glfw_window_cb_map_ready) return;
    key = (zend_long)(uintptr_t) window;
    ctx = zend_hash_index_find_ptr(&php_glfw_window_cb_map, (zend_ulong) key);
    if (ctx) {
        php_glfw_window_cb_free_one(ctx);
        zend_hash_index_del(&php_glfw_window_cb_map, (zend_ulong) key);
    }
}

static void php_glfw_set_cb_field(zval *field, zval *callback)
{
    if (!Z_ISUNDEF_P(field) && Z_TYPE_P(field) != IS_UNDEF) {
        zval_ptr_dtor(field);
    }
    if (callback && Z_TYPE_P(callback) != IS_NULL && Z_TYPE_P(callback) != IS_UNDEF) {
        ZVAL_COPY(field, callback);
    } else {
        ZVAL_UNDEF(field);
    }
}

static void php_glfw_call1(zval *cb, zval *params, uint32_t n)
{
    zval retval;
    if (!cb || Z_ISUNDEF_P(cb) || Z_TYPE_P(cb) == IS_NULL) return;
    ZVAL_UNDEF(&retval);
    call_user_function(EG(function_table), NULL, cb, &retval, n, params);
    if (!Z_ISUNDEF(retval)) zval_ptr_dtor(&retval);
}

static void php_glfw_pos_bridge(GLFWwindow *w, int x, int y)
{
    php_glfw_window_callbacks *ctx = php_glfw_window_cb_get(w, 0);
    zval params[3];
    if (!ctx) return;
    ZVAL_LONG(&params[0], (zend_long)(uintptr_t) w);
    ZVAL_LONG(&params[1], x); ZVAL_LONG(&params[2], y);
    php_glfw_call1(&ctx->pos, params, 3);
}
static void php_glfw_size_bridge(GLFWwindow *w, int width, int height)
{
    php_glfw_window_callbacks *ctx = php_glfw_window_cb_get(w, 0);
    zval params[3];
    if (!ctx) return;
    ZVAL_LONG(&params[0], (zend_long)(uintptr_t) w);
    ZVAL_LONG(&params[1], width); ZVAL_LONG(&params[2], height);
    php_glfw_call1(&ctx->size, params, 3);
}
static void php_glfw_close_bridge(GLFWwindow *w)
{
    php_glfw_window_callbacks *ctx = php_glfw_window_cb_get(w, 0);
    zval params[1];
    if (!ctx) return;
    ZVAL_LONG(&params[0], (zend_long)(uintptr_t) w);
    php_glfw_call1(&ctx->close, params, 1);
}
static void php_glfw_refresh_bridge(GLFWwindow *w)
{
    php_glfw_window_callbacks *ctx = php_glfw_window_cb_get(w, 0);
    zval params[1];
    if (!ctx) return;
    ZVAL_LONG(&params[0], (zend_long)(uintptr_t) w);
    php_glfw_call1(&ctx->refresh, params, 1);
}
static void php_glfw_focus_bridge(GLFWwindow *w, int focused)
{
    php_glfw_window_callbacks *ctx = php_glfw_window_cb_get(w, 0);
    zval params[2];
    if (!ctx) return;
    ZVAL_LONG(&params[0], (zend_long)(uintptr_t) w);
    ZVAL_LONG(&params[1], focused);
    php_glfw_call1(&ctx->focus, params, 2);
}
static void php_glfw_iconify_bridge(GLFWwindow *w, int iconified)
{
    php_glfw_window_callbacks *ctx = php_glfw_window_cb_get(w, 0);
    zval params[2];
    if (!ctx) return;
    ZVAL_LONG(&params[0], (zend_long)(uintptr_t) w);
    ZVAL_LONG(&params[1], iconified);
    php_glfw_call1(&ctx->iconify, params, 2);
}
static void php_glfw_maximize_bridge(GLFWwindow *w, int maximized)
{
    php_glfw_window_callbacks *ctx = php_glfw_window_cb_get(w, 0);
    zval params[2];
    if (!ctx) return;
    ZVAL_LONG(&params[0], (zend_long)(uintptr_t) w);
    ZVAL_LONG(&params[1], maximized);
    php_glfw_call1(&ctx->maximize, params, 2);
}
static void php_glfw_fbsize_bridge(GLFWwindow *w, int width, int height)
{
    php_glfw_window_callbacks *ctx = php_glfw_window_cb_get(w, 0);
    zval params[3];
    if (!ctx) return;
    ZVAL_LONG(&params[0], (zend_long)(uintptr_t) w);
    ZVAL_LONG(&params[1], width); ZVAL_LONG(&params[2], height);
    php_glfw_call1(&ctx->framebuffer_size, params, 3);
}
static void php_glfw_contentscale_bridge(GLFWwindow *w, float xscale, float yscale)
{
    php_glfw_window_callbacks *ctx = php_glfw_window_cb_get(w, 0);
    zval params[3];
    if (!ctx) return;
    ZVAL_LONG(&params[0], (zend_long)(uintptr_t) w);
    ZVAL_DOUBLE(&params[1], (double) xscale);
    ZVAL_DOUBLE(&params[2], (double) yscale);
    php_glfw_call1(&ctx->content_scale, params, 3);
}

/* Input callbacks stored on same window ctx (set from GLFWInput) */
void php_glfw_key_bridge(GLFWwindow *w, int key, int scancode, int action, int mods)
{
    php_glfw_window_callbacks *ctx = php_glfw_window_cb_get(w, 0);
    zval params[5];
    if (!ctx) return;
    ZVAL_LONG(&params[0], (zend_long)(uintptr_t) w);
    ZVAL_LONG(&params[1], key); ZVAL_LONG(&params[2], scancode);
    ZVAL_LONG(&params[3], action); ZVAL_LONG(&params[4], mods);
    php_glfw_call1(&ctx->key, params, 5);
}
void php_glfw_char_bridge(GLFWwindow *w, unsigned int codepoint)
{
    php_glfw_window_callbacks *ctx = php_glfw_window_cb_get(w, 0);
    zval params[2];
    if (!ctx) return;
    ZVAL_LONG(&params[0], (zend_long)(uintptr_t) w);
    ZVAL_LONG(&params[1], (zend_long) codepoint);
    php_glfw_call1(&ctx->character, params, 2);
}
void php_glfw_charmods_bridge(GLFWwindow *w, unsigned int codepoint, int mods)
{
    php_glfw_window_callbacks *ctx = php_glfw_window_cb_get(w, 0);
    zval params[3];
    if (!ctx) return;
    ZVAL_LONG(&params[0], (zend_long)(uintptr_t) w);
    ZVAL_LONG(&params[1], (zend_long) codepoint);
    ZVAL_LONG(&params[2], mods);
    php_glfw_call1(&ctx->charmods, params, 3);
}
void php_glfw_mousebutton_bridge(GLFWwindow *w, int button, int action, int mods)
{
    php_glfw_window_callbacks *ctx = php_glfw_window_cb_get(w, 0);
    zval params[4];
    if (!ctx) return;
    ZVAL_LONG(&params[0], (zend_long)(uintptr_t) w);
    ZVAL_LONG(&params[1], button); ZVAL_LONG(&params[2], action); ZVAL_LONG(&params[3], mods);
    php_glfw_call1(&ctx->mouse_button, params, 4);
}
void php_glfw_cursorpos_bridge(GLFWwindow *w, double xpos, double ypos)
{
    php_glfw_window_callbacks *ctx = php_glfw_window_cb_get(w, 0);
    zval params[3];
    if (!ctx) return;
    ZVAL_LONG(&params[0], (zend_long)(uintptr_t) w);
    ZVAL_DOUBLE(&params[1], xpos); ZVAL_DOUBLE(&params[2], ypos);
    php_glfw_call1(&ctx->cursor_pos, params, 3);
}
void php_glfw_cursorenter_bridge(GLFWwindow *w, int entered)
{
    php_glfw_window_callbacks *ctx = php_glfw_window_cb_get(w, 0);
    zval params[2];
    if (!ctx) return;
    ZVAL_LONG(&params[0], (zend_long)(uintptr_t) w);
    ZVAL_LONG(&params[1], entered);
    php_glfw_call1(&ctx->cursor_enter, params, 2);
}
void php_glfw_scroll_bridge(GLFWwindow *w, double xoffset, double yoffset)
{
    php_glfw_window_callbacks *ctx = php_glfw_window_cb_get(w, 0);
    zval params[3];
    if (!ctx) return;
    ZVAL_LONG(&params[0], (zend_long)(uintptr_t) w);
    ZVAL_DOUBLE(&params[1], xoffset); ZVAL_DOUBLE(&params[2], yoffset);
    php_glfw_call1(&ctx->scroll, params, 3);
}
void php_glfw_drop_bridge(GLFWwindow *w, int count, const char **paths)
{
    php_glfw_window_callbacks *ctx = php_glfw_window_cb_get(w, 0);
    zval params[2];
    zval path_arr;
    int i;
    if (!ctx) return;
    ZVAL_LONG(&params[0], (zend_long)(uintptr_t) w);
    array_init(&path_arr);
    for (i = 0; i < count; i++) {
        add_next_index_string(&path_arr, paths[i] ? paths[i] : "");
    }
    ZVAL_COPY_VALUE(&params[1], &path_arr);
    php_glfw_call1(&ctx->drop, params, 2);
    zval_ptr_dtor(&params[1]);
}

/* Exported helpers for GLFWInput */
php_glfw_window_callbacks *php_glfw_window_callbacks_ensure(GLFWwindow *window)
{
    return php_glfw_window_cb_get(window, 1);
}
void php_glfw_window_callback_set_field(GLFWwindow *window, const char *name, zval *callback)
{
    php_glfw_window_callbacks *ctx = php_glfw_window_cb_get(window, 1);
    if (!ctx) return;
    if (strcmp(name, "key") == 0) php_glfw_set_cb_field(&ctx->key, callback);
    else if (strcmp(name, "character") == 0) php_glfw_set_cb_field(&ctx->character, callback);
    else if (strcmp(name, "charmods") == 0) php_glfw_set_cb_field(&ctx->charmods, callback);
    else if (strcmp(name, "mouse_button") == 0) php_glfw_set_cb_field(&ctx->mouse_button, callback);
    else if (strcmp(name, "cursor_pos") == 0) php_glfw_set_cb_field(&ctx->cursor_pos, callback);
    else if (strcmp(name, "cursor_enter") == 0) php_glfw_set_cb_field(&ctx->cursor_enter, callback);
    else if (strcmp(name, "scroll") == 0) php_glfw_set_cb_field(&ctx->scroll, callback);
    else if (strcmp(name, "drop") == 0) php_glfw_set_cb_field(&ctx->drop, callback);
}



/**
 * GLFW window creation, attributes, and event loop.
 */
ZEPHIR_INIT_CLASS(Glfw_GLFW_Window_GLFWWindow)
{
	ZEPHIR_REGISTER_CLASS(Glfw\\GLFW\\Window, GLFWWindow, glfw, glfw_window_glfwwindow, glfw_glfw_window_glfwwindow_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwDefaultWindowHints)
{

	
            glfwDefaultWindowHints();
        
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwWindowHint)
{
	zval *hint_param = NULL, *value_param = NULL;
	zend_long hint, value;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(hint)
		Z_PARAM_LONG(value)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &hint_param, &value_param);
	
            glfwWindowHint((int) hint, (int) value);
        
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwWindowHintString)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval value;
	zval *hint_param = NULL, *value_param = NULL;
	zend_long hint;

	ZVAL_UNDEF(&value);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(hint)
		Z_PARAM_STR(value)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &hint_param, &value_param);
	zephir_get_strval(&value, value_param);
	
            glfwWindowHintString((int) hint, Z_STRVAL(value));
        
	ZEPHIR_MM_RESTORE();
}

/**
 * @param int|null monitor Fullscreen monitor handle, or null
 * @param int|null share Context-share window handle, or null
 */
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwCreateWindow)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval title;
	zval *width_param = NULL, *height_param = NULL, *title_param = NULL, *monitor = NULL, monitor_sub, *share = NULL, share_sub, __$null, err$$3, _0$$3, _1$$3, _2$$3;
	zend_long width, height, ZEPHIR_LAST_CALL_STATUS, ptr = 0;

	ZVAL_UNDEF(&monitor_sub);
	ZVAL_UNDEF(&share_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&err$$3);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&title);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(3, 5)
		Z_PARAM_LONG(width)
		Z_PARAM_LONG(height)
		Z_PARAM_STR(title)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(monitor)
		Z_PARAM_ZVAL_OR_NULL(share)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 2, &width_param, &height_param, &title_param, &monitor, &share);
	zephir_get_strval(&title, title_param);
	if (!monitor) {
		monitor = &monitor_sub;
		monitor = &__$null;
	}
	if (!share) {
		share = &share_sub;
		share = &__$null;
	}
	
            GLFWmonitor *mon = NULL;
            GLFWwindow *shr = NULL;
            if (Z_TYPE_P(monitor) != IS_NULL && Z_TYPE_P(monitor) != IS_UNDEF) {
                mon = (GLFWmonitor *)(uintptr_t) zval_get_long(monitor);
            }
            if (Z_TYPE_P(share) != IS_NULL && Z_TYPE_P(share) != IS_UNDEF) {
                shr = (GLFWwindow *)(uintptr_t) zval_get_long(share);
            }
            GLFWwindow *window = glfwCreateWindow((int) width, (int) height, Z_STRVAL(title), mon, shr);
            ptr = (zend_long)(uintptr_t) window;
            if (window) {
                php_glfw_window_cb_get(window, 1);
            }
        
	if (ptr == 0) {
		ZEPHIR_CALL_CE_STATIC(&err$$3, glfw_glfw_glfwerror_ce, "glfwgeterror", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_RuntimeException);
		zephir_array_fetch_string(&_1$$3, &err$$3, SL("description"), PH_NOISY | PH_READONLY, "glfw/glfw/window/glfwwindow.zep", 353);
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "glfwCreateWindow failed: ", &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 1, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "glfw/glfw/window/glfwwindow.zep", 353);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM_LONG(ptr);
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwDestroyWindow)
{
	zval *window_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            GLFWwindow *win = (GLFWwindow *)(uintptr_t) window;
            php_glfw_window_cb_remove(win);
            glfwDestroyWindow(win);
        
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwWindowShouldClose)
{
	zend_bool result = 0;
	zval *window_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            result = glfwWindowShouldClose((GLFWwindow *)(uintptr_t) window) != 0;
        
	RETURN_BOOL(result);
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowShouldClose)
{
	zval *window_param = NULL, *value_param = NULL;
	zend_long window, value;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_LONG(value)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &window_param, &value_param);
	
            glfwSetWindowShouldClose((GLFWwindow *)(uintptr_t) window, (int) value);
        
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwGetWindowTitle)
{
	zval result;
	zval *window_param = NULL;
	zend_long window;

	ZVAL_UNDEF(&result);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            const char *t = glfwGetWindowTitle((GLFWwindow *)(uintptr_t) window);
            ZVAL_STRING(&result, t ? t : "");
        
	RETURN_CTORW(&result);
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowTitle)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval title;
	zval *window_param = NULL, *title_param = NULL;
	zend_long window;

	ZVAL_UNDEF(&title);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_STR(title)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &window_param, &title_param);
	zephir_get_strval(&title, title_param);
	
            glfwSetWindowTitle((GLFWwindow *)(uintptr_t) window, Z_STRVAL(title));
        
	ZEPHIR_MM_RESTORE();
}

/**
 * @param array images list of ["width"=>int,"height"=>int,"pixels"=>string]
 */
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowIcon)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval images;
	zval *window_param = NULL, *images_param = NULL;
	zend_long window;

	ZVAL_UNDEF(&images);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_ARRAY(images)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &window_param, &images_param);
	zephir_get_arrval(&images, images_param);
	
            uint32_t count = zend_hash_num_elements(Z_ARRVAL_P(&images));
            GLFWimage *imgs = NULL;
            unsigned char **bufs = NULL;
            uint32_t i = 0;
            HashPosition pos;
            zval *entry;

            if (count == 0) {
                glfwSetWindowIcon((GLFWwindow *)(uintptr_t) window, 0, NULL);
                return;
            }

            imgs = ecalloc(count, sizeof(GLFWimage));
            bufs = ecalloc(count, sizeof(unsigned char *));

            ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&images), entry) {
                zval *w, *h, *pixels;
                if (Z_TYPE_P(entry) != IS_ARRAY || i >= count) {
                    continue;
                }
                w = zend_hash_str_find(Z_ARRVAL_P(entry), "width", sizeof("width") - 1);
                h = zend_hash_str_find(Z_ARRVAL_P(entry), "height", sizeof("height") - 1);
                pixels = zend_hash_str_find(Z_ARRVAL_P(entry), "pixels", sizeof("pixels") - 1);
                imgs[i].width = w ? (int) zval_get_long(w) : 0;
                imgs[i].height = h ? (int) zval_get_long(h) : 0;
                if (pixels && Z_TYPE_P(pixels) == IS_STRING) {
                    size_t need = (size_t) imgs[i].width * (size_t) imgs[i].height * 4;
                    bufs[i] = emalloc(need ? need : 1);
                    memcpy(bufs[i], Z_STRVAL_P(pixels), Z_STRLEN_P(pixels) < need ? Z_STRLEN_P(pixels) : need);
                    imgs[i].pixels = bufs[i];
                } else {
                    imgs[i].pixels = NULL;
                }
                i++;
            } ZEND_HASH_FOREACH_END();

            glfwSetWindowIcon((GLFWwindow *)(uintptr_t) window, (int) i, imgs);

            for (i = 0; i < count; i++) {
                if (bufs[i]) efree(bufs[i]);
            }
            efree(bufs);
            efree(imgs);
        
	ZEPHIR_MM_RESTORE();
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwGetWindowPos)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *window_param = NULL, _0;
	zend_long window, xpos = 0, ypos = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &window_param);
	
            int x = 0, y = 0;
            glfwGetWindowPos((GLFWwindow *)(uintptr_t) window, &x, &y);
            xpos = (zend_long) x; ypos = (zend_long) y;
        
	zephir_create_array(return_value, 2, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, xpos);
	zephir_array_update_string(return_value, SL("xpos"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, ypos);
	zephir_array_update_string(return_value, SL("ypos"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowPos)
{
	zval *window_param = NULL, *xpos_param = NULL, *ypos_param = NULL;
	zend_long window, xpos, ypos;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(window)
		Z_PARAM_LONG(xpos)
		Z_PARAM_LONG(ypos)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &window_param, &xpos_param, &ypos_param);
	
            glfwSetWindowPos((GLFWwindow *)(uintptr_t) window, (int) xpos, (int) ypos);
        
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwGetWindowSize)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *window_param = NULL, _0;
	zend_long window, width = 0, height = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &window_param);
	
            int w = 0, h = 0;
            glfwGetWindowSize((GLFWwindow *)(uintptr_t) window, &w, &h);
            width = (zend_long) w; height = (zend_long) h;
        
	zephir_create_array(return_value, 2, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, width);
	zephir_array_update_string(return_value, SL("width"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, height);
	zephir_array_update_string(return_value, SL("height"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowSizeLimits)
{
	zval *window_param = NULL, *minwidth_param = NULL, *minheight_param = NULL, *maxwidth_param = NULL, *maxheight_param = NULL;
	zend_long window, minwidth, minheight, maxwidth, maxheight;

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_LONG(window)
		Z_PARAM_LONG(minwidth)
		Z_PARAM_LONG(minheight)
		Z_PARAM_LONG(maxwidth)
		Z_PARAM_LONG(maxheight)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(5, 0, &window_param, &minwidth_param, &minheight_param, &maxwidth_param, &maxheight_param);
	
            glfwSetWindowSizeLimits((GLFWwindow *)(uintptr_t) window, (int) minwidth, (int) minheight, (int) maxwidth, (int) maxheight);
        
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowAspectRatio)
{
	zval *window_param = NULL, *numer_param = NULL, *denom_param = NULL;
	zend_long window, numer, denom;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(window)
		Z_PARAM_LONG(numer)
		Z_PARAM_LONG(denom)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &window_param, &numer_param, &denom_param);
	
            glfwSetWindowAspectRatio((GLFWwindow *)(uintptr_t) window, (int) numer, (int) denom);
        
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowSize)
{
	zval *window_param = NULL, *width_param = NULL, *height_param = NULL;
	zend_long window, width, height;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(window)
		Z_PARAM_LONG(width)
		Z_PARAM_LONG(height)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &window_param, &width_param, &height_param);
	
            glfwSetWindowSize((GLFWwindow *)(uintptr_t) window, (int) width, (int) height);
        
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwGetFramebufferSize)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *window_param = NULL, _0;
	zend_long window, width = 0, height = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &window_param);
	
            int w = 0, h = 0;
            glfwGetFramebufferSize((GLFWwindow *)(uintptr_t) window, &w, &h);
            width = (zend_long) w; height = (zend_long) h;
        
	zephir_create_array(return_value, 2, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, width);
	zephir_array_update_string(return_value, SL("width"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, height);
	zephir_array_update_string(return_value, SL("height"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwGetWindowFrameSize)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *window_param = NULL, _0;
	zend_long window, left = 0, top = 0, right = 0, bottom = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &window_param);
	
            int l = 0, t = 0, r = 0, b = 0;
            glfwGetWindowFrameSize((GLFWwindow *)(uintptr_t) window, &l, &t, &r, &b);
            left = (zend_long) l; top = (zend_long) t; right = (zend_long) r; bottom = (zend_long) b;
        
	zephir_create_array(return_value, 4, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, left);
	zephir_array_update_string(return_value, SL("left"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, top);
	zephir_array_update_string(return_value, SL("top"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, right);
	zephir_array_update_string(return_value, SL("right"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, bottom);
	zephir_array_update_string(return_value, SL("bottom"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwGetWindowContentScale)
{
	double xscale = 0, yscale = 0;
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
	
            float xs = 0.0f, ys = 0.0f;
            glfwGetWindowContentScale((GLFWwindow *)(uintptr_t) window, &xs, &ys);
            xscale = (double) xs; yscale = (double) ys;
        
	zephir_create_array(return_value, 2, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_DOUBLE(&_0, xscale);
	zephir_array_update_string(return_value, SL("xscale"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_DOUBLE(&_0, yscale);
	zephir_array_update_string(return_value, SL("yscale"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwGetWindowOpacity)
{
	double result = 0;
	zval *window_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            result = (double) glfwGetWindowOpacity((GLFWwindow *)(uintptr_t) window);
        
	RETURN_DOUBLE(result);
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowOpacity)
{
	double opacity;
	zval *window_param = NULL, *opacity_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_ZVAL(opacity)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &window_param, &opacity_param);
	opacity = zephir_get_doubleval(opacity_param);
	
            glfwSetWindowOpacity((GLFWwindow *)(uintptr_t) window, (float) opacity);
        
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwIconifyWindow)
{
	zval *window_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	 glfwIconifyWindow((GLFWwindow *)(uintptr_t) window); 
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwRestoreWindow)
{
	zval *window_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	 glfwRestoreWindow((GLFWwindow *)(uintptr_t) window); 
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwMaximizeWindow)
{
	zval *window_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	 glfwMaximizeWindow((GLFWwindow *)(uintptr_t) window); 
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwShowWindow)
{
	zval *window_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	 glfwShowWindow((GLFWwindow *)(uintptr_t) window); 
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwHideWindow)
{
	zval *window_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	 glfwHideWindow((GLFWwindow *)(uintptr_t) window); 
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwFocusWindow)
{
	zval *window_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	 glfwFocusWindow((GLFWwindow *)(uintptr_t) window); 
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwRequestWindowAttention)
{
	zval *window_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	 glfwRequestWindowAttention((GLFWwindow *)(uintptr_t) window); 
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwGetWindowMonitor)
{
	zval *window_param = NULL;
	zend_long window, ptr = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            ptr = (zend_long)(uintptr_t) glfwGetWindowMonitor((GLFWwindow *)(uintptr_t) window);
        
	RETURN_LONG(ptr);
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowMonitor)
{
	zval *window_param = NULL, *monitor, monitor_sub, *xpos_param = NULL, *ypos_param = NULL, *width_param = NULL, *height_param = NULL, *refreshRate_param = NULL;
	zend_long window, xpos, ypos, width, height, refreshRate;

	ZVAL_UNDEF(&monitor_sub);
	ZEND_PARSE_PARAMETERS_START(7, 7)
		Z_PARAM_LONG(window)
		Z_PARAM_ZVAL(monitor)
		Z_PARAM_LONG(xpos)
		Z_PARAM_LONG(ypos)
		Z_PARAM_LONG(width)
		Z_PARAM_LONG(height)
		Z_PARAM_LONG(refreshRate)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(7, 0, &window_param, &monitor, &xpos_param, &ypos_param, &width_param, &height_param, &refreshRate_param);
	
            GLFWmonitor *mon = NULL;
            if (Z_TYPE_P(monitor) != IS_NULL && Z_TYPE_P(monitor) != IS_UNDEF) {
                mon = (GLFWmonitor *)(uintptr_t) zval_get_long(monitor);
            }
            glfwSetWindowMonitor((GLFWwindow *)(uintptr_t) window, mon, (int) xpos, (int) ypos, (int) width, (int) height, (int) refreshRate);
        
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwGetWindowAttrib)
{
	zval *window_param = NULL, *attrib_param = NULL;
	zend_long window, attrib, result = 0;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_LONG(attrib)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &window_param, &attrib_param);
	
            result = (zend_long) glfwGetWindowAttrib((GLFWwindow *)(uintptr_t) window, (int) attrib);
        
	RETURN_LONG(result);
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowAttrib)
{
	zval *window_param = NULL, *attrib_param = NULL, *value_param = NULL;
	zend_long window, attrib, value;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(window)
		Z_PARAM_LONG(attrib)
		Z_PARAM_LONG(value)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &window_param, &attrib_param, &value_param);
	
            glfwSetWindowAttrib((GLFWwindow *)(uintptr_t) window, (int) attrib, (int) value);
        
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowUserPointer)
{
	zval *window_param = NULL, *pointer_param = NULL;
	zend_long window, pointer;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_LONG(pointer)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &window_param, &pointer_param);
	
            glfwSetWindowUserPointer((GLFWwindow *)(uintptr_t) window, (void *)(uintptr_t) pointer);
        
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwGetWindowUserPointer)
{
	zval *window_param = NULL;
	zend_long window, ptr = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            ptr = (zend_long)(uintptr_t) glfwGetWindowUserPointer((GLFWwindow *)(uintptr_t) window);
        
	RETURN_LONG(ptr);
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowPosCallback)
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
            php_glfw_window_callbacks *ctx = php_glfw_window_cb_get(win, 1);
            if (ctx) {
                php_glfw_set_cb_field(&ctx->pos, callback);
                glfwSetWindowPosCallback(win, (Z_TYPE_P(callback) == IS_NULL || Z_TYPE_P(callback) == IS_UNDEF) ? NULL : php_glfw_pos_bridge);
            }
        
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowSizeCallback)
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
            php_glfw_window_callbacks *ctx = php_glfw_window_cb_get(win, 1);
            if (ctx) {
                php_glfw_set_cb_field(&ctx->size, callback);
                glfwSetWindowSizeCallback(win, (Z_TYPE_P(callback) == IS_NULL || Z_TYPE_P(callback) == IS_UNDEF) ? NULL : php_glfw_size_bridge);
            }
        
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowCloseCallback)
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
            php_glfw_window_callbacks *ctx = php_glfw_window_cb_get(win, 1);
            if (ctx) {
                php_glfw_set_cb_field(&ctx->close, callback);
                glfwSetWindowCloseCallback(win, (Z_TYPE_P(callback) == IS_NULL || Z_TYPE_P(callback) == IS_UNDEF) ? NULL : php_glfw_close_bridge);
            }
        
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowRefreshCallback)
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
            php_glfw_window_callbacks *ctx = php_glfw_window_cb_get(win, 1);
            if (ctx) {
                php_glfw_set_cb_field(&ctx->refresh, callback);
                glfwSetWindowRefreshCallback(win, (Z_TYPE_P(callback) == IS_NULL || Z_TYPE_P(callback) == IS_UNDEF) ? NULL : php_glfw_refresh_bridge);
            }
        
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowFocusCallback)
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
            php_glfw_window_callbacks *ctx = php_glfw_window_cb_get(win, 1);
            if (ctx) {
                php_glfw_set_cb_field(&ctx->focus, callback);
                glfwSetWindowFocusCallback(win, (Z_TYPE_P(callback) == IS_NULL || Z_TYPE_P(callback) == IS_UNDEF) ? NULL : php_glfw_focus_bridge);
            }
        
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowIconifyCallback)
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
            php_glfw_window_callbacks *ctx = php_glfw_window_cb_get(win, 1);
            if (ctx) {
                php_glfw_set_cb_field(&ctx->iconify, callback);
                glfwSetWindowIconifyCallback(win, (Z_TYPE_P(callback) == IS_NULL || Z_TYPE_P(callback) == IS_UNDEF) ? NULL : php_glfw_iconify_bridge);
            }
        
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowMaximizeCallback)
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
            php_glfw_window_callbacks *ctx = php_glfw_window_cb_get(win, 1);
            if (ctx) {
                php_glfw_set_cb_field(&ctx->maximize, callback);
                glfwSetWindowMaximizeCallback(win, (Z_TYPE_P(callback) == IS_NULL || Z_TYPE_P(callback) == IS_UNDEF) ? NULL : php_glfw_maximize_bridge);
            }
        
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwSetFramebufferSizeCallback)
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
            php_glfw_window_callbacks *ctx = php_glfw_window_cb_get(win, 1);
            if (ctx) {
                php_glfw_set_cb_field(&ctx->framebuffer_size, callback);
                glfwSetFramebufferSizeCallback(win, (Z_TYPE_P(callback) == IS_NULL || Z_TYPE_P(callback) == IS_UNDEF) ? NULL : php_glfw_fbsize_bridge);
            }
        
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowContentScaleCallback)
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
            php_glfw_window_callbacks *ctx = php_glfw_window_cb_get(win, 1);
            if (ctx) {
                php_glfw_set_cb_field(&ctx->content_scale, callback);
                glfwSetWindowContentScaleCallback(win, (Z_TYPE_P(callback) == IS_NULL || Z_TYPE_P(callback) == IS_UNDEF) ? NULL : php_glfw_contentscale_bridge);
            }
        
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwPollEvents)
{

	 glfwPollEvents(); 
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwWaitEvents)
{

	 glfwWaitEvents(); 
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwWaitEventsTimeout)
{
	zval *timeout_param = NULL;
	double timeout;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(timeout)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &timeout_param);
	timeout = zephir_get_doubleval(timeout_param);
	 glfwWaitEventsTimeout(timeout); 
}

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwPostEmptyEvent)
{

	 glfwPostEmptyEvent(); 
}


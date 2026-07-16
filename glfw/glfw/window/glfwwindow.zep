namespace Glfw\GLFW\Window;

%{
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
}%

/**
 * GLFW window creation, attributes, and event loop.
 */
class GLFWWindow
{

    public static function glfwDefaultWindowHints() -> void
    {
        %{
            glfwDefaultWindowHints();
        }%
    }

    public static function glfwWindowHint(int hint, int value) -> void
    {
        %{
            glfwWindowHint((int) hint, (int) value);
        }%
    }

    public static function glfwWindowHintString(int hint, string value) -> void
    {
        %{
            glfwWindowHintString((int) hint, Z_STRVAL(value));
        }%
    }

    /**
     * @param int|null monitor Fullscreen monitor handle, or null
     * @param int|null share Context-share window handle, or null
     */
    public static function glfwCreateWindow(int width, int height, string title, var monitor = null, var share = null) -> int
    {
        int ptr;

        %{
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
        }%

        if ptr == 0 {
            var err;
            let err = \Glfw\GLFW\GLFWError::glfwGetError();
            throw new \RuntimeException("glfwCreateWindow failed: " . err["description"]);
        }

        return ptr;
    }

    public static function glfwDestroyWindow(int window) -> void
    {
        %{
            GLFWwindow *win = (GLFWwindow *)(uintptr_t) window;
            php_glfw_window_cb_remove(win);
            glfwDestroyWindow(win);
        }%
    }

    public static function glfwWindowShouldClose(int window) -> bool
    {
        bool result;
        %{
            result = glfwWindowShouldClose((GLFWwindow *)(uintptr_t) window) != 0;
        }%
        return result;
    }

    public static function glfwSetWindowShouldClose(int window, int value) -> void
    {
        %{
            glfwSetWindowShouldClose((GLFWwindow *)(uintptr_t) window, (int) value);
        }%
    }

    public static function glfwGetWindowTitle(int window) -> string
    {
        string result;
        %{
            const char *t = glfwGetWindowTitle((GLFWwindow *)(uintptr_t) window);
            ZVAL_STRING(&result, t ? t : "");
        }%
        return result;
    }

    public static function glfwSetWindowTitle(int window, string title) -> void
    {
        %{
            glfwSetWindowTitle((GLFWwindow *)(uintptr_t) window, Z_STRVAL(title));
        }%
    }

    /**
     * @param array images list of ["width"=>int,"height"=>int,"pixels"=>string]
     */
    public static function glfwSetWindowIcon(int window, array images) -> void
    {
        %{
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
        }%
    }

    public static function glfwGetWindowPos(int window) -> array
    {
        int xpos; int ypos;
        %{
            int x = 0, y = 0;
            glfwGetWindowPos((GLFWwindow *)(uintptr_t) window, &x, &y);
            xpos = (zend_long) x; ypos = (zend_long) y;
        }%
        return ["xpos": xpos, "ypos": ypos];
    }

    public static function glfwSetWindowPos(int window, int xpos, int ypos) -> void
    {
        %{
            glfwSetWindowPos((GLFWwindow *)(uintptr_t) window, (int) xpos, (int) ypos);
        }%
    }

    public static function glfwGetWindowSize(int window) -> array
    {
        int width; int height;
        %{
            int w = 0, h = 0;
            glfwGetWindowSize((GLFWwindow *)(uintptr_t) window, &w, &h);
            width = (zend_long) w; height = (zend_long) h;
        }%
        return ["width": width, "height": height];
    }

    public static function glfwSetWindowSizeLimits(int window, int minwidth, int minheight, int maxwidth, int maxheight) -> void
    {
        %{
            glfwSetWindowSizeLimits((GLFWwindow *)(uintptr_t) window, (int) minwidth, (int) minheight, (int) maxwidth, (int) maxheight);
        }%
    }

    public static function glfwSetWindowAspectRatio(int window, int numer, int denom) -> void
    {
        %{
            glfwSetWindowAspectRatio((GLFWwindow *)(uintptr_t) window, (int) numer, (int) denom);
        }%
    }

    public static function glfwSetWindowSize(int window, int width, int height) -> void
    {
        %{
            glfwSetWindowSize((GLFWwindow *)(uintptr_t) window, (int) width, (int) height);
        }%
    }

    public static function glfwGetFramebufferSize(int window) -> array
    {
        int width; int height;
        %{
            int w = 0, h = 0;
            glfwGetFramebufferSize((GLFWwindow *)(uintptr_t) window, &w, &h);
            width = (zend_long) w; height = (zend_long) h;
        }%
        return ["width": width, "height": height];
    }

    public static function glfwGetWindowFrameSize(int window) -> array
    {
        int left; int top; int right; int bottom;
        %{
            int l = 0, t = 0, r = 0, b = 0;
            glfwGetWindowFrameSize((GLFWwindow *)(uintptr_t) window, &l, &t, &r, &b);
            left = (zend_long) l; top = (zend_long) t; right = (zend_long) r; bottom = (zend_long) b;
        }%
        return ["left": left, "top": top, "right": right, "bottom": bottom];
    }

    public static function glfwGetWindowContentScale(int window) -> array
    {
        double xscale; double yscale;
        %{
            float xs = 0.0f, ys = 0.0f;
            glfwGetWindowContentScale((GLFWwindow *)(uintptr_t) window, &xs, &ys);
            xscale = (double) xs; yscale = (double) ys;
        }%
        return ["xscale": xscale, "yscale": yscale];
    }

    public static function glfwGetWindowOpacity(int window) -> float
    {
        float result;
        %{
            result = (double) glfwGetWindowOpacity((GLFWwindow *)(uintptr_t) window);
        }%
        return result;
    }

    public static function glfwSetWindowOpacity(int window, float opacity) -> void
    {
        %{
            glfwSetWindowOpacity((GLFWwindow *)(uintptr_t) window, (float) opacity);
        }%
    }

    public static function glfwIconifyWindow(int window) -> void
    {
        %{ glfwIconifyWindow((GLFWwindow *)(uintptr_t) window); }%
    }

    public static function glfwRestoreWindow(int window) -> void
    {
        %{ glfwRestoreWindow((GLFWwindow *)(uintptr_t) window); }%
    }

    public static function glfwMaximizeWindow(int window) -> void
    {
        %{ glfwMaximizeWindow((GLFWwindow *)(uintptr_t) window); }%
    }

    public static function glfwShowWindow(int window) -> void
    {
        %{ glfwShowWindow((GLFWwindow *)(uintptr_t) window); }%
    }

    public static function glfwHideWindow(int window) -> void
    {
        %{ glfwHideWindow((GLFWwindow *)(uintptr_t) window); }%
    }

    public static function glfwFocusWindow(int window) -> void
    {
        %{ glfwFocusWindow((GLFWwindow *)(uintptr_t) window); }%
    }

    public static function glfwRequestWindowAttention(int window) -> void
    {
        %{ glfwRequestWindowAttention((GLFWwindow *)(uintptr_t) window); }%
    }

    public static function glfwGetWindowMonitor(int window) -> int
    {
        int ptr;
        %{
            ptr = (zend_long)(uintptr_t) glfwGetWindowMonitor((GLFWwindow *)(uintptr_t) window);
        }%
        return ptr;
    }

    public static function glfwSetWindowMonitor(int window, var monitor, int xpos, int ypos, int width, int height, int refreshRate) -> void
    {
        %{
            GLFWmonitor *mon = NULL;
            if (Z_TYPE_P(monitor) != IS_NULL && Z_TYPE_P(monitor) != IS_UNDEF) {
                mon = (GLFWmonitor *)(uintptr_t) zval_get_long(monitor);
            }
            glfwSetWindowMonitor((GLFWwindow *)(uintptr_t) window, mon, (int) xpos, (int) ypos, (int) width, (int) height, (int) refreshRate);
        }%
    }

    public static function glfwGetWindowAttrib(int window, int attrib) -> int
    {
        int result;
        %{
            result = (zend_long) glfwGetWindowAttrib((GLFWwindow *)(uintptr_t) window, (int) attrib);
        }%
        return result;
    }

    public static function glfwSetWindowAttrib(int window, int attrib, int value) -> void
    {
        %{
            glfwSetWindowAttrib((GLFWwindow *)(uintptr_t) window, (int) attrib, (int) value);
        }%
    }

    public static function glfwSetWindowUserPointer(int window, int pointer) -> void
    {
        %{
            glfwSetWindowUserPointer((GLFWwindow *)(uintptr_t) window, (void *)(uintptr_t) pointer);
        }%
    }

    public static function glfwGetWindowUserPointer(int window) -> int
    {
        int ptr;
        %{
            ptr = (zend_long)(uintptr_t) glfwGetWindowUserPointer((GLFWwindow *)(uintptr_t) window);
        }%
        return ptr;
    }

    public static function glfwSetWindowPosCallback(int window, var callback = null) -> void
    {
        %{
            GLFWwindow *win = (GLFWwindow *)(uintptr_t) window;
            php_glfw_window_callbacks *ctx = php_glfw_window_cb_get(win, 1);
            if (ctx) {
                php_glfw_set_cb_field(&ctx->pos, callback);
                glfwSetWindowPosCallback(win, (Z_TYPE_P(callback) == IS_NULL || Z_TYPE_P(callback) == IS_UNDEF) ? NULL : php_glfw_pos_bridge);
            }
        }%
    }

    public static function glfwSetWindowSizeCallback(int window, var callback = null) -> void
    {
        %{
            GLFWwindow *win = (GLFWwindow *)(uintptr_t) window;
            php_glfw_window_callbacks *ctx = php_glfw_window_cb_get(win, 1);
            if (ctx) {
                php_glfw_set_cb_field(&ctx->size, callback);
                glfwSetWindowSizeCallback(win, (Z_TYPE_P(callback) == IS_NULL || Z_TYPE_P(callback) == IS_UNDEF) ? NULL : php_glfw_size_bridge);
            }
        }%
    }

    public static function glfwSetWindowCloseCallback(int window, var callback = null) -> void
    {
        %{
            GLFWwindow *win = (GLFWwindow *)(uintptr_t) window;
            php_glfw_window_callbacks *ctx = php_glfw_window_cb_get(win, 1);
            if (ctx) {
                php_glfw_set_cb_field(&ctx->close, callback);
                glfwSetWindowCloseCallback(win, (Z_TYPE_P(callback) == IS_NULL || Z_TYPE_P(callback) == IS_UNDEF) ? NULL : php_glfw_close_bridge);
            }
        }%
    }

    public static function glfwSetWindowRefreshCallback(int window, var callback = null) -> void
    {
        %{
            GLFWwindow *win = (GLFWwindow *)(uintptr_t) window;
            php_glfw_window_callbacks *ctx = php_glfw_window_cb_get(win, 1);
            if (ctx) {
                php_glfw_set_cb_field(&ctx->refresh, callback);
                glfwSetWindowRefreshCallback(win, (Z_TYPE_P(callback) == IS_NULL || Z_TYPE_P(callback) == IS_UNDEF) ? NULL : php_glfw_refresh_bridge);
            }
        }%
    }

    public static function glfwSetWindowFocusCallback(int window, var callback = null) -> void
    {
        %{
            GLFWwindow *win = (GLFWwindow *)(uintptr_t) window;
            php_glfw_window_callbacks *ctx = php_glfw_window_cb_get(win, 1);
            if (ctx) {
                php_glfw_set_cb_field(&ctx->focus, callback);
                glfwSetWindowFocusCallback(win, (Z_TYPE_P(callback) == IS_NULL || Z_TYPE_P(callback) == IS_UNDEF) ? NULL : php_glfw_focus_bridge);
            }
        }%
    }

    public static function glfwSetWindowIconifyCallback(int window, var callback = null) -> void
    {
        %{
            GLFWwindow *win = (GLFWwindow *)(uintptr_t) window;
            php_glfw_window_callbacks *ctx = php_glfw_window_cb_get(win, 1);
            if (ctx) {
                php_glfw_set_cb_field(&ctx->iconify, callback);
                glfwSetWindowIconifyCallback(win, (Z_TYPE_P(callback) == IS_NULL || Z_TYPE_P(callback) == IS_UNDEF) ? NULL : php_glfw_iconify_bridge);
            }
        }%
    }

    public static function glfwSetWindowMaximizeCallback(int window, var callback = null) -> void
    {
        %{
            GLFWwindow *win = (GLFWwindow *)(uintptr_t) window;
            php_glfw_window_callbacks *ctx = php_glfw_window_cb_get(win, 1);
            if (ctx) {
                php_glfw_set_cb_field(&ctx->maximize, callback);
                glfwSetWindowMaximizeCallback(win, (Z_TYPE_P(callback) == IS_NULL || Z_TYPE_P(callback) == IS_UNDEF) ? NULL : php_glfw_maximize_bridge);
            }
        }%
    }

    public static function glfwSetFramebufferSizeCallback(int window, var callback = null) -> void
    {
        %{
            GLFWwindow *win = (GLFWwindow *)(uintptr_t) window;
            php_glfw_window_callbacks *ctx = php_glfw_window_cb_get(win, 1);
            if (ctx) {
                php_glfw_set_cb_field(&ctx->framebuffer_size, callback);
                glfwSetFramebufferSizeCallback(win, (Z_TYPE_P(callback) == IS_NULL || Z_TYPE_P(callback) == IS_UNDEF) ? NULL : php_glfw_fbsize_bridge);
            }
        }%
    }

    public static function glfwSetWindowContentScaleCallback(int window, var callback = null) -> void
    {
        %{
            GLFWwindow *win = (GLFWwindow *)(uintptr_t) window;
            php_glfw_window_callbacks *ctx = php_glfw_window_cb_get(win, 1);
            if (ctx) {
                php_glfw_set_cb_field(&ctx->content_scale, callback);
                glfwSetWindowContentScaleCallback(win, (Z_TYPE_P(callback) == IS_NULL || Z_TYPE_P(callback) == IS_UNDEF) ? NULL : php_glfw_contentscale_bridge);
            }
        }%
    }

    public static function glfwPollEvents() -> void
    {
        %{ glfwPollEvents(); }%
    }

    public static function glfwWaitEvents() -> void
    {
        %{ glfwWaitEvents(); }%
    }

    public static function glfwWaitEventsTimeout(double timeout) -> void
    {
        %{ glfwWaitEventsTimeout(timeout); }%
    }

    public static function glfwPostEmptyEvent() -> void
    {
        %{ glfwPostEmptyEvent(); }%
    }
}

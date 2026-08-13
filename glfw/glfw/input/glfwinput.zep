namespace Glfw\GLFW\Input;

%{
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
}%

/**
 * GLFW input, joystick, gamepad, clipboard, and timer APIs.
 */
class GLFWInput
{
    public static function glfwGetInputMode(int window, int mode) -> int
    {
        int result;
        %{
            result = (zend_long) glfwGetInputMode((GLFWwindow *)(uintptr_t) window, (int) mode);
        }%
        return result;
    }

    public static function glfwSetInputMode(int window, int mode, int value) -> void
    {
        %{
            glfwSetInputMode((GLFWwindow *)(uintptr_t) window, (int) mode, (int) value);
        }%
    }

    public static function glfwRawMouseMotionSupported() -> bool
    {
        bool result;
        %{
            result = glfwRawMouseMotionSupported() == GLFW_TRUE;
        }%
        return result;
    }

    public static function glfwGetKeyName(int key, int scancode) -> string
    {
        string result;
        %{
            const char *name = glfwGetKeyName((int) key, (int) scancode);
            ZVAL_STRING(&result, name ? name : "");
        }%
        return result;
    }

    public static function glfwGetKeyScancode(int key) -> int
    {
        int result;
        %{
            result = (zend_long) glfwGetKeyScancode((int) key);
        }%
        return result;
    }

    public static function glfwGetKey(int window, int key) -> int
    {
        int result;
        %{
            result = (zend_long) glfwGetKey((GLFWwindow *)(uintptr_t) window, (int) key);
        }%
        return result;
    }

    public static function glfwGetMouseButton(int window, int button) -> int
    {
        int result;
        %{
            result = (zend_long) glfwGetMouseButton((GLFWwindow *)(uintptr_t) window, (int) button);
        }%
        return result;
    }

    public static function glfwGetCursorPos(int window) -> array
    {
        double xpos; double ypos;
        %{
            double x = 0.0, y = 0.0;
            glfwGetCursorPos((GLFWwindow *)(uintptr_t) window, &x, &y);
            xpos = x; ypos = y;
        }%
        return ["xpos": xpos, "ypos": ypos];
    }

    /**
     * Cursor X. Prefer this on the poll hot path (no hashtable).
     */
    public static function glfwGetCursorX(int window) -> double
    {
        double xpos = 0.0;
        %{
            double y = 0.0;
            glfwGetCursorPos((GLFWwindow *)(uintptr_t) window, &xpos, &y);
        }%
        return xpos;
    }

    /**
     * Cursor Y. Prefer this on the poll hot path (no hashtable).
     */
    public static function glfwGetCursorY(int window) -> double
    {
        double ypos = 0.0;
        %{
            double x = 0.0;
            glfwGetCursorPos((GLFWwindow *)(uintptr_t) window, &x, &ypos);
        }%
        return ypos;
    }

    public static function glfwSetCursorPos(int window, double xpos, double ypos) -> void
    {
        %{
            glfwSetCursorPos((GLFWwindow *)(uintptr_t) window, xpos, ypos);
        }%
    }

    /**
     * @param array image ["width"=>int,"height"=>int,"pixels"=>string]
     */
    public static function glfwCreateCursor(array image, int xhot, int yhot) -> int
    {
        int ptr;
        %{
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
        }%
        return ptr;
    }

    public static function glfwCreateStandardCursor(int shape) -> int
    {
        int ptr;
        %{
            ptr = (zend_long)(uintptr_t) glfwCreateStandardCursor((int) shape);
        }%
        return ptr;
    }

    public static function glfwDestroyCursor(int cursor) -> void
    {
        %{
            glfwDestroyCursor((GLFWcursor *)(uintptr_t) cursor);
        }%
    }

    public static function glfwSetCursor(int window, var cursor = null) -> void
    {
        %{
            GLFWcursor *c = NULL;
            if (Z_TYPE_P(cursor) != IS_NULL && Z_TYPE_P(cursor) != IS_UNDEF) {
                c = (GLFWcursor *)(uintptr_t) zval_get_long(cursor);
            }
            glfwSetCursor((GLFWwindow *)(uintptr_t) window, c);
        }%
    }

    public static function glfwSetKeyCallback(int window, var callback = null) -> void
    {
        %{
            GLFWwindow *win = (GLFWwindow *)(uintptr_t) window;
            php_glfw_window_callback_set_field(win, "key", callback);
            glfwSetKeyCallback(win, (Z_TYPE_P(callback) == IS_NULL || Z_TYPE_P(callback) == IS_UNDEF) ? NULL : php_glfw_key_bridge);
        }%
    }

    public static function glfwSetCharCallback(int window, var callback = null) -> void
    {
        %{
            GLFWwindow *win = (GLFWwindow *)(uintptr_t) window;
            php_glfw_window_callback_set_field(win, "character", callback);
            glfwSetCharCallback(win, (Z_TYPE_P(callback) == IS_NULL || Z_TYPE_P(callback) == IS_UNDEF) ? NULL : php_glfw_char_bridge);
        }%
    }

    public static function glfwSetCharModsCallback(int window, var callback = null) -> void
    {
        %{
            GLFWwindow *win = (GLFWwindow *)(uintptr_t) window;
            php_glfw_window_callback_set_field(win, "charmods", callback);
            glfwSetCharModsCallback(win, (Z_TYPE_P(callback) == IS_NULL || Z_TYPE_P(callback) == IS_UNDEF) ? NULL : php_glfw_charmods_bridge);
        }%
    }

    public static function glfwSetMouseButtonCallback(int window, var callback = null) -> void
    {
        %{
            GLFWwindow *win = (GLFWwindow *)(uintptr_t) window;
            php_glfw_window_callback_set_field(win, "mouse_button", callback);
            glfwSetMouseButtonCallback(win, (Z_TYPE_P(callback) == IS_NULL || Z_TYPE_P(callback) == IS_UNDEF) ? NULL : php_glfw_mousebutton_bridge);
        }%
    }

    public static function glfwSetCursorPosCallback(int window, var callback = null) -> void
    {
        %{
            GLFWwindow *win = (GLFWwindow *)(uintptr_t) window;
            php_glfw_window_callback_set_field(win, "cursor_pos", callback);
            glfwSetCursorPosCallback(win, (Z_TYPE_P(callback) == IS_NULL || Z_TYPE_P(callback) == IS_UNDEF) ? NULL : php_glfw_cursorpos_bridge);
        }%
    }

    public static function glfwSetCursorEnterCallback(int window, var callback = null) -> void
    {
        %{
            GLFWwindow *win = (GLFWwindow *)(uintptr_t) window;
            php_glfw_window_callback_set_field(win, "cursor_enter", callback);
            glfwSetCursorEnterCallback(win, (Z_TYPE_P(callback) == IS_NULL || Z_TYPE_P(callback) == IS_UNDEF) ? NULL : php_glfw_cursorenter_bridge);
        }%
    }

    public static function glfwSetScrollCallback(int window, var callback = null) -> void
    {
        %{
            GLFWwindow *win = (GLFWwindow *)(uintptr_t) window;
            php_glfw_window_callback_set_field(win, "scroll", callback);
            glfwSetScrollCallback(win, (Z_TYPE_P(callback) == IS_NULL || Z_TYPE_P(callback) == IS_UNDEF) ? NULL : php_glfw_scroll_bridge);
        }%
    }

    public static function glfwSetDropCallback(int window, var callback = null) -> void
    {
        %{
            GLFWwindow *win = (GLFWwindow *)(uintptr_t) window;
            php_glfw_window_callback_set_field(win, "drop", callback);
            glfwSetDropCallback(win, (Z_TYPE_P(callback) == IS_NULL || Z_TYPE_P(callback) == IS_UNDEF) ? NULL : php_glfw_drop_bridge);
        }%
    }

    public static function glfwJoystickPresent(int jid) -> bool
    {
        bool result;
        %{
            result = glfwJoystickPresent((int) jid) == GLFW_TRUE;
        }%
        return result;
    }

    public static function glfwGetJoystickAxes(int jid) -> array
    {
        array result = [];
        %{
            int count = 0;
            const float *axes = glfwGetJoystickAxes((int) jid, &count);
            array_init(&result);
            if (axes && count > 0) {
                int i;
                for (i = 0; i < count; i++) {
                    add_next_index_double(&result, (double) axes[i]);
                }
            }
        }%
        return result;
    }

    public static function glfwGetJoystickButtons(int jid) -> array
    {
        array result = [];
        %{
            int count = 0;
            const unsigned char *buttons = glfwGetJoystickButtons((int) jid, &count);
            array_init(&result);
            if (buttons && count > 0) {
                int i;
                for (i = 0; i < count; i++) {
                    add_next_index_long(&result, (zend_long) buttons[i]);
                }
            }
        }%
        return result;
    }

    public static function glfwGetJoystickHats(int jid) -> array
    {
        array result = [];
        %{
            int count = 0;
            const unsigned char *hats = glfwGetJoystickHats((int) jid, &count);
            array_init(&result);
            if (hats && count > 0) {
                int i;
                for (i = 0; i < count; i++) {
                    add_next_index_long(&result, (zend_long) hats[i]);
                }
            }
        }%
        return result;
    }

    public static function glfwGetJoystickName(int jid) -> string
    {
        string result;
        %{
            const char *name = glfwGetJoystickName((int) jid);
            ZVAL_STRING(&result, name ? name : "");
        }%
        return result;
    }

    public static function glfwGetJoystickGUID(int jid) -> string
    {
        string result;
        %{
            const char *guid = glfwGetJoystickGUID((int) jid);
            ZVAL_STRING(&result, guid ? guid : "");
        }%
        return result;
    }

    public static function glfwSetJoystickUserPointer(int jid, int pointer) -> void
    {
        %{
            glfwSetJoystickUserPointer((int) jid, (void *)(uintptr_t) pointer);
        }%
    }

    public static function glfwGetJoystickUserPointer(int jid) -> int
    {
        int ptr;
        %{
            ptr = (zend_long)(uintptr_t) glfwGetJoystickUserPointer((int) jid);
        }%
        return ptr;
    }

    public static function glfwJoystickIsGamepad(int jid) -> bool
    {
        bool result;
        %{
            result = glfwJoystickIsGamepad((int) jid) == GLFW_TRUE;
        }%
        return result;
    }

    public static function glfwSetJoystickCallback(var callback = null) -> void
    {
        %{
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
        }%
    }

    public static function glfwUpdateGamepadMappings(string mapping) -> bool
    {
        bool result;
        %{
            result = glfwUpdateGamepadMappings(Z_STRVAL(mapping)) == GLFW_TRUE;
        }%
        return result;
    }

    public static function glfwGetGamepadName(int jid) -> string
    {
        string result;
        %{
            const char *name = glfwGetGamepadName((int) jid);
            ZVAL_STRING(&result, name ? name : "");
        }%
        return result;
    }

    public static function glfwGetGamepadState(int jid) -> array
    {
        array result = [];
        %{
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
        }%
        return result;
    }

    /**
     * One gamepad button (GLFW_PRESS / GLFW_RELEASE). No hashtable.
     */
    public static function glfwGetGamepadButton(int jid, int button) -> int
    {
        int result = 0;
        %{
            GLFWgamepadstate state;
            result = 0;
            if (glfwGetGamepadState((int) jid, &state) == GLFW_TRUE) {
                int b = (int) button;
                if (b >= 0 && b < 15) {
                    result = (zend_long) state.buttons[b];
                }
            }
        }%
        return result;
    }

    /**
     * One gamepad axis. No hashtable.
     */
    public static function glfwGetGamepadAxis(int jid, int axis) -> double
    {
        double result = 0.0;
        %{
            GLFWgamepadstate state;
            result = 0.0;
            if (glfwGetGamepadState((int) jid, &state) == GLFW_TRUE) {
                int a = (int) axis;
                if (a >= 0 && a < 6) {
                    result = (double) state.axes[a];
                }
            }
        }%
        return result;
    }

    public static function glfwSetClipboardString(var window, string value) -> void
    {
        %{
            GLFWwindow *win = NULL;
            if (Z_TYPE_P(window) != IS_NULL && Z_TYPE_P(window) != IS_UNDEF) {
                win = (GLFWwindow *)(uintptr_t) zval_get_long(window);
            }
            glfwSetClipboardString(win, Z_STRVAL(value));
        }%
    }

    public static function glfwGetClipboardString(var window = null) -> string
    {
        string result;
        %{
            GLFWwindow *win = NULL;
            if (Z_TYPE_P(window) != IS_NULL && Z_TYPE_P(window) != IS_UNDEF) {
                win = (GLFWwindow *)(uintptr_t) zval_get_long(window);
            }
            const char *s = glfwGetClipboardString(win);
            ZVAL_STRING(&result, s ? s : "");
        }%
        return result;
    }

    public static function glfwGetTime() -> double
    {
        double result;
        %{
            result = glfwGetTime();
        }%
        return result;
    }

    public static function glfwSetTime(double time) -> void
    {
        %{
            glfwSetTime(time);
        }%
    }

    public static function glfwGetTimerValue() -> int
    {
        int result;
        %{
            result = (zend_long) glfwGetTimerValue();
        }%
        return result;
    }

    public static function glfwGetTimerFrequency() -> int
    {
        int result;
        %{
            result = (zend_long) glfwGetTimerFrequency();
        }%
        return result;
    }
}

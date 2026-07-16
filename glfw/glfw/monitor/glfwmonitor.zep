namespace Glfw\GLFW\Monitor;

%{
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
}%

/**
 * GLFW monitor and video mode APIs.
 */
class GLFWMonitor
{
    public static function glfwGetMonitors() -> array
    {
        array result = [];
        %{
            int count = 0;
            GLFWmonitor **monitors = glfwGetMonitors(&count);
            array_init(&result);
            if (monitors && count > 0) {
                int i;
                for (i = 0; i < count; i++) {
                    add_next_index_long(&result, (zend_long)(uintptr_t) monitors[i]);
                }
            }
        }%
        return result;
    }

    public static function glfwGetPrimaryMonitor() -> int
    {
        int ptr;
        %{
            ptr = (zend_long)(uintptr_t) glfwGetPrimaryMonitor();
        }%
        return ptr;
    }

    public static function glfwGetMonitorPos(int monitor) -> array
    {
        int xpos;
        int ypos;
        %{
            int x = 0, y = 0;
            glfwGetMonitorPos((GLFWmonitor *)(uintptr_t) monitor, &x, &y);
            xpos = (zend_long) x;
            ypos = (zend_long) y;
        }%
        return ["xpos": xpos, "ypos": ypos];
    }

    public static function glfwGetMonitorWorkarea(int monitor) -> array
    {
        int xpos;
        int ypos;
        int width;
        int height;
        %{
            int x = 0, y = 0, w = 0, h = 0;
            glfwGetMonitorWorkarea((GLFWmonitor *)(uintptr_t) monitor, &x, &y, &w, &h);
            xpos = (zend_long) x;
            ypos = (zend_long) y;
            width = (zend_long) w;
            height = (zend_long) h;
        }%
        return ["xpos": xpos, "ypos": ypos, "width": width, "height": height];
    }

    public static function glfwGetMonitorPhysicalSize(int monitor) -> array
    {
        int widthMM;
        int heightMM;
        %{
            int w = 0, h = 0;
            glfwGetMonitorPhysicalSize((GLFWmonitor *)(uintptr_t) monitor, &w, &h);
            widthMM = (zend_long) w;
            heightMM = (zend_long) h;
        }%
        return ["widthMM": widthMM, "heightMM": heightMM];
    }

    public static function glfwGetMonitorContentScale(int monitor) -> array
    {
        double xscale;
        double yscale;
        %{
            float xs = 0.0f, ys = 0.0f;
            glfwGetMonitorContentScale((GLFWmonitor *)(uintptr_t) monitor, &xs, &ys);
            xscale = (double) xs;
            yscale = (double) ys;
        }%
        return ["xscale": xscale, "yscale": yscale];
    }

    public static function glfwGetMonitorName(int monitor) -> string
    {
        string result;
        %{
            const char *name = glfwGetMonitorName((GLFWmonitor *)(uintptr_t) monitor);
            ZVAL_STRING(&result, name ? name : "");
        }%
        return result;
    }

    public static function glfwSetMonitorUserPointer(int monitor, int pointer) -> void
    {
        %{
            glfwSetMonitorUserPointer((GLFWmonitor *)(uintptr_t) monitor, (void *)(uintptr_t) pointer);
        }%
    }

    public static function glfwGetMonitorUserPointer(int monitor) -> int
    {
        int ptr;
        %{
            ptr = (zend_long)(uintptr_t) glfwGetMonitorUserPointer((GLFWmonitor *)(uintptr_t) monitor);
        }%
        return ptr;
    }

    /**
     * @param callable|null callback function(int $monitor, int $event): void
     */
    public static function glfwSetMonitorCallback(var callback = null) -> void
    {
        %{
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
        }%
    }

    public static function glfwGetVideoModes(int monitor) -> array
    {
        array result = [];
        %{
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
        }%
        return result;
    }

    public static function glfwGetVideoMode(int monitor) -> array
    {
        array result = [];
        %{
            const GLFWvidmode *mode = glfwGetVideoMode((GLFWmonitor *)(uintptr_t) monitor);
            if (mode) {
                php_glfw_vidmode_to_zval(mode, &result);
            } else {
                array_init(&result);
            }
        }%
        return result;
    }

    public static function glfwSetGamma(int monitor, float gamma) -> void
    {
        %{
            glfwSetGamma((GLFWmonitor *)(uintptr_t) monitor, (float) gamma);
        }%
    }

    public static function glfwGetGammaRamp(int monitor) -> array
    {
        array result = [];
        %{
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
        }%
        return result;
    }

    /**
     * @param array ramp ["red"=>int[], "green"=>int[], "blue"=>int[], "size"=>int]
     */
    public static function glfwSetGammaRamp(int monitor, array ramp) -> void
    {
        %{
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
        }%
    }
}

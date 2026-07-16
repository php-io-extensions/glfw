namespace Glfw\GLFW;

%{
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
}%

/**
 * GLFW initialization, version, and platform APIs.
 */
class GLFW
{
    public static function glfwInit() -> bool
    {
        bool result;
        %{
            result = glfwInit() == GLFW_TRUE;
        }%
        return result;
    }

    public static function glfwTerminate() -> void
    {
        %{
            glfwTerminate();
        }%
    }

    public static function glfwInitHint(int hint, int value) -> void
    {
        %{
            glfwInitHint((int) hint, (int) value);
        }%
    }

    /**
     * Custom allocators are not exposed to PHP; pass null to restore defaults.
     */
    public static function glfwInitAllocator(var allocator = null) -> void
    {
        %{
            (void) allocator;
            glfwInitAllocator(NULL);
        }%
    }

    /**
     * @param int loader Pointer to PFN_vkGetInstanceProcAddr, or 0 for NULL.
     */
    public static function glfwInitVulkanLoader(int loader = 0) -> void
    {
        %{
            glfwInitVulkanLoader(loader ? (void *)(uintptr_t) loader : NULL);
        }%
    }

    public static function glfwGetVersion() -> array
    {
        int major;
        int minor;
        int rev;
        %{
            int maj = 0, min = 0, r = 0;
            glfwGetVersion(&maj, &min, &r);
            major = (zend_long) maj;
            minor = (zend_long) min;
            rev = (zend_long) r;
        }%
        return ["major": major, "minor": minor, "rev": rev];
    }

    public static function glfwGetVersionString() -> string
    {
        string result;
        %{
            const char *s = glfwGetVersionString();
            ZVAL_STRING(&result, s ? s : "");
        }%
        return result;
    }

    /**
     * @param callable|null callback function(int $errorCode, string $description): void
     */
    public static function glfwSetErrorCallback(var callback = null) -> void
    {
        %{
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
        }%
    }

    public static function glfwGetPlatform() -> int
    {
        int result;
        %{
            result = (zend_long) glfwGetPlatform();
        }%
        return result;
    }

    public static function glfwPlatformSupported(int platform) -> bool
    {
        bool result;
        %{
            result = glfwPlatformSupported((int) platform) == GLFW_TRUE;
        }%
        return result;
    }
}

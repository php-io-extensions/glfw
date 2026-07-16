namespace Glfw\GLFW\Vulkan;

%{
#include <stdio.h>
#include <stdint.h>

/* Opaque Vulkan stand-ins so glfw3.h can declare VK helpers without vulkan.h */
#if !defined(VK_VERSION_1_0)
#define VK_VERSION_1_0 1
typedef void *VkInstance;
typedef void *VkPhysicalDevice;
typedef void *VkSurfaceKHR;
typedef struct VkAllocationCallbacks VkAllocationCallbacks;
typedef int32_t VkResult;
typedef void (*PFN_vkVoidFunction)(void);
typedef PFN_vkVoidFunction (*PFN_vkGetInstanceProcAddr)(VkInstance, const char *);
#endif

#include <GLFW/glfw3.h>
}%

/**
 * GLFW Vulkan support APIs.
 */
class GLFWVulkan
{
    public static function glfwVulkanSupported() -> bool
    {
        bool result;
        %{
            result = glfwVulkanSupported() == GLFW_TRUE;
        }%
        return result;
    }

    public static function glfwGetRequiredInstanceExtensions() -> array
    {
        array result = [];
        %{
            uint32_t count = 0;
            const char **exts = glfwGetRequiredInstanceExtensions(&count);
            array_init(&result);
            if (exts && count > 0) {
                uint32_t i;
                for (i = 0; i < count; i++) {
                    add_next_index_string(&result, exts[i]);
                }
            }
        }%
        return result;
    }

    /**
     * @param int instance VkInstance as opaque pointer int (0 = NULL)
     */
    public static function glfwGetInstanceProcAddress(int instance, string procname) -> int
    {
        int ptr;
        %{
            ptr = (zend_long)(uintptr_t) glfwGetInstanceProcAddress(
                (VkInstance)(uintptr_t) instance,
                Z_STRVAL(procname)
            );
        }%
        return ptr;
    }

    public static function glfwGetPhysicalDevicePresentationSupport(int instance, int device, int queuefamily) -> bool
    {
        bool result;
        %{
            result = glfwGetPhysicalDevicePresentationSupport(
                (VkInstance)(uintptr_t) instance,
                (VkPhysicalDevice)(uintptr_t) device,
                (uint32_t) queuefamily
            ) == GLFW_TRUE;
        }%
        return result;
    }

    /**
     * @param int instance VkInstance pointer
     * @param int window GLFWwindow handle
     * @param int allocator VkAllocationCallbacks pointer, or 0
     * @return array{result: int, surface: int}
     */
    public static function glfwCreateWindowSurface(int instance, int window, int allocator = 0) -> array
    {
        int result;
        int surface;
        %{
            VkSurfaceKHR surf = (VkSurfaceKHR) 0;
            VkResult vr = glfwCreateWindowSurface(
                (VkInstance)(uintptr_t) instance,
                (GLFWwindow *)(uintptr_t) window,
                allocator ? (const VkAllocationCallbacks *)(uintptr_t) allocator : NULL,
                &surf
            );
            result = (zend_long) vr;
            surface = (zend_long)(uintptr_t) surf;
        }%
        return ["result": result, "surface": surface];
    }
}

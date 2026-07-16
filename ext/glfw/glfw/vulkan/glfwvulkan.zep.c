
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
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/array.h"

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



/**
 * GLFW Vulkan support APIs.
 */
ZEPHIR_INIT_CLASS(Glfw_GLFW_Vulkan_GLFWVulkan)
{
	ZEPHIR_REGISTER_CLASS(Glfw\\GLFW\\Vulkan, GLFWVulkan, glfw, glfw_vulkan_glfwvulkan, glfw_glfw_vulkan_glfwvulkan_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Glfw_GLFW_Vulkan_GLFWVulkan, glfwVulkanSupported)
{
	zend_bool result = 0;
	
            result = glfwVulkanSupported() == GLFW_TRUE;
        
	RETURN_BOOL(result);
}

PHP_METHOD(Glfw_GLFW_Vulkan_GLFWVulkan, glfwGetRequiredInstanceExtensions)
{
	zval result;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;

	ZVAL_UNDEF(&result);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&result);
	array_init(&result);
	
            uint32_t count = 0;
            const char **exts = glfwGetRequiredInstanceExtensions(&count);
            array_init(&result);
            if (exts && count > 0) {
                uint32_t i;
                for (i = 0; i < count; i++) {
                    add_next_index_string(&result, exts[i]);
                }
            }
        
	RETURN_CTOR(&result);
}

/**
 * @param int instance VkInstance as opaque pointer int (0 = NULL)
 */
PHP_METHOD(Glfw_GLFW_Vulkan_GLFWVulkan, glfwGetInstanceProcAddress)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval procname;
	zval *instance_param = NULL, *procname_param = NULL;
	zend_long instance, ptr = 0;

	ZVAL_UNDEF(&procname);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(instance)
		Z_PARAM_STR(procname)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &instance_param, &procname_param);
	zephir_get_strval(&procname, procname_param);
	
            ptr = (zend_long)(uintptr_t) glfwGetInstanceProcAddress(
                (VkInstance)(uintptr_t) instance,
                Z_STRVAL(procname)
            );
        
	RETURN_MM_LONG(ptr);
}

PHP_METHOD(Glfw_GLFW_Vulkan_GLFWVulkan, glfwGetPhysicalDevicePresentationSupport)
{
	zend_bool result = 0;
	zval *instance_param = NULL, *device_param = NULL, *queuefamily_param = NULL;
	zend_long instance, device, queuefamily;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(instance)
		Z_PARAM_LONG(device)
		Z_PARAM_LONG(queuefamily)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &instance_param, &device_param, &queuefamily_param);
	
            result = glfwGetPhysicalDevicePresentationSupport(
                (VkInstance)(uintptr_t) instance,
                (VkPhysicalDevice)(uintptr_t) device,
                (uint32_t) queuefamily
            ) == GLFW_TRUE;
        
	RETURN_BOOL(result);
}

/**
 * @param int instance VkInstance pointer
 * @param int window GLFWwindow handle
 * @param int allocator VkAllocationCallbacks pointer, or 0
 * @return array{result: int, surface: int}
 */
PHP_METHOD(Glfw_GLFW_Vulkan_GLFWVulkan, glfwCreateWindowSurface)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *instance_param = NULL, *window_param = NULL, *allocator_param = NULL, _0;
	zend_long instance, window, allocator, result = 0, surface = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(2, 3)
		Z_PARAM_LONG(instance)
		Z_PARAM_LONG(window)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(allocator)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 1, &instance_param, &window_param, &allocator_param);
	if (!allocator_param) {
		allocator = 0;
	} else {
		}
	
            VkSurfaceKHR surf = (VkSurfaceKHR) 0;
            VkResult vr = glfwCreateWindowSurface(
                (VkInstance)(uintptr_t) instance,
                (GLFWwindow *)(uintptr_t) window,
                allocator ? (const VkAllocationCallbacks *)(uintptr_t) allocator : NULL,
                &surf
            );
            result = (zend_long) vr;
            surface = (zend_long)(uintptr_t) surf;
        
	zephir_create_array(return_value, 2, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, result);
	zephir_array_update_string(return_value, SL("result"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, surface);
	zephir_array_update_string(return_value, SL("surface"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}


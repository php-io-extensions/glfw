
extern zend_class_entry *glfw_glfw_vulkan_glfwvulkan_ce;

ZEPHIR_INIT_CLASS(Glfw_GLFW_Vulkan_GLFWVulkan);

PHP_METHOD(Glfw_GLFW_Vulkan_GLFWVulkan, glfwVulkanSupported);
PHP_METHOD(Glfw_GLFW_Vulkan_GLFWVulkan, glfwGetRequiredInstanceExtensions);
PHP_METHOD(Glfw_GLFW_Vulkan_GLFWVulkan, glfwGetInstanceProcAddress);
PHP_METHOD(Glfw_GLFW_Vulkan_GLFWVulkan, glfwGetPhysicalDevicePresentationSupport);
PHP_METHOD(Glfw_GLFW_Vulkan_GLFWVulkan, glfwCreateWindowSurface);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_vulkan_glfwvulkan_glfwvulkansupported, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_vulkan_glfwvulkan_glfwgetrequiredinstanceextensions, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_vulkan_glfwvulkan_glfwgetinstanceprocaddress, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, instance, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, procname, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_vulkan_glfwvulkan_glfwgetphysicaldevicepresentationsupport, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, instance, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, queuefamily, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_vulkan_glfwvulkan_glfwcreatewindowsurface, 0, 2, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, instance, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, allocator, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(glfw_glfw_vulkan_glfwvulkan_method_entry) {
	PHP_ME(Glfw_GLFW_Vulkan_GLFWVulkan, glfwVulkanSupported, arginfo_glfw_glfw_vulkan_glfwvulkan_glfwvulkansupported, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Vulkan_GLFWVulkan, glfwGetRequiredInstanceExtensions, arginfo_glfw_glfw_vulkan_glfwvulkan_glfwgetrequiredinstanceextensions, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Vulkan_GLFWVulkan, glfwGetInstanceProcAddress, arginfo_glfw_glfw_vulkan_glfwvulkan_glfwgetinstanceprocaddress, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Vulkan_GLFWVulkan, glfwGetPhysicalDevicePresentationSupport, arginfo_glfw_glfw_vulkan_glfwvulkan_glfwgetphysicaldevicepresentationsupport, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Vulkan_GLFWVulkan, glfwCreateWindowSurface, arginfo_glfw_glfw_vulkan_glfwvulkan_glfwcreatewindowsurface, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};

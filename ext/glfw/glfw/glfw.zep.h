
extern zend_class_entry *glfw_glfw_glfw_ce;

ZEPHIR_INIT_CLASS(Glfw_GLFW_GLFW);

PHP_METHOD(Glfw_GLFW_GLFW, glfwInit);
PHP_METHOD(Glfw_GLFW_GLFW, glfwTerminate);
PHP_METHOD(Glfw_GLFW_GLFW, glfwInitHint);
PHP_METHOD(Glfw_GLFW_GLFW, glfwInitAllocator);
PHP_METHOD(Glfw_GLFW_GLFW, glfwInitVulkanLoader);
PHP_METHOD(Glfw_GLFW_GLFW, glfwGetVersion);
PHP_METHOD(Glfw_GLFW_GLFW, glfwGetVersionString);
PHP_METHOD(Glfw_GLFW_GLFW, glfwSetErrorCallback);
PHP_METHOD(Glfw_GLFW_GLFW, glfwGetPlatform);
PHP_METHOD(Glfw_GLFW_GLFW, glfwPlatformSupported);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_glfw_glfwinit, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_glfw_glfwterminate, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_glfw_glfwinithint, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, hint, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_glfw_glfwinitallocator, 0, 0, IS_VOID, 0)

	ZEND_ARG_INFO(0, allocator)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_glfw_glfwinitvulkanloader, 0, 0, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, loader, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_glfw_glfwgetversion, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_glfw_glfwgetversionstring, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_glfw_glfwseterrorcallback, 0, 0, IS_VOID, 0)

	ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_glfw_glfwgetplatform, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_glfw_glfwplatformsupported, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, platform, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(glfw_glfw_glfw_method_entry) {
	PHP_ME(Glfw_GLFW_GLFW, glfwInit, arginfo_glfw_glfw_glfw_glfwinit, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_GLFW, glfwTerminate, arginfo_glfw_glfw_glfw_glfwterminate, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_GLFW, glfwInitHint, arginfo_glfw_glfw_glfw_glfwinithint, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_GLFW, glfwInitAllocator, arginfo_glfw_glfw_glfw_glfwinitallocator, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_GLFW, glfwInitVulkanLoader, arginfo_glfw_glfw_glfw_glfwinitvulkanloader, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_GLFW, glfwGetVersion, arginfo_glfw_glfw_glfw_glfwgetversion, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_GLFW, glfwGetVersionString, arginfo_glfw_glfw_glfw_glfwgetversionstring, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_GLFW, glfwSetErrorCallback, arginfo_glfw_glfw_glfw_glfwseterrorcallback, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_GLFW, glfwGetPlatform, arginfo_glfw_glfw_glfw_glfwgetplatform, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_GLFW, glfwPlatformSupported, arginfo_glfw_glfw_glfw_glfwplatformsupported, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};

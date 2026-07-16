
extern zend_class_entry *glfw_glfw_context_glfwcontext_ce;

ZEPHIR_INIT_CLASS(Glfw_GLFW_Context_GLFWContext);

PHP_METHOD(Glfw_GLFW_Context_GLFWContext, glfwMakeContextCurrent);
PHP_METHOD(Glfw_GLFW_Context_GLFWContext, glfwGetCurrentContext);
PHP_METHOD(Glfw_GLFW_Context_GLFWContext, glfwSwapBuffers);
PHP_METHOD(Glfw_GLFW_Context_GLFWContext, glfwSwapInterval);
PHP_METHOD(Glfw_GLFW_Context_GLFWContext, glfwExtensionSupported);
PHP_METHOD(Glfw_GLFW_Context_GLFWContext, glfwGetProcAddress);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_context_glfwcontext_glfwmakecontextcurrent, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_context_glfwcontext_glfwgetcurrentcontext, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_context_glfwcontext_glfwswapbuffers, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_context_glfwcontext_glfwswapinterval, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, interval, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_context_glfwcontext_glfwextensionsupported, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, extension, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_context_glfwcontext_glfwgetprocaddress, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, procname, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(glfw_glfw_context_glfwcontext_method_entry) {
	PHP_ME(Glfw_GLFW_Context_GLFWContext, glfwMakeContextCurrent, arginfo_glfw_glfw_context_glfwcontext_glfwmakecontextcurrent, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Context_GLFWContext, glfwGetCurrentContext, arginfo_glfw_glfw_context_glfwcontext_glfwgetcurrentcontext, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Context_GLFWContext, glfwSwapBuffers, arginfo_glfw_glfw_context_glfwcontext_glfwswapbuffers, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Context_GLFWContext, glfwSwapInterval, arginfo_glfw_glfw_context_glfwcontext_glfwswapinterval, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Context_GLFWContext, glfwExtensionSupported, arginfo_glfw_glfw_context_glfwcontext_glfwextensionsupported, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Context_GLFWContext, glfwGetProcAddress, arginfo_glfw_glfw_context_glfwcontext_glfwgetprocaddress, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};

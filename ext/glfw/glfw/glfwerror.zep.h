
extern zend_class_entry *glfw_glfw_glfwerror_ce;

ZEPHIR_INIT_CLASS(Glfw_GLFW_GLFWError);

PHP_METHOD(Glfw_GLFW_GLFWError, glfwGetError);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_glfwerror_glfwgeterror, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(glfw_glfw_glfwerror_method_entry) {
	PHP_ME(Glfw_GLFW_GLFWError, glfwGetError, arginfo_glfw_glfw_glfwerror_glfwgeterror, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};

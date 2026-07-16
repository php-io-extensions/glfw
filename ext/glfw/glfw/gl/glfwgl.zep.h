
extern zend_class_entry *glfw_glfw_gl_glfwgl_ce;

ZEPHIR_INIT_CLASS(Glfw_GLFW_GL_GLFWGL);

PHP_METHOD(Glfw_GLFW_GL_GLFWGL, glClearColor);
PHP_METHOD(Glfw_GLFW_GL_GLFWGL, glClear);
PHP_METHOD(Glfw_GLFW_GL_GLFWGL, glViewport);
PHP_METHOD(Glfw_GLFW_GL_GLFWGL, glScissor);
PHP_METHOD(Glfw_GLFW_GL_GLFWGL, glEnable);
PHP_METHOD(Glfw_GLFW_GL_GLFWGL, glDisable);
PHP_METHOD(Glfw_GLFW_GL_GLFWGL, glGetError);
PHP_METHOD(Glfw_GLFW_GL_GLFWGL, glGetString);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_gl_glfwgl_glclearcolor, 0, 4, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, red, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, green, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, blue, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, alpha, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_gl_glfwgl_glclear, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, mask, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_gl_glfwgl_glviewport, 0, 4, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_gl_glfwgl_glscissor, 0, 4, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_gl_glfwgl_glenable, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, cap, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_gl_glfwgl_gldisable, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, cap, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_gl_glfwgl_glgeterror, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_gl_glfwgl_glgetstring, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(glfw_glfw_gl_glfwgl_method_entry) {
	PHP_ME(Glfw_GLFW_GL_GLFWGL, glClearColor, arginfo_glfw_glfw_gl_glfwgl_glclearcolor, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_GL_GLFWGL, glClear, arginfo_glfw_glfw_gl_glfwgl_glclear, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_GL_GLFWGL, glViewport, arginfo_glfw_glfw_gl_glfwgl_glviewport, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_GL_GLFWGL, glScissor, arginfo_glfw_glfw_gl_glfwgl_glscissor, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_GL_GLFWGL, glEnable, arginfo_glfw_glfw_gl_glfwgl_glenable, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_GL_GLFWGL, glDisable, arginfo_glfw_glfw_gl_glfwgl_gldisable, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_GL_GLFWGL, glGetError, arginfo_glfw_glfw_gl_glfwgl_glgeterror, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_GL_GLFWGL, glGetString, arginfo_glfw_glfw_gl_glfwgl_glgetstring, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};

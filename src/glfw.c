/*
 * glfw: 1:1 bindings of GLFW 3.4 for staged windows: init, monitors and video modes, windows and
 * their hints, attributes and callbacks, events, contexts, Vulkan surfaces and native handles.
 * Input (keys, mouse, joysticks, cursors) is not bound. Handles and constants keep their C names;
 * dropping the last PHP reference does not destroy the native object.
 */

#include "runtime.h"
#include "ext/standard/info.h"

ZEND_DECLARE_MODULE_GLOBALS(glfw)

static PHP_GINIT_FUNCTION(glfw)
{
#if defined(COMPILE_DL_GLFW) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	zend_hash_init(&glfw_globals->boxes, 32, NULL, NULL, 1);
	zend_hash_init(&glfw_globals->window_callbacks, 8, NULL, NULL, 1);
	ZVAL_UNDEF(&glfw_globals->error_callback);
	ZVAL_UNDEF(&glfw_globals->monitor_callback);
}

static PHP_GSHUTDOWN_FUNCTION(glfw)
{
	zend_hash_destroy(&glfw_globals->boxes);
	zend_hash_destroy(&glfw_globals->window_callbacks);
}

PHP_MINIT_FUNCTION(glfw)
{
	glfw_register_glfw3(module_number);
	glfw_register_glfw3native(module_number);

	return SUCCESS;
}

PHP_RINIT_FUNCTION(glfw)
{
#if defined(COMPILE_DL_GLFW) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}

/*
 * The callables the request stored die with it: GLFW is told to stop calling them first, so a
 * window or error that outlives the request (a later request in the same process) calls nothing.
 */
PHP_RSHUTDOWN_FUNCTION(glfw)
{
	if (Z_TYPE(GLFW_G(error_callback)) != IS_UNDEF) {
		glfwSetErrorCallback(NULL);
		zval_ptr_dtor(&GLFW_G(error_callback));
		ZVAL_UNDEF(&GLFW_G(error_callback));
	}
	if (Z_TYPE(GLFW_G(monitor_callback)) != IS_UNDEF) {
		glfwSetMonitorCallback(NULL);
		zval_ptr_dtor(&GLFW_G(monitor_callback));
		ZVAL_UNDEF(&GLFW_G(monitor_callback));
	}
	glfw_callbacks_drop_all(true);

	return SUCCESS;
}

PHP_MINFO_FUNCTION(glfw)
{
	php_info_print_table_start();
	php_info_print_table_row(2, "glfw support", "enabled");
	php_info_print_table_row(2, "Version", PHP_GLFW_VERSION);
	php_info_print_table_row(2, "GLFW version", glfwGetVersionString());
	php_info_print_table_end();
}

zend_module_entry glfw_module_entry = {
	STANDARD_MODULE_HEADER,
	"glfw",
	NULL,
	PHP_MINIT(glfw),
	NULL,
	PHP_RINIT(glfw),
	PHP_RSHUTDOWN(glfw),
	PHP_MINFO(glfw),
	PHP_GLFW_VERSION,
	PHP_MODULE_GLOBALS(glfw),
	PHP_GINIT(glfw),
	PHP_GSHUTDOWN(glfw),
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};

#ifdef COMPILE_DL_GLFW
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(glfw)
#endif


/* This file was generated automatically by Zephir do not modify it! */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>

#include "php_ext.h"
#include "glfw.h"

#include <ext/standard/info.h>

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/globals.h"
#include "kernel/main.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"



zend_class_entry *glfw_glfw_context_glfwcontext_ce;
zend_class_entry *glfw_glfw_gl_glfwgl_ce;
zend_class_entry *glfw_glfw_glfw_ce;
zend_class_entry *glfw_glfw_glfwerror_ce;
zend_class_entry *glfw_glfw_input_glfwinput_ce;
zend_class_entry *glfw_glfw_monitor_glfwmonitor_ce;
zend_class_entry *glfw_glfw_vulkan_glfwvulkan_ce;
zend_class_entry *glfw_glfw_window_glfwwindow_ce;

ZEND_DECLARE_MODULE_GLOBALS(glfw)

PHP_INI_BEGIN()
	
PHP_INI_END()

static PHP_MINIT_FUNCTION(glfw)
{
	REGISTER_INI_ENTRIES();
	zephir_module_init();
	ZEPHIR_INIT(Glfw_GLFW_Context_GLFWContext);
	ZEPHIR_INIT(Glfw_GLFW_GLFW);
	ZEPHIR_INIT(Glfw_GLFW_GLFWError);
	ZEPHIR_INIT(Glfw_GLFW_GL_GLFWGL);
	ZEPHIR_INIT(Glfw_GLFW_Input_GLFWInput);
	ZEPHIR_INIT(Glfw_GLFW_Monitor_GLFWMonitor);
	ZEPHIR_INIT(Glfw_GLFW_Vulkan_GLFWVulkan);
	ZEPHIR_INIT(Glfw_GLFW_Window_GLFWWindow);
	
	return SUCCESS;
}

#ifndef ZEPHIR_RELEASE
static PHP_MSHUTDOWN_FUNCTION(glfw)
{
	
	zephir_deinitialize_memory();
	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}
#endif

/**
 * Initialize globals on each request or each thread started
 */
static void php_zephir_init_globals(zend_glfw_globals *glfw_globals)
{
	glfw_globals->initialized = 0;

	/* Cache Enabled */
	glfw_globals->cache_enabled = 1;

	/* Recursive Lock */
	glfw_globals->recursive_lock = 0;

	/* Static cache */
	memset(glfw_globals->scache, '\0', sizeof(zephir_fcall_cache_entry*) * ZEPHIR_MAX_CACHE_SLOTS);

	
	
}

/**
 * Initialize globals only on each thread started
 */
static void php_zephir_init_module_globals(zend_glfw_globals *glfw_globals)
{
	
}

static PHP_RINIT_FUNCTION(glfw)
{
	zend_glfw_globals *glfw_globals_ptr;
	glfw_globals_ptr = ZEPHIR_VGLOBAL;

	php_zephir_init_globals(glfw_globals_ptr);
	zephir_initialize_memory(glfw_globals_ptr);

	
	return SUCCESS;
}

static PHP_RSHUTDOWN_FUNCTION(glfw)
{
	
	zephir_deinitialize_memory();
	return SUCCESS;
}



static PHP_MINFO_FUNCTION(glfw)
{
	php_info_print_box_start(0);
	php_printf("%s", PHP_GLFW_DESCRIPTION);
	php_info_print_box_end();

	php_info_print_table_start();
	php_info_print_table_header(2, PHP_GLFW_NAME, "enabled");
	php_info_print_table_row(2, "Author", PHP_GLFW_AUTHOR);
	php_info_print_table_row(2, "Version", PHP_GLFW_VERSION);
	php_info_print_table_row(2, "Build Date", __DATE__ " " __TIME__ );
	php_info_print_table_row(2, "Powered by Zephir", "Version " PHP_GLFW_ZEPVERSION);
	php_info_print_table_end();
	
	DISPLAY_INI_ENTRIES();
}

static PHP_GINIT_FUNCTION(glfw)
{
#if defined(COMPILE_DL_GLFW) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	php_zephir_init_globals(glfw_globals);
	php_zephir_init_module_globals(glfw_globals);
}

static PHP_GSHUTDOWN_FUNCTION(glfw)
{
	
}


zend_function_entry php_glfw_functions[] = {
	ZEND_FE_END

};

static const zend_module_dep php_glfw_deps[] = {
	
	ZEND_MOD_END
};

zend_module_entry glfw_module_entry = {
	STANDARD_MODULE_HEADER_EX,
	NULL,
	php_glfw_deps,
	PHP_GLFW_EXTNAME,
	php_glfw_functions,
	PHP_MINIT(glfw),
#ifndef ZEPHIR_RELEASE
	PHP_MSHUTDOWN(glfw),
#else
	NULL,
#endif
	PHP_RINIT(glfw),
	PHP_RSHUTDOWN(glfw),
	PHP_MINFO(glfw),
	PHP_GLFW_VERSION,
	ZEND_MODULE_GLOBALS(glfw),
	PHP_GINIT(glfw),
	PHP_GSHUTDOWN(glfw),
#ifdef ZEPHIR_POST_REQUEST
	PHP_PRSHUTDOWN(glfw),
#else
	NULL,
#endif
	STANDARD_MODULE_PROPERTIES_EX
};

/* implement standard "stub" routine to introduce ourselves to Zend */
#ifdef COMPILE_DL_GLFW
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(glfw)
#endif

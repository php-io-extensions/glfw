
/* This file was generated automatically by Zephir do not modify it! */

#ifndef PHP_GLFW_H
#define PHP_GLFW_H 1

#ifdef PHP_WIN32
#define ZEPHIR_RELEASE 1
#endif

#include "kernel/globals.h"

#define PHP_GLFW_NAME        "glfw"
#define PHP_GLFW_VERSION     "0.7.0"
#define PHP_GLFW_EXTNAME     "glfw"
#define PHP_GLFW_AUTHOR      "Project Saturn Studios, LLC"
#define PHP_GLFW_ZEPVERSION  "0.19.0-$Id$"
#define PHP_GLFW_DESCRIPTION "PHP-Controllable GLFW Windowing Extension"



ZEND_BEGIN_MODULE_GLOBALS(glfw)

	int initialized;

	/** Function cache */
	HashTable *fcache;

	zephir_fcall_cache_entry *scache[ZEPHIR_MAX_CACHE_SLOTS];

	/* Cache enabled */
	unsigned int cache_enabled;

	/* Max recursion control */
	unsigned int recursive_lock;

	
ZEND_END_MODULE_GLOBALS(glfw)

#ifdef ZTS
#include "TSRM.h"
#endif

ZEND_EXTERN_MODULE_GLOBALS(glfw)

#ifdef ZTS
	#define ZEPHIR_GLOBAL(v) ZEND_MODULE_GLOBALS_ACCESSOR(glfw, v)
#else
	#define ZEPHIR_GLOBAL(v) (glfw_globals.v)
#endif

#ifdef ZTS
	ZEND_TSRMLS_CACHE_EXTERN()
	#define ZEPHIR_VGLOBAL ((zend_glfw_globals *) (*((void ***) tsrm_get_ls_cache()))[TSRM_UNSHUFFLE_RSRC_ID(glfw_globals_id)])
#else
	#define ZEPHIR_VGLOBAL &(glfw_globals)
#endif

#define ZEPHIR_API ZEND_API

#define zephir_globals_def glfw_globals
#define zend_zephir_globals_def zend_glfw_globals

extern zend_module_entry glfw_module_entry;
#define phpext_glfw_ptr &glfw_module_entry

#endif

#ifndef PHP_GLFW_H
#define PHP_GLFW_H

extern zend_module_entry glfw_module_entry;
#define phpext_glfw_ptr &glfw_module_entry

#define PHP_GLFW_VERSION "0.10.0"

#if defined(ZTS) && defined(COMPILE_DL_GLFW)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

#endif

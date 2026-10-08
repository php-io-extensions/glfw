PHP_ARG_ENABLE([glfw],
  [whether to enable glfw support],
  [AS_HELP_STRING([--enable-glfw], [Enable the GLFW 3.4 bindings])],
  [no])

if test "$PHP_GLFW" != "no"; then
  PKG_CHECK_MODULES([GLFW], [glfw3 >= 3.4])
  PHP_EVAL_INCLINE([$GLFW_CFLAGS])
  PHP_EVAL_LIBLINE([$GLFW_LIBS], [GLFW_SHARED_LIBADD])
  PHP_SUBST([GLFW_SHARED_LIBADD])

  PHP_NEW_EXTENSION([glfw],
    [src/glfw.c src/runtime.c src/glfw3.c src/glfw3native.c],
    [$ext_shared],, [-DZEND_ENABLE_STATIC_TSRMLS_CACHE=1])
  PHP_ADD_BUILD_DIR([$ext_builddir/src])
fi

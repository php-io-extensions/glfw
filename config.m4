PHP_ARG_ENABLE([glfw],
  [whether to enable glfw support],
  [AS_HELP_STRING([--enable-glfw], [Enable the GLFW 3.4 bindings])],
  [no])

if test "$PHP_GLFW" != "no"; then
  PKG_CHECK_MODULES([GLFW], [glfw3 >= 3.4])
  PHP_EVAL_INCLINE([$GLFW_CFLAGS])
  PHP_EVAL_LIBLINE([$GLFW_LIBS], [GLFW_SHARED_LIBADD])
  dnl Compiled into PHP, the flags PHP_EVAL_LIBLINE drops (a static library's -framework
  dnl pairs and -Wl, flags on macOS) join PHP's program link line.
  if test "$ext_shared" != "yes"; then
    for glfw_flag in $GLFW_LIBS; do
      case $glfw_flag in
        -l*|-L*|-pthread) ;;
        *) EXTRA_LDFLAGS_PROGRAM="$EXTRA_LDFLAGS_PROGRAM $glfw_flag" ;;
      esac
    done
  fi
  PHP_SUBST([GLFW_SHARED_LIBADD])

  PHP_NEW_EXTENSION([glfw],
    [src/glfw.c src/runtime.c src/glfw3.c src/glfw3native.c],
    [$ext_shared],, [-DZEND_ENABLE_STATIC_TSRMLS_CACHE=1])
  PHP_ADD_BUILD_DIR([$ext_builddir/src])
fi

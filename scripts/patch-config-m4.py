#!/usr/bin/env python3
"""Rewrite ext/config.m4 for portable GLFW + OpenGL linking (pkg-config / Darwin framework)."""

from __future__ import annotations

from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
CONFIG_M4 = ROOT / "ext" / "config.m4"

CONFIG = r"""PHP_ARG_ENABLE(glfw, whether to enable glfw, [ --enable-glfw   Enable Glfw])

if test "$PHP_GLFW" = "yes"; then

	dnl GCC 14+ promotes long-standing warnings to errors; Zephir-generated C
	dnl trips some of them. Demote back to warnings. GL_SILENCE_DEPRECATION
	dnl quiets macOS OpenGL deprecation noise in GLFWGL.
	CFLAGS="$CFLAGS -Wno-error=incompatible-pointer-types -Wno-error=int-conversion -Wno-error=implicit-function-declaration -Wno-error=implicit-int -DGL_SILENCE_DEPRECATION"

	AC_PATH_PROG(PKG_CONFIG, pkg-config, no)
	if test "x$PKG_CONFIG" = "xno"; then
		AC_MSG_RESULT([pkg-config not found])
		AC_MSG_ERROR([Please reinstall the pkg-config distribution])
	fi

	AC_MSG_CHECKING([for glfw3])
	if $PKG_CONFIG --exists glfw3; then
		PHP_GLFW3_VERSION=`$PKG_CONFIG glfw3 --modversion`
		PHP_GLFW3_PREFIX=`$PKG_CONFIG glfw3 --variable=prefix`

		if $PKG_CONFIG --atleast-version=3.4.0 glfw3; then
			AC_MSG_RESULT([found version $PHP_GLFW3_VERSION, under $PHP_GLFW3_PREFIX])
			PHP_GLFW3_LIBS=`$PKG_CONFIG glfw3 --libs`
			PHP_GLFW3_INCS=`$PKG_CONFIG glfw3 --cflags`

			PHP_EVAL_LIBLINE($PHP_GLFW3_LIBS, GLFW_SHARED_LIBADD)
			PHP_EVAL_INCLINE($PHP_GLFW3_INCS)
		else
			AC_MSG_ERROR(Requested 'glfw3 >= 3.4.0' but version of glfw3 is $PHP_GLFW3_VERSION)
		fi
	else
		AC_MSG_ERROR(Unable to find glfw3 installation)
	fi

	dnl Optional search-path hints for Homebrew /usr/local layouts.
	for prefix in /opt/homebrew /usr/local; do
		if test -d "$prefix/include"; then
			PHP_ADD_INCLUDE([$prefix/include])
		fi
		if test -d "$prefix/lib"; then
			GLFW_SHARED_LIBADD="$[]GLFW_SHARED_LIBADD -L$prefix/lib"
		fi
	done

	AC_DEFINE(HAVE_GLFW, 1, [Whether you have Glfw])
	glfw_sources="glfw.c kernel/main.c kernel/memory.c kernel/exception.c kernel/debug.c kernel/backtrace.c kernel/object.c kernel/array.c kernel/string.c kernel/fcall.c kernel/require.c kernel/file.c kernel/operators.c kernel/math.c kernel/concat.c kernel/variables.c kernel/filter.c kernel/iterator.c kernel/time.c kernel/exit.c glfw/glfw/context/glfwcontext.zep.c
	glfw/glfw/gl/glfwgl.zep.c
	glfw/glfw/glfw.zep.c
	glfw/glfw/glfwerror.zep.c
	glfw/glfw/input/glfwinput.zep.c
	glfw/glfw/monitor/glfwmonitor.zep.c
	glfw/glfw/vulkan/glfwvulkan.zep.c
	glfw/glfw/window/glfwwindow.zep.c "
	PHP_NEW_EXTENSION(glfw, $glfw_sources, $ext_shared,, $PHP_GLFW3_INCS )
	PHP_ADD_BUILD_DIR([$ext_builddir/kernel/])
	for dir in "glfw/glfw" "glfw/glfw/context" "glfw/glfw/gl" "glfw/glfw/input" "glfw/glfw/monitor" "glfw/glfw/vulkan" "glfw/glfw/window"; do
		PHP_ADD_BUILD_DIR([$ext_builddir/$dir])
	done

	dnl Link system OpenGL for Glfw\GLFW\GL\GLFWGL.
	dnl $[] keeps a literal $ through autoconf/m4.
	case `uname -s` in
		Darwin)
			GLFW_SHARED_LIBADD="$[]GLFW_SHARED_LIBADD -framework OpenGL"
			;;
		*)
			PHP_EVAL_LIBLINE(-lGL, GLFW_SHARED_LIBADD)
			;;
	esac

	PHP_SUBST(GLFW_SHARED_LIBADD)

	old_CPPFLAGS=$CPPFLAGS
	CPPFLAGS="$CPPFLAGS $INCLUDES"

	AC_CHECK_DECL(
		[HAVE_BUNDLED_PCRE],
		[
			AC_CHECK_HEADERS(
				[ext/pcre/php_pcre.h],
				[
					PHP_ADD_EXTENSION_DEP([glfw], [pcre])
					AC_DEFINE([ZEPHIR_USE_PHP_PCRE], [1], [Whether PHP pcre extension is present at compile time])
				],
				,
				[[#include "main/php.h"]]
			)
		],
		,
		[[#include "php_config.h"]]
	)

	AC_CHECK_DECL(
		[HAVE_JSON],
		[
			AC_CHECK_HEADERS(
				[ext/json/php_json.h],
				[
					PHP_ADD_EXTENSION_DEP([glfw], [json])
					AC_DEFINE([ZEPHIR_USE_PHP_JSON], [1], [Whether PHP json extension is present at compile time])
				],
				,
				[[#include "main/php.h"]]
			)
		],
		,
		[[#include "php_config.h"]]
	)

	CPPFLAGS=$old_CPPFLAGS

	PHP_INSTALL_HEADERS([ext/glfw], [php_GLFW.h])

fi
"""


def main() -> None:
    if not CONFIG_M4.exists():
        raise SystemExit(f"missing {CONFIG_M4} — run zephir generate first")
    CONFIG_M4.write_text(CONFIG, encoding="utf-8")
    print(f"patched {CONFIG_M4}")


if __name__ == "__main__":
    main()

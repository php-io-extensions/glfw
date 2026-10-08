/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 0846e7743f1448ca6f759f6f58c015906b4c6f7e */

#if defined(__APPLE__)
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetCocoaWindow, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
ZEND_END_ARG_INFO()

#define arginfo_glfwGetCocoaView arginfo_glfwGetCocoaWindow

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetCocoaMonitor, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, monitor, GLFWmonitor, 0)
ZEND_END_ARG_INFO()

#define arginfo_glfwGetNSGLContext arginfo_glfwGetCocoaWindow
#endif

#if defined(__linux__)
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetX11Display, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetX11Window, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetX11Adapter, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, monitor, GLFWmonitor, 0)
ZEND_END_ARG_INFO()

#define arginfo_glfwGetX11Monitor arginfo_glfwGetX11Adapter

#define arginfo_glfwGetWaylandDisplay arginfo_glfwGetX11Display

#define arginfo_glfwGetWaylandWindow arginfo_glfwGetX11Window

#define arginfo_glfwGetWaylandMonitor arginfo_glfwGetX11Adapter

#define arginfo_glfwGetGLXContext arginfo_glfwGetX11Window

#define arginfo_glfwGetGLXWindow arginfo_glfwGetX11Window

#define arginfo_glfwGetEGLDisplay arginfo_glfwGetX11Display

#define arginfo_glfwGetEGLContext arginfo_glfwGetX11Window

#define arginfo_glfwGetEGLSurface arginfo_glfwGetX11Window
#endif

#if defined(__APPLE__)
ZEND_FUNCTION(glfwGetCocoaWindow);
ZEND_FUNCTION(glfwGetCocoaView);
ZEND_FUNCTION(glfwGetCocoaMonitor);
ZEND_FUNCTION(glfwGetNSGLContext);
#endif
#if defined(__linux__)
ZEND_FUNCTION(glfwGetX11Display);
ZEND_FUNCTION(glfwGetX11Window);
ZEND_FUNCTION(glfwGetX11Adapter);
ZEND_FUNCTION(glfwGetX11Monitor);
ZEND_FUNCTION(glfwGetWaylandDisplay);
ZEND_FUNCTION(glfwGetWaylandWindow);
ZEND_FUNCTION(glfwGetWaylandMonitor);
ZEND_FUNCTION(glfwGetGLXContext);
ZEND_FUNCTION(glfwGetGLXWindow);
ZEND_FUNCTION(glfwGetEGLDisplay);
ZEND_FUNCTION(glfwGetEGLContext);
ZEND_FUNCTION(glfwGetEGLSurface);
#endif

static const zend_function_entry ext_functions[] = {
#if defined(__APPLE__)
	ZEND_FE(glfwGetCocoaWindow, arginfo_glfwGetCocoaWindow)
	ZEND_FE(glfwGetCocoaView, arginfo_glfwGetCocoaView)
	ZEND_FE(glfwGetCocoaMonitor, arginfo_glfwGetCocoaMonitor)
	ZEND_FE(glfwGetNSGLContext, arginfo_glfwGetNSGLContext)
#endif
#if defined(__linux__)
	ZEND_FE(glfwGetX11Display, arginfo_glfwGetX11Display)
	ZEND_FE(glfwGetX11Window, arginfo_glfwGetX11Window)
	ZEND_FE(glfwGetX11Adapter, arginfo_glfwGetX11Adapter)
	ZEND_FE(glfwGetX11Monitor, arginfo_glfwGetX11Monitor)
	ZEND_FE(glfwGetWaylandDisplay, arginfo_glfwGetWaylandDisplay)
	ZEND_FE(glfwGetWaylandWindow, arginfo_glfwGetWaylandWindow)
	ZEND_FE(glfwGetWaylandMonitor, arginfo_glfwGetWaylandMonitor)
	ZEND_FE(glfwGetGLXContext, arginfo_glfwGetGLXContext)
	ZEND_FE(glfwGetGLXWindow, arginfo_glfwGetGLXWindow)
	ZEND_FE(glfwGetEGLDisplay, arginfo_glfwGetEGLDisplay)
	ZEND_FE(glfwGetEGLContext, arginfo_glfwGetEGLContext)
	ZEND_FE(glfwGetEGLSurface, arginfo_glfwGetEGLSurface)
#endif
	ZEND_FE_END
};

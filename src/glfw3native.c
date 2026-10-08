/*
 * The native-access functions GLFW 3.4 exports, declared here with ABI-identical opaque types
 * (pointers as void *, X11 ids as unsigned long, display ids as uint32_t) instead of through
 * glfw3native.h, so the build needs no Cocoa, X11, Xrandr, Wayland, GLX or EGL headers. Each
 * answers the handle as an int: an address or an id for another extension to adopt.
 */

#include "runtime.h"
#include "../stubs/glfw3native_arginfo.h"

#ifdef __APPLE__
void *glfwGetCocoaWindow(GLFWwindow *window);
void *glfwGetCocoaView(GLFWwindow *window);
uint32_t glfwGetCocoaMonitor(GLFWmonitor *monitor);
void *glfwGetNSGLContext(GLFWwindow *window);
#endif

#ifdef __linux__
void *glfwGetX11Display(void);
unsigned long glfwGetX11Window(GLFWwindow *window);
unsigned long glfwGetX11Adapter(GLFWmonitor *monitor);
unsigned long glfwGetX11Monitor(GLFWmonitor *monitor);
void *glfwGetWaylandDisplay(void);
void *glfwGetWaylandWindow(GLFWwindow *window);
void *glfwGetWaylandMonitor(GLFWmonitor *monitor);
void *glfwGetGLXContext(GLFWwindow *window);
unsigned long glfwGetGLXWindow(GLFWwindow *window);
void *glfwGetEGLDisplay(void);
void *glfwGetEGLContext(GLFWwindow *window);
void *glfwGetEGLSurface(GLFWwindow *window);
#endif

void glfw_register_glfw3native(int module_number)
{
	zend_register_functions(NULL, ext_functions, NULL, MODULE_PERSISTENT);
}

#define GLFW_NATIVE_OF_WINDOW(fn) \
ZEND_FUNCTION(fn) \
{ \
	zend_object *window_obj; \
	ZEND_PARSE_PARAMETERS_START(1, 1) \
		Z_PARAM_OBJ_OF_CLASS(window_obj, glfw_ce_GLFWwindow) \
	ZEND_PARSE_PARAMETERS_END(); \
	GLFW_WINDOW_ARG(window, window_obj, 1) \
	RETURN_LONG((zend_long) (uintptr_t) fn(window)); \
}

#define GLFW_NATIVE_OF_MONITOR(fn) \
ZEND_FUNCTION(fn) \
{ \
	zend_object *monitor_obj; \
	ZEND_PARSE_PARAMETERS_START(1, 1) \
		Z_PARAM_OBJ_OF_CLASS(monitor_obj, glfw_ce_GLFWmonitor) \
	ZEND_PARSE_PARAMETERS_END(); \
	GLFW_MONITOR_ARG(monitor, monitor_obj, 1) \
	RETURN_LONG((zend_long) (uintptr_t) fn(monitor)); \
}

#define GLFW_NATIVE_GLOBAL(fn) \
ZEND_FUNCTION(fn) \
{ \
	ZEND_PARSE_PARAMETERS_NONE(); \
	RETURN_LONG((zend_long) (uintptr_t) fn()); \
}

#ifdef __APPLE__
GLFW_NATIVE_OF_WINDOW(glfwGetCocoaWindow)
GLFW_NATIVE_OF_WINDOW(glfwGetCocoaView)
GLFW_NATIVE_OF_MONITOR(glfwGetCocoaMonitor)
GLFW_NATIVE_OF_WINDOW(glfwGetNSGLContext)
#endif

#ifdef __linux__
GLFW_NATIVE_GLOBAL(glfwGetX11Display)
GLFW_NATIVE_OF_WINDOW(glfwGetX11Window)
GLFW_NATIVE_OF_MONITOR(glfwGetX11Adapter)
GLFW_NATIVE_OF_MONITOR(glfwGetX11Monitor)
GLFW_NATIVE_GLOBAL(glfwGetWaylandDisplay)
GLFW_NATIVE_OF_WINDOW(glfwGetWaylandWindow)
GLFW_NATIVE_OF_MONITOR(glfwGetWaylandMonitor)
GLFW_NATIVE_OF_WINDOW(glfwGetGLXContext)
GLFW_NATIVE_OF_WINDOW(glfwGetGLXWindow)
GLFW_NATIVE_GLOBAL(glfwGetEGLDisplay)
GLFW_NATIVE_OF_WINDOW(glfwGetEGLContext)
GLFW_NATIVE_OF_WINDOW(glfwGetEGLSurface)
#endif

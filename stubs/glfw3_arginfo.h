/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: d0ca84ba262f21e2b0386ba5a20977e5fb5f0081 */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwInit, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwTerminate, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwInitHint, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, hint, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetVersion, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(1, major, IS_LONG, 1)
	ZEND_ARG_TYPE_INFO(1, minor, IS_LONG, 1)
	ZEND_ARG_TYPE_INFO(1, rev, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetVersionString, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetError, 0, 0, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(1, description, IS_STRING, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwSetErrorCallback, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, callback, IS_CALLABLE, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetPlatform, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwPlatformSupported, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, platform, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetMonitors, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_glfwGetPrimaryMonitor, 0, 0, GLFWmonitor, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetMonitorPos, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, monitor, GLFWmonitor, 0)
	ZEND_ARG_TYPE_INFO(1, xpos, IS_LONG, 1)
	ZEND_ARG_TYPE_INFO(1, ypos, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetMonitorWorkarea, 0, 5, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, monitor, GLFWmonitor, 0)
	ZEND_ARG_TYPE_INFO(1, xpos, IS_LONG, 1)
	ZEND_ARG_TYPE_INFO(1, ypos, IS_LONG, 1)
	ZEND_ARG_TYPE_INFO(1, width, IS_LONG, 1)
	ZEND_ARG_TYPE_INFO(1, height, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetMonitorPhysicalSize, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, monitor, GLFWmonitor, 0)
	ZEND_ARG_TYPE_INFO(1, widthMM, IS_LONG, 1)
	ZEND_ARG_TYPE_INFO(1, heightMM, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetMonitorContentScale, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, monitor, GLFWmonitor, 0)
	ZEND_ARG_TYPE_INFO(1, xscale, IS_DOUBLE, 1)
	ZEND_ARG_TYPE_INFO(1, yscale, IS_DOUBLE, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetMonitorName, 0, 1, IS_STRING, 1)
	ZEND_ARG_OBJ_INFO(0, monitor, GLFWmonitor, 0)
ZEND_END_ARG_INFO()

#define arginfo_glfwSetMonitorCallback arginfo_glfwSetErrorCallback

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetVideoModes, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_OBJ_INFO(0, monitor, GLFWmonitor, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_glfwGetVideoMode, 0, 1, GLFWvidmode, 1)
	ZEND_ARG_OBJ_INFO(0, monitor, GLFWmonitor, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwSetGamma, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, monitor, GLFWmonitor, 0)
	ZEND_ARG_TYPE_INFO(0, gamma, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_glfwGetGammaRamp, 0, 1, GLFWgammaramp, 1)
	ZEND_ARG_OBJ_INFO(0, monitor, GLFWmonitor, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwSetGammaRamp, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, monitor, GLFWmonitor, 0)
	ZEND_ARG_OBJ_INFO(0, ramp, GLFWgammaramp, 0)
ZEND_END_ARG_INFO()

#define arginfo_glfwDefaultWindowHints arginfo_glfwTerminate

#define arginfo_glfwWindowHint arginfo_glfwInitHint

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwWindowHintString, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, hint, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_glfwCreateWindow, 0, 3, GLFWwindow, 1)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, title, IS_STRING, 0)
	ZEND_ARG_OBJ_INFO_WITH_DEFAULT_VALUE(0, monitor, GLFWmonitor, 1, "null")
	ZEND_ARG_OBJ_INFO_WITH_DEFAULT_VALUE(0, share, GLFWwindow, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwDestroyWindow, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwWindowShouldClose, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwSetWindowShouldClose, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
	ZEND_ARG_TYPE_INFO(0, value, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetWindowTitle, 0, 1, IS_STRING, 1)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwSetWindowTitle, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
	ZEND_ARG_TYPE_INFO(0, title, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwSetWindowIcon, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
	ZEND_ARG_TYPE_INFO(0, images, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetWindowPos, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
	ZEND_ARG_TYPE_INFO(1, xpos, IS_LONG, 1)
	ZEND_ARG_TYPE_INFO(1, ypos, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwSetWindowPos, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
	ZEND_ARG_TYPE_INFO(0, xpos, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, ypos, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetWindowSize, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
	ZEND_ARG_TYPE_INFO(1, width, IS_LONG, 1)
	ZEND_ARG_TYPE_INFO(1, height, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwSetWindowSizeLimits, 0, 5, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
	ZEND_ARG_TYPE_INFO(0, minwidth, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, minheight, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, maxwidth, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, maxheight, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwSetWindowAspectRatio, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
	ZEND_ARG_TYPE_INFO(0, numer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, denom, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwSetWindowSize, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glfwGetFramebufferSize arginfo_glfwGetWindowSize

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetWindowFrameSize, 0, 5, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
	ZEND_ARG_TYPE_INFO(1, left, IS_LONG, 1)
	ZEND_ARG_TYPE_INFO(1, top, IS_LONG, 1)
	ZEND_ARG_TYPE_INFO(1, right, IS_LONG, 1)
	ZEND_ARG_TYPE_INFO(1, bottom, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetWindowContentScale, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
	ZEND_ARG_TYPE_INFO(1, xscale, IS_DOUBLE, 1)
	ZEND_ARG_TYPE_INFO(1, yscale, IS_DOUBLE, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetWindowOpacity, 0, 1, IS_DOUBLE, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwSetWindowOpacity, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
	ZEND_ARG_TYPE_INFO(0, opacity, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_glfwIconifyWindow arginfo_glfwDestroyWindow

#define arginfo_glfwRestoreWindow arginfo_glfwDestroyWindow

#define arginfo_glfwMaximizeWindow arginfo_glfwDestroyWindow

#define arginfo_glfwShowWindow arginfo_glfwDestroyWindow

#define arginfo_glfwHideWindow arginfo_glfwDestroyWindow

#define arginfo_glfwFocusWindow arginfo_glfwDestroyWindow

#define arginfo_glfwRequestWindowAttention arginfo_glfwDestroyWindow

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_glfwGetWindowMonitor, 0, 1, GLFWmonitor, 1)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwSetWindowMonitor, 0, 7, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
	ZEND_ARG_OBJ_INFO(0, monitor, GLFWmonitor, 1)
	ZEND_ARG_TYPE_INFO(0, xpos, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, ypos, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, refreshRate, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetWindowAttrib, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
	ZEND_ARG_TYPE_INFO(0, attrib, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwSetWindowAttrib, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
	ZEND_ARG_TYPE_INFO(0, attrib, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwSetWindowPosCallback, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
	ZEND_ARG_TYPE_INFO(0, callback, IS_CALLABLE, 1)
ZEND_END_ARG_INFO()

#define arginfo_glfwSetWindowSizeCallback arginfo_glfwSetWindowPosCallback

#define arginfo_glfwSetWindowCloseCallback arginfo_glfwSetWindowPosCallback

#define arginfo_glfwSetWindowRefreshCallback arginfo_glfwSetWindowPosCallback

#define arginfo_glfwSetWindowFocusCallback arginfo_glfwSetWindowPosCallback

#define arginfo_glfwSetWindowIconifyCallback arginfo_glfwSetWindowPosCallback

#define arginfo_glfwSetWindowMaximizeCallback arginfo_glfwSetWindowPosCallback

#define arginfo_glfwSetFramebufferSizeCallback arginfo_glfwSetWindowPosCallback

#define arginfo_glfwSetWindowContentScaleCallback arginfo_glfwSetWindowPosCallback

#define arginfo_glfwPollEvents arginfo_glfwTerminate

#define arginfo_glfwWaitEvents arginfo_glfwTerminate

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwWaitEventsTimeout, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, timeout, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_glfwPostEmptyEvent arginfo_glfwTerminate

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetTime, 0, 0, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwSetTime, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, time, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_glfwGetTimerValue arginfo_glfwGetPlatform

#define arginfo_glfwGetTimerFrequency arginfo_glfwGetPlatform

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwMakeContextCurrent, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_glfwGetCurrentContext, 0, 0, GLFWwindow, 1)
ZEND_END_ARG_INFO()

#define arginfo_glfwSwapBuffers arginfo_glfwDestroyWindow

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwSwapInterval, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, interval, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwExtensionSupported, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, extension, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetProcAddress, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, procname, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwInitVulkanLoader, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, loader, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glfwVulkanSupported arginfo_glfwInit

#define arginfo_glfwGetRequiredInstanceExtensions arginfo_glfwGetMonitors

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetPhysicalDevicePresentationSupport, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, instance, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, queuefamily, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetInstanceProcAddress, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, instance, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, procname, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwCreateWindowSurface, 0, 4, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, instance, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
	ZEND_ARG_TYPE_INFO(0, allocator, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, surface, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_GLFWwindow___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GLFWwindow_pointer arginfo_glfwGetPlatform

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GLFWwindow_fromPointer, 0, 1, IS_STATIC, 0)
	ZEND_ARG_TYPE_INFO(0, pointer, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GLFWmonitor___construct arginfo_class_GLFWwindow___construct

#define arginfo_class_GLFWmonitor_pointer arginfo_glfwGetPlatform

#define arginfo_class_GLFWmonitor_fromPointer arginfo_class_GLFWwindow_fromPointer

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_GLFWgammaramp___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, red, IS_ARRAY, 0, "[]")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, green, IS_ARRAY, 0, "[]")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, blue, IS_ARRAY, 0, "[]")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_GLFWimage___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, width, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, height, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, pixels, IS_STRING, 0, "\"\"")
ZEND_END_ARG_INFO()

ZEND_FUNCTION(glfwInit);
ZEND_FUNCTION(glfwTerminate);
ZEND_FUNCTION(glfwInitHint);
ZEND_FUNCTION(glfwGetVersion);
ZEND_FUNCTION(glfwGetVersionString);
ZEND_FUNCTION(glfwGetError);
ZEND_FUNCTION(glfwSetErrorCallback);
ZEND_FUNCTION(glfwGetPlatform);
ZEND_FUNCTION(glfwPlatformSupported);
ZEND_FUNCTION(glfwGetMonitors);
ZEND_FUNCTION(glfwGetPrimaryMonitor);
ZEND_FUNCTION(glfwGetMonitorPos);
ZEND_FUNCTION(glfwGetMonitorWorkarea);
ZEND_FUNCTION(glfwGetMonitorPhysicalSize);
ZEND_FUNCTION(glfwGetMonitorContentScale);
ZEND_FUNCTION(glfwGetMonitorName);
ZEND_FUNCTION(glfwSetMonitorCallback);
ZEND_FUNCTION(glfwGetVideoModes);
ZEND_FUNCTION(glfwGetVideoMode);
ZEND_FUNCTION(glfwSetGamma);
ZEND_FUNCTION(glfwGetGammaRamp);
ZEND_FUNCTION(glfwSetGammaRamp);
ZEND_FUNCTION(glfwDefaultWindowHints);
ZEND_FUNCTION(glfwWindowHint);
ZEND_FUNCTION(glfwWindowHintString);
ZEND_FUNCTION(glfwCreateWindow);
ZEND_FUNCTION(glfwDestroyWindow);
ZEND_FUNCTION(glfwWindowShouldClose);
ZEND_FUNCTION(glfwSetWindowShouldClose);
ZEND_FUNCTION(glfwGetWindowTitle);
ZEND_FUNCTION(glfwSetWindowTitle);
ZEND_FUNCTION(glfwSetWindowIcon);
ZEND_FUNCTION(glfwGetWindowPos);
ZEND_FUNCTION(glfwSetWindowPos);
ZEND_FUNCTION(glfwGetWindowSize);
ZEND_FUNCTION(glfwSetWindowSizeLimits);
ZEND_FUNCTION(glfwSetWindowAspectRatio);
ZEND_FUNCTION(glfwSetWindowSize);
ZEND_FUNCTION(glfwGetFramebufferSize);
ZEND_FUNCTION(glfwGetWindowFrameSize);
ZEND_FUNCTION(glfwGetWindowContentScale);
ZEND_FUNCTION(glfwGetWindowOpacity);
ZEND_FUNCTION(glfwSetWindowOpacity);
ZEND_FUNCTION(glfwIconifyWindow);
ZEND_FUNCTION(glfwRestoreWindow);
ZEND_FUNCTION(glfwMaximizeWindow);
ZEND_FUNCTION(glfwShowWindow);
ZEND_FUNCTION(glfwHideWindow);
ZEND_FUNCTION(glfwFocusWindow);
ZEND_FUNCTION(glfwRequestWindowAttention);
ZEND_FUNCTION(glfwGetWindowMonitor);
ZEND_FUNCTION(glfwSetWindowMonitor);
ZEND_FUNCTION(glfwGetWindowAttrib);
ZEND_FUNCTION(glfwSetWindowAttrib);
ZEND_FUNCTION(glfwSetWindowPosCallback);
ZEND_FUNCTION(glfwSetWindowSizeCallback);
ZEND_FUNCTION(glfwSetWindowCloseCallback);
ZEND_FUNCTION(glfwSetWindowRefreshCallback);
ZEND_FUNCTION(glfwSetWindowFocusCallback);
ZEND_FUNCTION(glfwSetWindowIconifyCallback);
ZEND_FUNCTION(glfwSetWindowMaximizeCallback);
ZEND_FUNCTION(glfwSetFramebufferSizeCallback);
ZEND_FUNCTION(glfwSetWindowContentScaleCallback);
ZEND_FUNCTION(glfwPollEvents);
ZEND_FUNCTION(glfwWaitEvents);
ZEND_FUNCTION(glfwWaitEventsTimeout);
ZEND_FUNCTION(glfwPostEmptyEvent);
ZEND_FUNCTION(glfwGetTime);
ZEND_FUNCTION(glfwSetTime);
ZEND_FUNCTION(glfwGetTimerValue);
ZEND_FUNCTION(glfwGetTimerFrequency);
ZEND_FUNCTION(glfwMakeContextCurrent);
ZEND_FUNCTION(glfwGetCurrentContext);
ZEND_FUNCTION(glfwSwapBuffers);
ZEND_FUNCTION(glfwSwapInterval);
ZEND_FUNCTION(glfwExtensionSupported);
ZEND_FUNCTION(glfwGetProcAddress);
ZEND_FUNCTION(glfwInitVulkanLoader);
ZEND_FUNCTION(glfwVulkanSupported);
ZEND_FUNCTION(glfwGetRequiredInstanceExtensions);
ZEND_FUNCTION(glfwGetPhysicalDevicePresentationSupport);
ZEND_FUNCTION(glfwGetInstanceProcAddress);
ZEND_FUNCTION(glfwCreateWindowSurface);
ZEND_METHOD(GLFWwindow, __construct);
ZEND_METHOD(GLFWwindow, pointer);
ZEND_METHOD(GLFWwindow, fromPointer);
ZEND_METHOD(GLFWmonitor, __construct);
ZEND_METHOD(GLFWmonitor, pointer);
ZEND_METHOD(GLFWmonitor, fromPointer);
ZEND_METHOD(GLFWgammaramp, __construct);
ZEND_METHOD(GLFWimage, __construct);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(glfwInit, arginfo_glfwInit)
	ZEND_FE(glfwTerminate, arginfo_glfwTerminate)
	ZEND_FE(glfwInitHint, arginfo_glfwInitHint)
	ZEND_FE(glfwGetVersion, arginfo_glfwGetVersion)
	ZEND_FE(glfwGetVersionString, arginfo_glfwGetVersionString)
	ZEND_FE(glfwGetError, arginfo_glfwGetError)
	ZEND_FE(glfwSetErrorCallback, arginfo_glfwSetErrorCallback)
	ZEND_FE(glfwGetPlatform, arginfo_glfwGetPlatform)
	ZEND_FE(glfwPlatformSupported, arginfo_glfwPlatformSupported)
	ZEND_FE(glfwGetMonitors, arginfo_glfwGetMonitors)
	ZEND_FE(glfwGetPrimaryMonitor, arginfo_glfwGetPrimaryMonitor)
	ZEND_FE(glfwGetMonitorPos, arginfo_glfwGetMonitorPos)
	ZEND_FE(glfwGetMonitorWorkarea, arginfo_glfwGetMonitorWorkarea)
	ZEND_FE(glfwGetMonitorPhysicalSize, arginfo_glfwGetMonitorPhysicalSize)
	ZEND_FE(glfwGetMonitorContentScale, arginfo_glfwGetMonitorContentScale)
	ZEND_FE(glfwGetMonitorName, arginfo_glfwGetMonitorName)
	ZEND_FE(glfwSetMonitorCallback, arginfo_glfwSetMonitorCallback)
	ZEND_FE(glfwGetVideoModes, arginfo_glfwGetVideoModes)
	ZEND_FE(glfwGetVideoMode, arginfo_glfwGetVideoMode)
	ZEND_FE(glfwSetGamma, arginfo_glfwSetGamma)
	ZEND_FE(glfwGetGammaRamp, arginfo_glfwGetGammaRamp)
	ZEND_FE(glfwSetGammaRamp, arginfo_glfwSetGammaRamp)
	ZEND_FE(glfwDefaultWindowHints, arginfo_glfwDefaultWindowHints)
	ZEND_FE(glfwWindowHint, arginfo_glfwWindowHint)
	ZEND_FE(glfwWindowHintString, arginfo_glfwWindowHintString)
	ZEND_FE(glfwCreateWindow, arginfo_glfwCreateWindow)
	ZEND_FE(glfwDestroyWindow, arginfo_glfwDestroyWindow)
	ZEND_FE(glfwWindowShouldClose, arginfo_glfwWindowShouldClose)
	ZEND_FE(glfwSetWindowShouldClose, arginfo_glfwSetWindowShouldClose)
	ZEND_FE(glfwGetWindowTitle, arginfo_glfwGetWindowTitle)
	ZEND_FE(glfwSetWindowTitle, arginfo_glfwSetWindowTitle)
	ZEND_FE(glfwSetWindowIcon, arginfo_glfwSetWindowIcon)
	ZEND_FE(glfwGetWindowPos, arginfo_glfwGetWindowPos)
	ZEND_FE(glfwSetWindowPos, arginfo_glfwSetWindowPos)
	ZEND_FE(glfwGetWindowSize, arginfo_glfwGetWindowSize)
	ZEND_FE(glfwSetWindowSizeLimits, arginfo_glfwSetWindowSizeLimits)
	ZEND_FE(glfwSetWindowAspectRatio, arginfo_glfwSetWindowAspectRatio)
	ZEND_FE(glfwSetWindowSize, arginfo_glfwSetWindowSize)
	ZEND_FE(glfwGetFramebufferSize, arginfo_glfwGetFramebufferSize)
	ZEND_FE(glfwGetWindowFrameSize, arginfo_glfwGetWindowFrameSize)
	ZEND_FE(glfwGetWindowContentScale, arginfo_glfwGetWindowContentScale)
	ZEND_FE(glfwGetWindowOpacity, arginfo_glfwGetWindowOpacity)
	ZEND_FE(glfwSetWindowOpacity, arginfo_glfwSetWindowOpacity)
	ZEND_FE(glfwIconifyWindow, arginfo_glfwIconifyWindow)
	ZEND_FE(glfwRestoreWindow, arginfo_glfwRestoreWindow)
	ZEND_FE(glfwMaximizeWindow, arginfo_glfwMaximizeWindow)
	ZEND_FE(glfwShowWindow, arginfo_glfwShowWindow)
	ZEND_FE(glfwHideWindow, arginfo_glfwHideWindow)
	ZEND_FE(glfwFocusWindow, arginfo_glfwFocusWindow)
	ZEND_FE(glfwRequestWindowAttention, arginfo_glfwRequestWindowAttention)
	ZEND_FE(glfwGetWindowMonitor, arginfo_glfwGetWindowMonitor)
	ZEND_FE(glfwSetWindowMonitor, arginfo_glfwSetWindowMonitor)
	ZEND_FE(glfwGetWindowAttrib, arginfo_glfwGetWindowAttrib)
	ZEND_FE(glfwSetWindowAttrib, arginfo_glfwSetWindowAttrib)
	ZEND_FE(glfwSetWindowPosCallback, arginfo_glfwSetWindowPosCallback)
	ZEND_FE(glfwSetWindowSizeCallback, arginfo_glfwSetWindowSizeCallback)
	ZEND_FE(glfwSetWindowCloseCallback, arginfo_glfwSetWindowCloseCallback)
	ZEND_FE(glfwSetWindowRefreshCallback, arginfo_glfwSetWindowRefreshCallback)
	ZEND_FE(glfwSetWindowFocusCallback, arginfo_glfwSetWindowFocusCallback)
	ZEND_FE(glfwSetWindowIconifyCallback, arginfo_glfwSetWindowIconifyCallback)
	ZEND_FE(glfwSetWindowMaximizeCallback, arginfo_glfwSetWindowMaximizeCallback)
	ZEND_FE(glfwSetFramebufferSizeCallback, arginfo_glfwSetFramebufferSizeCallback)
	ZEND_FE(glfwSetWindowContentScaleCallback, arginfo_glfwSetWindowContentScaleCallback)
	ZEND_FE(glfwPollEvents, arginfo_glfwPollEvents)
	ZEND_FE(glfwWaitEvents, arginfo_glfwWaitEvents)
	ZEND_FE(glfwWaitEventsTimeout, arginfo_glfwWaitEventsTimeout)
	ZEND_FE(glfwPostEmptyEvent, arginfo_glfwPostEmptyEvent)
	ZEND_FE(glfwGetTime, arginfo_glfwGetTime)
	ZEND_FE(glfwSetTime, arginfo_glfwSetTime)
	ZEND_FE(glfwGetTimerValue, arginfo_glfwGetTimerValue)
	ZEND_FE(glfwGetTimerFrequency, arginfo_glfwGetTimerFrequency)
	ZEND_FE(glfwMakeContextCurrent, arginfo_glfwMakeContextCurrent)
	ZEND_FE(glfwGetCurrentContext, arginfo_glfwGetCurrentContext)
	ZEND_FE(glfwSwapBuffers, arginfo_glfwSwapBuffers)
	ZEND_FE(glfwSwapInterval, arginfo_glfwSwapInterval)
	ZEND_FE(glfwExtensionSupported, arginfo_glfwExtensionSupported)
	ZEND_FE(glfwGetProcAddress, arginfo_glfwGetProcAddress)
	ZEND_FE(glfwInitVulkanLoader, arginfo_glfwInitVulkanLoader)
	ZEND_FE(glfwVulkanSupported, arginfo_glfwVulkanSupported)
	ZEND_FE(glfwGetRequiredInstanceExtensions, arginfo_glfwGetRequiredInstanceExtensions)
	ZEND_FE(glfwGetPhysicalDevicePresentationSupport, arginfo_glfwGetPhysicalDevicePresentationSupport)
	ZEND_FE(glfwGetInstanceProcAddress, arginfo_glfwGetInstanceProcAddress)
	ZEND_FE(glfwCreateWindowSurface, arginfo_glfwCreateWindowSurface)
	ZEND_FE_END
};

static const zend_function_entry class_GLFWwindow_methods[] = {
	ZEND_ME(GLFWwindow, __construct, arginfo_class_GLFWwindow___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(GLFWwindow, pointer, arginfo_class_GLFWwindow_pointer, ZEND_ACC_PUBLIC)
	ZEND_ME(GLFWwindow, fromPointer, arginfo_class_GLFWwindow_fromPointer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};

static const zend_function_entry class_GLFWmonitor_methods[] = {
	ZEND_ME(GLFWmonitor, __construct, arginfo_class_GLFWmonitor___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(GLFWmonitor, pointer, arginfo_class_GLFWmonitor_pointer, ZEND_ACC_PUBLIC)
	ZEND_ME(GLFWmonitor, fromPointer, arginfo_class_GLFWmonitor_fromPointer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};

static const zend_function_entry class_GLFWgammaramp_methods[] = {
	ZEND_ME(GLFWgammaramp, __construct, arginfo_class_GLFWgammaramp___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_GLFWimage_methods[] = {
	ZEND_ME(GLFWimage, __construct, arginfo_class_GLFWimage___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static void register_glfw3_symbols(int module_number)
{
	REGISTER_LONG_CONSTANT("GLFW_VERSION_MAJOR", GLFW_VERSION_MAJOR, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_VERSION_MINOR", GLFW_VERSION_MINOR, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_VERSION_REVISION", GLFW_VERSION_REVISION, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_TRUE", GLFW_TRUE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_FALSE", GLFW_FALSE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_DONT_CARE", GLFW_DONT_CARE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_NO_ERROR", GLFW_NO_ERROR, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_NOT_INITIALIZED", GLFW_NOT_INITIALIZED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_NO_CURRENT_CONTEXT", GLFW_NO_CURRENT_CONTEXT, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_INVALID_ENUM", GLFW_INVALID_ENUM, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_INVALID_VALUE", GLFW_INVALID_VALUE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_OUT_OF_MEMORY", GLFW_OUT_OF_MEMORY, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_API_UNAVAILABLE", GLFW_API_UNAVAILABLE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_VERSION_UNAVAILABLE", GLFW_VERSION_UNAVAILABLE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_PLATFORM_ERROR", GLFW_PLATFORM_ERROR, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_FORMAT_UNAVAILABLE", GLFW_FORMAT_UNAVAILABLE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_NO_WINDOW_CONTEXT", GLFW_NO_WINDOW_CONTEXT, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_FEATURE_UNAVAILABLE", GLFW_FEATURE_UNAVAILABLE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_FEATURE_UNIMPLEMENTED", GLFW_FEATURE_UNIMPLEMENTED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_PLATFORM_UNAVAILABLE", GLFW_PLATFORM_UNAVAILABLE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_FOCUSED", GLFW_FOCUSED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_ICONIFIED", GLFW_ICONIFIED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_RESIZABLE", GLFW_RESIZABLE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_VISIBLE", GLFW_VISIBLE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_DECORATED", GLFW_DECORATED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_AUTO_ICONIFY", GLFW_AUTO_ICONIFY, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_FLOATING", GLFW_FLOATING, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_MAXIMIZED", GLFW_MAXIMIZED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_CENTER_CURSOR", GLFW_CENTER_CURSOR, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_TRANSPARENT_FRAMEBUFFER", GLFW_TRANSPARENT_FRAMEBUFFER, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_HOVERED", GLFW_HOVERED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_FOCUS_ON_SHOW", GLFW_FOCUS_ON_SHOW, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_MOUSE_PASSTHROUGH", GLFW_MOUSE_PASSTHROUGH, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_POSITION_X", GLFW_POSITION_X, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_POSITION_Y", GLFW_POSITION_Y, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_RED_BITS", GLFW_RED_BITS, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_GREEN_BITS", GLFW_GREEN_BITS, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_BLUE_BITS", GLFW_BLUE_BITS, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_ALPHA_BITS", GLFW_ALPHA_BITS, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_DEPTH_BITS", GLFW_DEPTH_BITS, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_STENCIL_BITS", GLFW_STENCIL_BITS, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_ACCUM_RED_BITS", GLFW_ACCUM_RED_BITS, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_ACCUM_GREEN_BITS", GLFW_ACCUM_GREEN_BITS, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_ACCUM_BLUE_BITS", GLFW_ACCUM_BLUE_BITS, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_ACCUM_ALPHA_BITS", GLFW_ACCUM_ALPHA_BITS, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_AUX_BUFFERS", GLFW_AUX_BUFFERS, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_STEREO", GLFW_STEREO, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_SAMPLES", GLFW_SAMPLES, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_SRGB_CAPABLE", GLFW_SRGB_CAPABLE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_REFRESH_RATE", GLFW_REFRESH_RATE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_DOUBLEBUFFER", GLFW_DOUBLEBUFFER, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_CLIENT_API", GLFW_CLIENT_API, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_CONTEXT_VERSION_MAJOR", GLFW_CONTEXT_VERSION_MAJOR, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_CONTEXT_VERSION_MINOR", GLFW_CONTEXT_VERSION_MINOR, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_CONTEXT_REVISION", GLFW_CONTEXT_REVISION, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_CONTEXT_ROBUSTNESS", GLFW_CONTEXT_ROBUSTNESS, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_OPENGL_FORWARD_COMPAT", GLFW_OPENGL_FORWARD_COMPAT, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_CONTEXT_DEBUG", GLFW_CONTEXT_DEBUG, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_OPENGL_DEBUG_CONTEXT", GLFW_OPENGL_DEBUG_CONTEXT, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_OPENGL_PROFILE", GLFW_OPENGL_PROFILE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_CONTEXT_RELEASE_BEHAVIOR", GLFW_CONTEXT_RELEASE_BEHAVIOR, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_CONTEXT_NO_ERROR", GLFW_CONTEXT_NO_ERROR, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_CONTEXT_CREATION_API", GLFW_CONTEXT_CREATION_API, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_SCALE_TO_MONITOR", GLFW_SCALE_TO_MONITOR, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_SCALE_FRAMEBUFFER", GLFW_SCALE_FRAMEBUFFER, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_COCOA_RETINA_FRAMEBUFFER", GLFW_COCOA_RETINA_FRAMEBUFFER, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_COCOA_FRAME_NAME", GLFW_COCOA_FRAME_NAME, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_COCOA_GRAPHICS_SWITCHING", GLFW_COCOA_GRAPHICS_SWITCHING, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_X11_CLASS_NAME", GLFW_X11_CLASS_NAME, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_X11_INSTANCE_NAME", GLFW_X11_INSTANCE_NAME, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_WIN32_KEYBOARD_MENU", GLFW_WIN32_KEYBOARD_MENU, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_WIN32_SHOWDEFAULT", GLFW_WIN32_SHOWDEFAULT, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_WAYLAND_APP_ID", GLFW_WAYLAND_APP_ID, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_NO_API", GLFW_NO_API, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_OPENGL_API", GLFW_OPENGL_API, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_OPENGL_ES_API", GLFW_OPENGL_ES_API, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_NO_ROBUSTNESS", GLFW_NO_ROBUSTNESS, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_NO_RESET_NOTIFICATION", GLFW_NO_RESET_NOTIFICATION, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_LOSE_CONTEXT_ON_RESET", GLFW_LOSE_CONTEXT_ON_RESET, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_OPENGL_ANY_PROFILE", GLFW_OPENGL_ANY_PROFILE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_OPENGL_CORE_PROFILE", GLFW_OPENGL_CORE_PROFILE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_OPENGL_COMPAT_PROFILE", GLFW_OPENGL_COMPAT_PROFILE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_ANY_RELEASE_BEHAVIOR", GLFW_ANY_RELEASE_BEHAVIOR, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_RELEASE_BEHAVIOR_FLUSH", GLFW_RELEASE_BEHAVIOR_FLUSH, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_RELEASE_BEHAVIOR_NONE", GLFW_RELEASE_BEHAVIOR_NONE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_NATIVE_CONTEXT_API", GLFW_NATIVE_CONTEXT_API, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_EGL_CONTEXT_API", GLFW_EGL_CONTEXT_API, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_OSMESA_CONTEXT_API", GLFW_OSMESA_CONTEXT_API, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_ANGLE_PLATFORM_TYPE_NONE", GLFW_ANGLE_PLATFORM_TYPE_NONE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_ANGLE_PLATFORM_TYPE_OPENGL", GLFW_ANGLE_PLATFORM_TYPE_OPENGL, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_ANGLE_PLATFORM_TYPE_OPENGLES", GLFW_ANGLE_PLATFORM_TYPE_OPENGLES, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_ANGLE_PLATFORM_TYPE_D3D9", GLFW_ANGLE_PLATFORM_TYPE_D3D9, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_ANGLE_PLATFORM_TYPE_D3D11", GLFW_ANGLE_PLATFORM_TYPE_D3D11, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_ANGLE_PLATFORM_TYPE_VULKAN", GLFW_ANGLE_PLATFORM_TYPE_VULKAN, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_ANGLE_PLATFORM_TYPE_METAL", GLFW_ANGLE_PLATFORM_TYPE_METAL, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_WAYLAND_PREFER_LIBDECOR", GLFW_WAYLAND_PREFER_LIBDECOR, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_WAYLAND_DISABLE_LIBDECOR", GLFW_WAYLAND_DISABLE_LIBDECOR, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_ANY_POSITION", GLFW_ANY_POSITION, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_ANGLE_PLATFORM_TYPE", GLFW_ANGLE_PLATFORM_TYPE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_PLATFORM", GLFW_PLATFORM, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_COCOA_CHDIR_RESOURCES", GLFW_COCOA_CHDIR_RESOURCES, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_COCOA_MENUBAR", GLFW_COCOA_MENUBAR, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_X11_XCB_VULKAN_SURFACE", GLFW_X11_XCB_VULKAN_SURFACE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_WAYLAND_LIBDECOR", GLFW_WAYLAND_LIBDECOR, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_ANY_PLATFORM", GLFW_ANY_PLATFORM, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_PLATFORM_WIN32", GLFW_PLATFORM_WIN32, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_PLATFORM_COCOA", GLFW_PLATFORM_COCOA, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_PLATFORM_WAYLAND", GLFW_PLATFORM_WAYLAND, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_PLATFORM_X11", GLFW_PLATFORM_X11, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_PLATFORM_NULL", GLFW_PLATFORM_NULL, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_CONNECTED", GLFW_CONNECTED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLFW_DISCONNECTED", GLFW_DISCONNECTED, CONST_PERSISTENT);
}

static zend_class_entry *register_class_GLFWwindow(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "GLFWwindow", class_GLFWwindow_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	return class_entry;
}

static zend_class_entry *register_class_GLFWmonitor(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "GLFWmonitor", class_GLFWmonitor_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	return class_entry;
}

static zend_class_entry *register_class_GLFWvidmode(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "GLFWvidmode", NULL);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	zval property_width_default_value;
	ZVAL_LONG(&property_width_default_value, 0);
	zend_string *property_width_name = zend_string_init("width", sizeof("width") - 1, 1);
	zend_declare_typed_property(class_entry, property_width_name, &property_width_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_width_name);

	zval property_height_default_value;
	ZVAL_LONG(&property_height_default_value, 0);
	zend_string *property_height_name = zend_string_init("height", sizeof("height") - 1, 1);
	zend_declare_typed_property(class_entry, property_height_name, &property_height_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_height_name);

	zval property_redBits_default_value;
	ZVAL_LONG(&property_redBits_default_value, 0);
	zend_string *property_redBits_name = zend_string_init("redBits", sizeof("redBits") - 1, 1);
	zend_declare_typed_property(class_entry, property_redBits_name, &property_redBits_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_redBits_name);

	zval property_greenBits_default_value;
	ZVAL_LONG(&property_greenBits_default_value, 0);
	zend_string *property_greenBits_name = zend_string_init("greenBits", sizeof("greenBits") - 1, 1);
	zend_declare_typed_property(class_entry, property_greenBits_name, &property_greenBits_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_greenBits_name);

	zval property_blueBits_default_value;
	ZVAL_LONG(&property_blueBits_default_value, 0);
	zend_string *property_blueBits_name = zend_string_init("blueBits", sizeof("blueBits") - 1, 1);
	zend_declare_typed_property(class_entry, property_blueBits_name, &property_blueBits_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_blueBits_name);

	zval property_refreshRate_default_value;
	ZVAL_LONG(&property_refreshRate_default_value, 0);
	zend_string *property_refreshRate_name = zend_string_init("refreshRate", sizeof("refreshRate") - 1, 1);
	zend_declare_typed_property(class_entry, property_refreshRate_name, &property_refreshRate_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_refreshRate_name);

	return class_entry;
}

static zend_class_entry *register_class_GLFWgammaramp(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "GLFWgammaramp", class_GLFWgammaramp_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	zval property_red_default_value;
	ZVAL_EMPTY_ARRAY(&property_red_default_value);
	zend_string *property_red_name = zend_string_init("red", sizeof("red") - 1, 1);
	zend_declare_typed_property(class_entry, property_red_name, &property_red_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_ARRAY));
	zend_string_release(property_red_name);

	zval property_green_default_value;
	ZVAL_EMPTY_ARRAY(&property_green_default_value);
	zend_string *property_green_name = zend_string_init("green", sizeof("green") - 1, 1);
	zend_declare_typed_property(class_entry, property_green_name, &property_green_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_ARRAY));
	zend_string_release(property_green_name);

	zval property_blue_default_value;
	ZVAL_EMPTY_ARRAY(&property_blue_default_value);
	zend_string *property_blue_name = zend_string_init("blue", sizeof("blue") - 1, 1);
	zend_declare_typed_property(class_entry, property_blue_name, &property_blue_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_ARRAY));
	zend_string_release(property_blue_name);

	return class_entry;
}

static zend_class_entry *register_class_GLFWimage(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "GLFWimage", class_GLFWimage_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	zval property_width_default_value;
	ZVAL_LONG(&property_width_default_value, 0);
	zend_string *property_width_name = zend_string_init("width", sizeof("width") - 1, 1);
	zend_declare_typed_property(class_entry, property_width_name, &property_width_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_width_name);

	zval property_height_default_value;
	ZVAL_LONG(&property_height_default_value, 0);
	zend_string *property_height_name = zend_string_init("height", sizeof("height") - 1, 1);
	zend_declare_typed_property(class_entry, property_height_name, &property_height_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_height_name);

	zval property_pixels_default_value;
	ZVAL_EMPTY_STRING(&property_pixels_default_value);
	zend_string *property_pixels_name = zend_string_init("pixels", sizeof("pixels") - 1, 1);
	zend_declare_typed_property(class_entry, property_pixels_name, &property_pixels_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_STRING));
	zend_string_release(property_pixels_name);

	return class_entry;
}


extern zend_class_entry *glfw_glfw_window_glfwwindow_ce;

ZEPHIR_INIT_CLASS(Glfw_GLFW_Window_GLFWWindow);

PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwDefaultWindowHints);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwWindowHint);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwWindowHintString);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwCreateWindow);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwDestroyWindow);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwWindowShouldClose);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowShouldClose);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwGetWindowTitle);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowTitle);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowIcon);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwGetWindowPos);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowPos);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwGetWindowSize);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowSizeLimits);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowAspectRatio);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowSize);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwGetFramebufferSize);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwGetWindowFrameSize);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwGetWindowContentScale);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwGetWindowOpacity);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowOpacity);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwIconifyWindow);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwRestoreWindow);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwMaximizeWindow);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwShowWindow);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwHideWindow);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwFocusWindow);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwRequestWindowAttention);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwGetWindowMonitor);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowMonitor);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwGetWindowAttrib);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowAttrib);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowUserPointer);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwGetWindowUserPointer);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowPosCallback);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowSizeCallback);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowCloseCallback);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowRefreshCallback);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowFocusCallback);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowIconifyCallback);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowMaximizeCallback);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwSetFramebufferSizeCallback);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowContentScaleCallback);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwPollEvents);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwWaitEvents);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwWaitEventsTimeout);
PHP_METHOD(Glfw_GLFW_Window_GLFWWindow, glfwPostEmptyEvent);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwdefaultwindowhints, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwwindowhint, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, hint, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwwindowhintstring, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, hint, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwcreatewindow, 0, 3, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, title, IS_STRING, 0)
	ZEND_ARG_INFO(0, monitor)
	ZEND_ARG_INFO(0, share)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwdestroywindow, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwwindowshouldclose, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwsetwindowshouldclose, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwgetwindowtitle, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwsetwindowtitle, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, title, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwsetwindowicon, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_ARRAY_INFO(0, images, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwgetwindowpos, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwsetwindowpos, 0, 3, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, xpos, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, ypos, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwgetwindowsize, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwsetwindowsizelimits, 0, 5, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, minwidth, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, minheight, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, maxwidth, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, maxheight, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwsetwindowaspectratio, 0, 3, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, numer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, denom, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwsetwindowsize, 0, 3, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwgetframebuffersize, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwgetwindowframesize, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwgetwindowcontentscale, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwgetwindowopacity, 0, 1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwsetwindowopacity, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, opacity, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwiconifywindow, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwrestorewindow, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwmaximizewindow, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwshowwindow, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwhidewindow, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwfocuswindow, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwrequestwindowattention, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwgetwindowmonitor, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwsetwindowmonitor, 0, 7, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_INFO(0, monitor)
	ZEND_ARG_TYPE_INFO(0, xpos, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, ypos, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, refreshRate, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwgetwindowattrib, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, attrib, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwsetwindowattrib, 0, 3, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, attrib, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwsetwindowuserpointer, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, pointer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwgetwindowuserpointer, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwsetwindowposcallback, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwsetwindowsizecallback, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwsetwindowclosecallback, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwsetwindowrefreshcallback, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwsetwindowfocuscallback, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwsetwindowiconifycallback, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwsetwindowmaximizecallback, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwsetframebuffersizecallback, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwsetwindowcontentscalecallback, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwpollevents, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwwaitevents, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwwaiteventstimeout, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, timeout, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_window_glfwwindow_glfwpostemptyevent, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(glfw_glfw_window_glfwwindow_method_entry) {
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwDefaultWindowHints, arginfo_glfw_glfw_window_glfwwindow_glfwdefaultwindowhints, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwWindowHint, arginfo_glfw_glfw_window_glfwwindow_glfwwindowhint, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwWindowHintString, arginfo_glfw_glfw_window_glfwwindow_glfwwindowhintstring, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwCreateWindow, arginfo_glfw_glfw_window_glfwwindow_glfwcreatewindow, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwDestroyWindow, arginfo_glfw_glfw_window_glfwwindow_glfwdestroywindow, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwWindowShouldClose, arginfo_glfw_glfw_window_glfwwindow_glfwwindowshouldclose, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowShouldClose, arginfo_glfw_glfw_window_glfwwindow_glfwsetwindowshouldclose, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwGetWindowTitle, arginfo_glfw_glfw_window_glfwwindow_glfwgetwindowtitle, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowTitle, arginfo_glfw_glfw_window_glfwwindow_glfwsetwindowtitle, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowIcon, arginfo_glfw_glfw_window_glfwwindow_glfwsetwindowicon, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwGetWindowPos, arginfo_glfw_glfw_window_glfwwindow_glfwgetwindowpos, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowPos, arginfo_glfw_glfw_window_glfwwindow_glfwsetwindowpos, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwGetWindowSize, arginfo_glfw_glfw_window_glfwwindow_glfwgetwindowsize, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowSizeLimits, arginfo_glfw_glfw_window_glfwwindow_glfwsetwindowsizelimits, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowAspectRatio, arginfo_glfw_glfw_window_glfwwindow_glfwsetwindowaspectratio, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowSize, arginfo_glfw_glfw_window_glfwwindow_glfwsetwindowsize, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwGetFramebufferSize, arginfo_glfw_glfw_window_glfwwindow_glfwgetframebuffersize, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwGetWindowFrameSize, arginfo_glfw_glfw_window_glfwwindow_glfwgetwindowframesize, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwGetWindowContentScale, arginfo_glfw_glfw_window_glfwwindow_glfwgetwindowcontentscale, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwGetWindowOpacity, arginfo_glfw_glfw_window_glfwwindow_glfwgetwindowopacity, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowOpacity, arginfo_glfw_glfw_window_glfwwindow_glfwsetwindowopacity, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwIconifyWindow, arginfo_glfw_glfw_window_glfwwindow_glfwiconifywindow, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwRestoreWindow, arginfo_glfw_glfw_window_glfwwindow_glfwrestorewindow, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwMaximizeWindow, arginfo_glfw_glfw_window_glfwwindow_glfwmaximizewindow, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwShowWindow, arginfo_glfw_glfw_window_glfwwindow_glfwshowwindow, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwHideWindow, arginfo_glfw_glfw_window_glfwwindow_glfwhidewindow, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwFocusWindow, arginfo_glfw_glfw_window_glfwwindow_glfwfocuswindow, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwRequestWindowAttention, arginfo_glfw_glfw_window_glfwwindow_glfwrequestwindowattention, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwGetWindowMonitor, arginfo_glfw_glfw_window_glfwwindow_glfwgetwindowmonitor, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowMonitor, arginfo_glfw_glfw_window_glfwwindow_glfwsetwindowmonitor, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwGetWindowAttrib, arginfo_glfw_glfw_window_glfwwindow_glfwgetwindowattrib, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowAttrib, arginfo_glfw_glfw_window_glfwwindow_glfwsetwindowattrib, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowUserPointer, arginfo_glfw_glfw_window_glfwwindow_glfwsetwindowuserpointer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwGetWindowUserPointer, arginfo_glfw_glfw_window_glfwwindow_glfwgetwindowuserpointer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowPosCallback, arginfo_glfw_glfw_window_glfwwindow_glfwsetwindowposcallback, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowSizeCallback, arginfo_glfw_glfw_window_glfwwindow_glfwsetwindowsizecallback, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowCloseCallback, arginfo_glfw_glfw_window_glfwwindow_glfwsetwindowclosecallback, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowRefreshCallback, arginfo_glfw_glfw_window_glfwwindow_glfwsetwindowrefreshcallback, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowFocusCallback, arginfo_glfw_glfw_window_glfwwindow_glfwsetwindowfocuscallback, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowIconifyCallback, arginfo_glfw_glfw_window_glfwwindow_glfwsetwindowiconifycallback, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowMaximizeCallback, arginfo_glfw_glfw_window_glfwwindow_glfwsetwindowmaximizecallback, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwSetFramebufferSizeCallback, arginfo_glfw_glfw_window_glfwwindow_glfwsetframebuffersizecallback, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwSetWindowContentScaleCallback, arginfo_glfw_glfw_window_glfwwindow_glfwsetwindowcontentscalecallback, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwPollEvents, arginfo_glfw_glfw_window_glfwwindow_glfwpollevents, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwWaitEvents, arginfo_glfw_glfw_window_glfwwindow_glfwwaitevents, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwWaitEventsTimeout, arginfo_glfw_glfw_window_glfwwindow_glfwwaiteventstimeout, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Window_GLFWWindow, glfwPostEmptyEvent, arginfo_glfw_glfw_window_glfwwindow_glfwpostemptyevent, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};

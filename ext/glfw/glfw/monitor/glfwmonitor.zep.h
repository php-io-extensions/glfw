
extern zend_class_entry *glfw_glfw_monitor_glfwmonitor_ce;

ZEPHIR_INIT_CLASS(Glfw_GLFW_Monitor_GLFWMonitor);

PHP_METHOD(Glfw_GLFW_Monitor_GLFWMonitor, glfwGetMonitors);
PHP_METHOD(Glfw_GLFW_Monitor_GLFWMonitor, glfwGetPrimaryMonitor);
PHP_METHOD(Glfw_GLFW_Monitor_GLFWMonitor, glfwGetMonitorPos);
PHP_METHOD(Glfw_GLFW_Monitor_GLFWMonitor, glfwGetMonitorWorkarea);
PHP_METHOD(Glfw_GLFW_Monitor_GLFWMonitor, glfwGetMonitorPhysicalSize);
PHP_METHOD(Glfw_GLFW_Monitor_GLFWMonitor, glfwGetMonitorContentScale);
PHP_METHOD(Glfw_GLFW_Monitor_GLFWMonitor, glfwGetMonitorName);
PHP_METHOD(Glfw_GLFW_Monitor_GLFWMonitor, glfwSetMonitorUserPointer);
PHP_METHOD(Glfw_GLFW_Monitor_GLFWMonitor, glfwGetMonitorUserPointer);
PHP_METHOD(Glfw_GLFW_Monitor_GLFWMonitor, glfwSetMonitorCallback);
PHP_METHOD(Glfw_GLFW_Monitor_GLFWMonitor, glfwGetVideoModes);
PHP_METHOD(Glfw_GLFW_Monitor_GLFWMonitor, glfwGetVideoMode);
PHP_METHOD(Glfw_GLFW_Monitor_GLFWMonitor, glfwSetGamma);
PHP_METHOD(Glfw_GLFW_Monitor_GLFWMonitor, glfwGetGammaRamp);
PHP_METHOD(Glfw_GLFW_Monitor_GLFWMonitor, glfwSetGammaRamp);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_monitor_glfwmonitor_glfwgetmonitors, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_monitor_glfwmonitor_glfwgetprimarymonitor, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_monitor_glfwmonitor_glfwgetmonitorpos, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, monitor, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_monitor_glfwmonitor_glfwgetmonitorworkarea, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, monitor, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_monitor_glfwmonitor_glfwgetmonitorphysicalsize, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, monitor, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_monitor_glfwmonitor_glfwgetmonitorcontentscale, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, monitor, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_monitor_glfwmonitor_glfwgetmonitorname, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, monitor, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_monitor_glfwmonitor_glfwsetmonitoruserpointer, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, monitor, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, pointer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_monitor_glfwmonitor_glfwgetmonitoruserpointer, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, monitor, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_monitor_glfwmonitor_glfwsetmonitorcallback, 0, 0, IS_VOID, 0)

	ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_monitor_glfwmonitor_glfwgetvideomodes, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, monitor, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_monitor_glfwmonitor_glfwgetvideomode, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, monitor, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_monitor_glfwmonitor_glfwsetgamma, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, monitor, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, gamma, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_monitor_glfwmonitor_glfwgetgammaramp, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, monitor, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_monitor_glfwmonitor_glfwsetgammaramp, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, monitor, IS_LONG, 0)
	ZEND_ARG_ARRAY_INFO(0, ramp, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(glfw_glfw_monitor_glfwmonitor_method_entry) {
	PHP_ME(Glfw_GLFW_Monitor_GLFWMonitor, glfwGetMonitors, arginfo_glfw_glfw_monitor_glfwmonitor_glfwgetmonitors, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Monitor_GLFWMonitor, glfwGetPrimaryMonitor, arginfo_glfw_glfw_monitor_glfwmonitor_glfwgetprimarymonitor, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Monitor_GLFWMonitor, glfwGetMonitorPos, arginfo_glfw_glfw_monitor_glfwmonitor_glfwgetmonitorpos, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Monitor_GLFWMonitor, glfwGetMonitorWorkarea, arginfo_glfw_glfw_monitor_glfwmonitor_glfwgetmonitorworkarea, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Monitor_GLFWMonitor, glfwGetMonitorPhysicalSize, arginfo_glfw_glfw_monitor_glfwmonitor_glfwgetmonitorphysicalsize, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Monitor_GLFWMonitor, glfwGetMonitorContentScale, arginfo_glfw_glfw_monitor_glfwmonitor_glfwgetmonitorcontentscale, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Monitor_GLFWMonitor, glfwGetMonitorName, arginfo_glfw_glfw_monitor_glfwmonitor_glfwgetmonitorname, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Monitor_GLFWMonitor, glfwSetMonitorUserPointer, arginfo_glfw_glfw_monitor_glfwmonitor_glfwsetmonitoruserpointer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Monitor_GLFWMonitor, glfwGetMonitorUserPointer, arginfo_glfw_glfw_monitor_glfwmonitor_glfwgetmonitoruserpointer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Monitor_GLFWMonitor, glfwSetMonitorCallback, arginfo_glfw_glfw_monitor_glfwmonitor_glfwsetmonitorcallback, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Monitor_GLFWMonitor, glfwGetVideoModes, arginfo_glfw_glfw_monitor_glfwmonitor_glfwgetvideomodes, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Monitor_GLFWMonitor, glfwGetVideoMode, arginfo_glfw_glfw_monitor_glfwmonitor_glfwgetvideomode, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Monitor_GLFWMonitor, glfwSetGamma, arginfo_glfw_glfw_monitor_glfwmonitor_glfwsetgamma, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Monitor_GLFWMonitor, glfwGetGammaRamp, arginfo_glfw_glfw_monitor_glfwmonitor_glfwgetgammaramp, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Monitor_GLFWMonitor, glfwSetGammaRamp, arginfo_glfw_glfw_monitor_glfwmonitor_glfwsetgammaramp, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};

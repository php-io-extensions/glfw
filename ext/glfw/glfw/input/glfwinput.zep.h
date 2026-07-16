
extern zend_class_entry *glfw_glfw_input_glfwinput_ce;

ZEPHIR_INIT_CLASS(Glfw_GLFW_Input_GLFWInput);

PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwGetInputMode);
PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwSetInputMode);
PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwRawMouseMotionSupported);
PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwGetKeyName);
PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwGetKeyScancode);
PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwGetKey);
PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwGetMouseButton);
PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwGetCursorPos);
PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwSetCursorPos);
PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwCreateCursor);
PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwCreateStandardCursor);
PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwDestroyCursor);
PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwSetCursor);
PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwSetKeyCallback);
PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwSetCharCallback);
PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwSetCharModsCallback);
PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwSetMouseButtonCallback);
PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwSetCursorPosCallback);
PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwSetCursorEnterCallback);
PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwSetScrollCallback);
PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwSetDropCallback);
PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwJoystickPresent);
PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwGetJoystickAxes);
PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwGetJoystickButtons);
PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwGetJoystickHats);
PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwGetJoystickName);
PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwGetJoystickGUID);
PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwSetJoystickUserPointer);
PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwGetJoystickUserPointer);
PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwJoystickIsGamepad);
PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwSetJoystickCallback);
PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwUpdateGamepadMappings);
PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwGetGamepadName);
PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwGetGamepadState);
PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwSetClipboardString);
PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwGetClipboardString);
PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwGetTime);
PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwSetTime);
PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwGetTimerValue);
PHP_METHOD(Glfw_GLFW_Input_GLFWInput, glfwGetTimerFrequency);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_input_glfwinput_glfwgetinputmode, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, mode, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_input_glfwinput_glfwsetinputmode, 0, 3, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, mode, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_input_glfwinput_glfwrawmousemotionsupported, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_input_glfwinput_glfwgetkeyname, 0, 2, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, key, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, scancode, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_input_glfwinput_glfwgetkeyscancode, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, key, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_input_glfwinput_glfwgetkey, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, key, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_input_glfwinput_glfwgetmousebutton, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, button, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_input_glfwinput_glfwgetcursorpos, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_input_glfwinput_glfwsetcursorpos, 0, 3, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, xpos, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, ypos, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_input_glfwinput_glfwcreatecursor, 0, 3, IS_LONG, 0)
	ZEND_ARG_ARRAY_INFO(0, image, 0)
	ZEND_ARG_TYPE_INFO(0, xhot, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, yhot, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_input_glfwinput_glfwcreatestandardcursor, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, shape, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_input_glfwinput_glfwdestroycursor, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, cursor, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_input_glfwinput_glfwsetcursor, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_INFO(0, cursor)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_input_glfwinput_glfwsetkeycallback, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_input_glfwinput_glfwsetcharcallback, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_input_glfwinput_glfwsetcharmodscallback, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_input_glfwinput_glfwsetmousebuttoncallback, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_input_glfwinput_glfwsetcursorposcallback, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_input_glfwinput_glfwsetcursorentercallback, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_input_glfwinput_glfwsetscrollcallback, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_input_glfwinput_glfwsetdropcallback, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_input_glfwinput_glfwjoystickpresent, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, jid, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_input_glfwinput_glfwgetjoystickaxes, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, jid, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_input_glfwinput_glfwgetjoystickbuttons, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, jid, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_input_glfwinput_glfwgetjoystickhats, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, jid, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_input_glfwinput_glfwgetjoystickname, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, jid, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_input_glfwinput_glfwgetjoystickguid, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, jid, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_input_glfwinput_glfwsetjoystickuserpointer, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, jid, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, pointer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_input_glfwinput_glfwgetjoystickuserpointer, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, jid, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_input_glfwinput_glfwjoystickisgamepad, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, jid, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_input_glfwinput_glfwsetjoystickcallback, 0, 0, IS_VOID, 0)

	ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_input_glfwinput_glfwupdategamepadmappings, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, mapping, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_input_glfwinput_glfwgetgamepadname, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, jid, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_input_glfwinput_glfwgetgamepadstate, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, jid, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_input_glfwinput_glfwsetclipboardstring, 0, 2, IS_VOID, 0)

	ZEND_ARG_INFO(0, window)
	ZEND_ARG_TYPE_INFO(0, value, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_input_glfwinput_glfwgetclipboardstring, 0, 0, IS_STRING, 0)
	ZEND_ARG_INFO(0, window)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_input_glfwinput_glfwgettime, 0, 0, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_input_glfwinput_glfwsettime, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, time, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_input_glfwinput_glfwgettimervalue, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfw_glfw_input_glfwinput_glfwgettimerfrequency, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(glfw_glfw_input_glfwinput_method_entry) {
	PHP_ME(Glfw_GLFW_Input_GLFWInput, glfwGetInputMode, arginfo_glfw_glfw_input_glfwinput_glfwgetinputmode, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Input_GLFWInput, glfwSetInputMode, arginfo_glfw_glfw_input_glfwinput_glfwsetinputmode, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Input_GLFWInput, glfwRawMouseMotionSupported, arginfo_glfw_glfw_input_glfwinput_glfwrawmousemotionsupported, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Input_GLFWInput, glfwGetKeyName, arginfo_glfw_glfw_input_glfwinput_glfwgetkeyname, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Input_GLFWInput, glfwGetKeyScancode, arginfo_glfw_glfw_input_glfwinput_glfwgetkeyscancode, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Input_GLFWInput, glfwGetKey, arginfo_glfw_glfw_input_glfwinput_glfwgetkey, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Input_GLFWInput, glfwGetMouseButton, arginfo_glfw_glfw_input_glfwinput_glfwgetmousebutton, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Input_GLFWInput, glfwGetCursorPos, arginfo_glfw_glfw_input_glfwinput_glfwgetcursorpos, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Input_GLFWInput, glfwSetCursorPos, arginfo_glfw_glfw_input_glfwinput_glfwsetcursorpos, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Input_GLFWInput, glfwCreateCursor, arginfo_glfw_glfw_input_glfwinput_glfwcreatecursor, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Input_GLFWInput, glfwCreateStandardCursor, arginfo_glfw_glfw_input_glfwinput_glfwcreatestandardcursor, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Input_GLFWInput, glfwDestroyCursor, arginfo_glfw_glfw_input_glfwinput_glfwdestroycursor, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Input_GLFWInput, glfwSetCursor, arginfo_glfw_glfw_input_glfwinput_glfwsetcursor, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Input_GLFWInput, glfwSetKeyCallback, arginfo_glfw_glfw_input_glfwinput_glfwsetkeycallback, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Input_GLFWInput, glfwSetCharCallback, arginfo_glfw_glfw_input_glfwinput_glfwsetcharcallback, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Input_GLFWInput, glfwSetCharModsCallback, arginfo_glfw_glfw_input_glfwinput_glfwsetcharmodscallback, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Input_GLFWInput, glfwSetMouseButtonCallback, arginfo_glfw_glfw_input_glfwinput_glfwsetmousebuttoncallback, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Input_GLFWInput, glfwSetCursorPosCallback, arginfo_glfw_glfw_input_glfwinput_glfwsetcursorposcallback, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Input_GLFWInput, glfwSetCursorEnterCallback, arginfo_glfw_glfw_input_glfwinput_glfwsetcursorentercallback, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Input_GLFWInput, glfwSetScrollCallback, arginfo_glfw_glfw_input_glfwinput_glfwsetscrollcallback, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Input_GLFWInput, glfwSetDropCallback, arginfo_glfw_glfw_input_glfwinput_glfwsetdropcallback, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Input_GLFWInput, glfwJoystickPresent, arginfo_glfw_glfw_input_glfwinput_glfwjoystickpresent, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Input_GLFWInput, glfwGetJoystickAxes, arginfo_glfw_glfw_input_glfwinput_glfwgetjoystickaxes, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Input_GLFWInput, glfwGetJoystickButtons, arginfo_glfw_glfw_input_glfwinput_glfwgetjoystickbuttons, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Input_GLFWInput, glfwGetJoystickHats, arginfo_glfw_glfw_input_glfwinput_glfwgetjoystickhats, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Input_GLFWInput, glfwGetJoystickName, arginfo_glfw_glfw_input_glfwinput_glfwgetjoystickname, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Input_GLFWInput, glfwGetJoystickGUID, arginfo_glfw_glfw_input_glfwinput_glfwgetjoystickguid, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Input_GLFWInput, glfwSetJoystickUserPointer, arginfo_glfw_glfw_input_glfwinput_glfwsetjoystickuserpointer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Input_GLFWInput, glfwGetJoystickUserPointer, arginfo_glfw_glfw_input_glfwinput_glfwgetjoystickuserpointer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Input_GLFWInput, glfwJoystickIsGamepad, arginfo_glfw_glfw_input_glfwinput_glfwjoystickisgamepad, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Input_GLFWInput, glfwSetJoystickCallback, arginfo_glfw_glfw_input_glfwinput_glfwsetjoystickcallback, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Input_GLFWInput, glfwUpdateGamepadMappings, arginfo_glfw_glfw_input_glfwinput_glfwupdategamepadmappings, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Input_GLFWInput, glfwGetGamepadName, arginfo_glfw_glfw_input_glfwinput_glfwgetgamepadname, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Input_GLFWInput, glfwGetGamepadState, arginfo_glfw_glfw_input_glfwinput_glfwgetgamepadstate, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Input_GLFWInput, glfwSetClipboardString, arginfo_glfw_glfw_input_glfwinput_glfwsetclipboardstring, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Input_GLFWInput, glfwGetClipboardString, arginfo_glfw_glfw_input_glfwinput_glfwgetclipboardstring, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Input_GLFWInput, glfwGetTime, arginfo_glfw_glfw_input_glfwinput_glfwgettime, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Input_GLFWInput, glfwSetTime, arginfo_glfw_glfw_input_glfwinput_glfwsettime, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Input_GLFWInput, glfwGetTimerValue, arginfo_glfw_glfw_input_glfwinput_glfwgettimervalue, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glfw_GLFW_Input_GLFWInput, glfwGetTimerFrequency, arginfo_glfw_glfw_input_glfwinput_glfwgettimerfrequency, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};

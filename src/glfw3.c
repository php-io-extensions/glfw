#include "runtime.h"
#include "../stubs/glfw3_arginfo.h"

zend_class_entry *glfw_ce_GLFWwindow;
zend_class_entry *glfw_ce_GLFWmonitor;
zend_class_entry *glfw_ce_GLFWvidmode;
zend_class_entry *glfw_ce_GLFWgammaramp;
zend_class_entry *glfw_ce_GLFWimage;

void glfw_register_glfw3(int module_number)
{
	register_glfw3_symbols(module_number);
	zend_register_functions(NULL, ext_functions, NULL, MODULE_PERSISTENT);

	glfw_ce_GLFWwindow = register_class_GLFWwindow();
	glfw_handle_setup(glfw_ce_GLFWwindow);
	glfw_ce_GLFWmonitor = register_class_GLFWmonitor();
	glfw_handle_setup(glfw_ce_GLFWmonitor);
	glfw_ce_GLFWvidmode = register_class_GLFWvidmode();
	glfw_ce_GLFWgammaramp = register_class_GLFWgammaramp();
	glfw_ce_GLFWimage = register_class_GLFWimage();
}

GLFW_POINTER_METHODS(GLFWwindow)
GLFW_POINTER_METHODS(GLFWmonitor)

/* Writes ints and floats into by-reference parameters. False when an assignment threw. */
static bool glfw_assign_longs(zval **refs, const int *values, int count)
{
	for (int i = 0; i < count; i++) {
		ZEND_TRY_ASSIGN_REF_LONG(refs[i], values[i]);
		if (EG(exception)) {
			return false;
		}
	}
	return true;
}

static bool glfw_assign_doubles(zval **refs, const float *values, int count)
{
	for (int i = 0; i < count; i++) {
		ZEND_TRY_ASSIGN_REF_DOUBLE(refs[i], (double) values[i]);
		if (EG(exception)) {
			return false;
		}
	}
	return true;
}

/* An int parameter that GLFW takes as int: converted as C converts it. */
#define GLFW_INT_ARG(var, value, n) int var = (int) (value);

/* ---- GLFWgammaramp, GLFWimage --------------------------------------------- */

ZEND_METHOD(GLFWgammaramp, __construct)
{
	HashTable *red = NULL, *green = NULL, *blue = NULL;

	ZEND_PARSE_PARAMETERS_START(0, 3)
		Z_PARAM_OPTIONAL
		Z_PARAM_ARRAY_HT(red)
		Z_PARAM_ARRAY_HT(green)
		Z_PARAM_ARRAY_HT(blue)
	ZEND_PARSE_PARAMETERS_END();

	zend_object *obj = Z_OBJ_P(ZEND_THIS);
	zval value;
	HashTable *channels[3] = { red, green, blue };
	const char *names[3] = { "red", "green", "blue" };

	for (int i = 0; i < 3; i++) {
		if (channels[i] == NULL) {
			continue;
		}
		ZVAL_ARR(&value, zend_array_dup(channels[i]));
		zend_update_property(glfw_ce_GLFWgammaramp, obj, names[i], strlen(names[i]), &value);
		zval_ptr_dtor(&value);
	}
}

ZEND_METHOD(GLFWimage, __construct)
{
	zend_long width = 0, height = 0;
	zend_string *pixels = NULL;

	ZEND_PARSE_PARAMETERS_START(0, 3)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(width)
		Z_PARAM_LONG(height)
		Z_PARAM_STR(pixels)
	ZEND_PARSE_PARAMETERS_END();

	zend_object *obj = Z_OBJ_P(ZEND_THIS);
	zend_update_property_long(glfw_ce_GLFWimage, obj, ZEND_STRL("width"), width);
	zend_update_property_long(glfw_ce_GLFWimage, obj, ZEND_STRL("height"), height);
	if (pixels != NULL) {
		zend_update_property_str(glfw_ce_GLFWimage, obj, ZEND_STRL("pixels"), pixels);
	}
}

static zval *glfw_prop(zend_object *obj, const char *name)
{
	zval rv;

	return zend_read_property(obj->ce, obj, name, strlen(name), true, &rv);
}

/*
 * Stores callback (null clears) in slot, and returns the callable it held, as GLFW's set-callback
 * functions return the previous callback. The returned callable moves out of the slot.
 */
static void glfw_swap_callback(zval *slot, zval *callback, zval *rv)
{
	if (Z_TYPE_P(slot) == IS_UNDEF) {
		ZVAL_NULL(rv);
	} else {
		ZVAL_COPY_VALUE(rv, slot);
	}
	if (Z_TYPE_P(callback) == IS_NULL) {
		ZVAL_UNDEF(slot);
	} else {
		ZVAL_COPY(slot, callback);
	}
}

/* ---- Initialization, version and error ------------------------------------ */

static void glfw_error_trampoline(int code, const char *description)
{
	zval argv[2];

	ZVAL_LONG(&argv[0], code);
	ZVAL_STRING(&argv[1], description != NULL ? description : "");
	glfw_call(&GLFW_G(error_callback), 2, argv);
	zval_ptr_dtor(&argv[1]);
}

ZEND_FUNCTION(glfwInit)
{
	ZEND_PARSE_PARAMETERS_NONE();
	RETURN_LONG(glfwInit());
}

/* glfwTerminate destroys every window and forgets every monitor: their PHP objects say so after. */
ZEND_FUNCTION(glfwTerminate)
{
	ZEND_PARSE_PARAMETERS_NONE();

	glfw_callbacks_drop_all(false);
	glfwTerminate();
	glfw_release_all(glfw_ce_GLFWwindow);
	glfw_release_all(glfw_ce_GLFWmonitor);
}

ZEND_FUNCTION(glfwInitHint)
{
	zend_long hint, value;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(hint)
		Z_PARAM_LONG(value)
	ZEND_PARSE_PARAMETERS_END();
	GLFW_INT_ARG(native_hint, hint, 1)
	GLFW_INT_ARG(native_value, value, 2)

	glfwInitHint(native_hint, native_value);
}

ZEND_FUNCTION(glfwGetVersion)
{
	zval *refs[3];
	int values[3];

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_ZVAL(refs[0])
		Z_PARAM_ZVAL(refs[1])
		Z_PARAM_ZVAL(refs[2])
	ZEND_PARSE_PARAMETERS_END();

	glfwGetVersion(&values[0], &values[1], &values[2]);
	glfw_assign_longs(refs, values, 3);
}

ZEND_FUNCTION(glfwGetVersionString)
{
	ZEND_PARSE_PARAMETERS_NONE();
	RETURN_STRING(glfwGetVersionString());
}

ZEND_FUNCTION(glfwGetError)
{
	zval *description_ref = NULL;
	const char *description = NULL;

	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL(description_ref)
	ZEND_PARSE_PARAMETERS_END();

	int code = glfwGetError(&description);
	if (description_ref != NULL) {
		if (description != NULL) {
			ZEND_TRY_ASSIGN_REF_STRING(description_ref, description);
		} else {
			ZEND_TRY_ASSIGN_REF_NULL(description_ref);
		}
	}
	RETURN_LONG(code);
}

ZEND_FUNCTION(glfwSetErrorCallback)
{
	zval *callback;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(callback)
	ZEND_PARSE_PARAMETERS_END();
	if (Z_TYPE_P(callback) != IS_NULL && !zend_is_callable(callback, 0, NULL)) {
		zend_argument_type_error(1, "must be a valid callback or null");
		RETURN_THROWS();
	}

	glfw_swap_callback(&GLFW_G(error_callback), callback, return_value);
	glfwSetErrorCallback(Z_TYPE_P(callback) == IS_NULL ? NULL : glfw_error_trampoline);
}

ZEND_FUNCTION(glfwGetPlatform)
{
	ZEND_PARSE_PARAMETERS_NONE();
	RETURN_LONG(glfwGetPlatform());
}

ZEND_FUNCTION(glfwPlatformSupported)
{
	zend_long platform;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(platform)
	ZEND_PARSE_PARAMETERS_END();
	GLFW_INT_ARG(native, platform, 1)

	RETURN_LONG(glfwPlatformSupported(native));
}

/* ---- Monitors ------------------------------------------------------------- */

#define GLFW_PARSE_MONITOR zend_object *monitor_obj; ZEND_PARSE_PARAMETERS_START(1, 1) Z_PARAM_OBJ_OF_CLASS(monitor_obj, glfw_ce_GLFWmonitor) ZEND_PARSE_PARAMETERS_END(); GLFW_MONITOR_ARG(monitor, monitor_obj, 1)

ZEND_FUNCTION(glfwGetMonitors)
{
	int count = 0;

	ZEND_PARSE_PARAMETERS_NONE();

	GLFWmonitor **monitors = glfwGetMonitors(&count);
	array_init_size(return_value, (uint32_t) count);
	for (int i = 0; i < count; i++) {
		zval boxed;
		glfw_box(&boxed, monitors[i], glfw_ce_GLFWmonitor);
		add_next_index_zval(return_value, &boxed);
	}
}

ZEND_FUNCTION(glfwGetPrimaryMonitor)
{
	ZEND_PARSE_PARAMETERS_NONE();
	glfw_box(return_value, glfwGetPrimaryMonitor(), glfw_ce_GLFWmonitor);
}

ZEND_FUNCTION(glfwGetMonitorPos)
{
	zend_object *monitor_obj;
	zval *refs[2];
	int values[2];

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJ_OF_CLASS(monitor_obj, glfw_ce_GLFWmonitor)
		Z_PARAM_ZVAL(refs[0])
		Z_PARAM_ZVAL(refs[1])
	ZEND_PARSE_PARAMETERS_END();
	GLFW_MONITOR_ARG(monitor, monitor_obj, 1)

	glfwGetMonitorPos(monitor, &values[0], &values[1]);
	glfw_assign_longs(refs, values, 2);
}

ZEND_FUNCTION(glfwGetMonitorWorkarea)
{
	zend_object *monitor_obj;
	zval *refs[4];
	int values[4];

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_OBJ_OF_CLASS(monitor_obj, glfw_ce_GLFWmonitor)
		Z_PARAM_ZVAL(refs[0])
		Z_PARAM_ZVAL(refs[1])
		Z_PARAM_ZVAL(refs[2])
		Z_PARAM_ZVAL(refs[3])
	ZEND_PARSE_PARAMETERS_END();
	GLFW_MONITOR_ARG(monitor, monitor_obj, 1)

	glfwGetMonitorWorkarea(monitor, &values[0], &values[1], &values[2], &values[3]);
	glfw_assign_longs(refs, values, 4);
}

ZEND_FUNCTION(glfwGetMonitorPhysicalSize)
{
	zend_object *monitor_obj;
	zval *refs[2];
	int values[2];

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJ_OF_CLASS(monitor_obj, glfw_ce_GLFWmonitor)
		Z_PARAM_ZVAL(refs[0])
		Z_PARAM_ZVAL(refs[1])
	ZEND_PARSE_PARAMETERS_END();
	GLFW_MONITOR_ARG(monitor, monitor_obj, 1)

	glfwGetMonitorPhysicalSize(monitor, &values[0], &values[1]);
	glfw_assign_longs(refs, values, 2);
}

ZEND_FUNCTION(glfwGetMonitorContentScale)
{
	zend_object *monitor_obj;
	zval *refs[2];
	float values[2];

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJ_OF_CLASS(monitor_obj, glfw_ce_GLFWmonitor)
		Z_PARAM_ZVAL(refs[0])
		Z_PARAM_ZVAL(refs[1])
	ZEND_PARSE_PARAMETERS_END();
	GLFW_MONITOR_ARG(monitor, monitor_obj, 1)

	glfwGetMonitorContentScale(monitor, &values[0], &values[1]);
	glfw_assign_doubles(refs, values, 2);
}

ZEND_FUNCTION(glfwGetMonitorName)
{
	GLFW_PARSE_MONITOR

	const char *name = glfwGetMonitorName(monitor);
	if (name == NULL) {
		RETURN_NULL();
	}
	RETURN_STRING(name);
}

/* Called for a monitor GLFW connected or disconnected; a disconnected monitor's PHP object goes stale after the call. */
static void glfw_monitor_trampoline(GLFWmonitor *monitor, int event)
{
	zval argv[2];

	glfw_box(&argv[0], monitor, glfw_ce_GLFWmonitor);
	ZVAL_LONG(&argv[1], event);
	glfw_call(&GLFW_G(monitor_callback), 2, argv);
	zval_ptr_dtor(&argv[0]);
	if (event == GLFW_DISCONNECTED) {
		glfw_release_ptr(monitor);
	}
}

ZEND_FUNCTION(glfwSetMonitorCallback)
{
	zval *callback;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(callback)
	ZEND_PARSE_PARAMETERS_END();
	if (Z_TYPE_P(callback) != IS_NULL && !zend_is_callable(callback, 0, NULL)) {
		zend_argument_type_error(1, "must be a valid callback or null");
		RETURN_THROWS();
	}

	glfw_swap_callback(&GLFW_G(monitor_callback), callback, return_value);
	glfwSetMonitorCallback(Z_TYPE_P(callback) == IS_NULL ? NULL : glfw_monitor_trampoline);
}

ZEND_FUNCTION(glfwGetVideoModes)
{
	int count = 0;
	GLFW_PARSE_MONITOR

	const GLFWvidmode *modes = glfwGetVideoModes(monitor, &count);
	array_init_size(return_value, (uint32_t) (count > 0 ? count : 0));
	for (int i = 0; modes != NULL && i < count; i++) {
		zval mode;
		glfw_return_vidmode(&mode, &modes[i]);
		add_next_index_zval(return_value, &mode);
	}
}

ZEND_FUNCTION(glfwGetVideoMode)
{
	GLFW_PARSE_MONITOR
	glfw_return_vidmode(return_value, glfwGetVideoMode(monitor));
}

ZEND_FUNCTION(glfwSetGamma)
{
	zend_object *monitor_obj;
	double gamma;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJ_OF_CLASS(monitor_obj, glfw_ce_GLFWmonitor)
		Z_PARAM_DOUBLE(gamma)
	ZEND_PARSE_PARAMETERS_END();
	GLFW_MONITOR_ARG(monitor, monitor_obj, 1)

	glfwSetGamma(monitor, (float) gamma);
}

ZEND_FUNCTION(glfwGetGammaRamp)
{
	GLFW_PARSE_MONITOR

	const GLFWgammaramp *ramp = glfwGetGammaRamp(monitor);
	if (ramp == NULL) {
		RETURN_NULL();
	}

	zval channels[3];
	const unsigned short *values[3] = { ramp->red, ramp->green, ramp->blue };
	for (int c = 0; c < 3; c++) {
		array_init_size(&channels[c], ramp->size);
		for (unsigned int i = 0; i < ramp->size; i++) {
			add_next_index_long(&channels[c], values[c][i]);
		}
	}

	object_init_ex(return_value, glfw_ce_GLFWgammaramp);
	zend_update_property(glfw_ce_GLFWgammaramp, Z_OBJ_P(return_value), ZEND_STRL("red"), &channels[0]);
	zend_update_property(glfw_ce_GLFWgammaramp, Z_OBJ_P(return_value), ZEND_STRL("green"), &channels[1]);
	zend_update_property(glfw_ce_GLFWgammaramp, Z_OBJ_P(return_value), ZEND_STRL("blue"), &channels[2]);
	for (int c = 0; c < 3; c++) {
		zval_ptr_dtor(&channels[c]);
	}
}

/*
 * The C GLFWgammaramp of a PHP one: its three lists become red, green and blue arrays of one
 * size, in one emalloc block at ramp->red. Lists of different lengths have no single size.
 */
static bool glfw_gamma_from(zend_object *obj, uint32_t arg_num, GLFWgammaramp *ramp)
{
	const char *names[3] = { "red", "green", "blue" };
	HashTable *channels[3];

	for (int c = 0; c < 3; c++) {
		zval *channel = glfw_prop(obj, names[c]);
		if (Z_TYPE_P(channel) != IS_ARRAY) {
			zend_argument_type_error(arg_num, "must have a list of ints as $%s", names[c]);
			return false;
		}
		channels[c] = Z_ARRVAL_P(channel);
		if (zend_hash_num_elements(channels[c]) != zend_hash_num_elements(channels[0])) {
			zend_argument_value_error(arg_num, "must have red, green and blue lists of one length");
			return false;
		}
	}

	uint32_t size = zend_hash_num_elements(channels[0]);
	unsigned short *values = safe_emalloc(3, (size_t) size * sizeof(unsigned short), 0);
	for (int c = 0; c < 3; c++) {
		uint32_t i = 0;
		zval *value;
		ZEND_HASH_FOREACH_VAL(channels[c], value) {
			if (Z_TYPE_P(value) != IS_LONG) {
				efree(values);
				zend_argument_type_error(arg_num, "must hold ints in $%s", names[c]);
				return false;
			}
			values[c * size + i++] = (unsigned short) Z_LVAL_P(value);
		} ZEND_HASH_FOREACH_END();
	}

	ramp->red = values;
	ramp->green = values + size;
	ramp->blue = values + 2 * size;
	ramp->size = size;
	return true;
}

ZEND_FUNCTION(glfwSetGammaRamp)
{
	zend_object *monitor_obj, *ramp_obj;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJ_OF_CLASS(monitor_obj, glfw_ce_GLFWmonitor)
		Z_PARAM_OBJ_OF_CLASS(ramp_obj, glfw_ce_GLFWgammaramp)
	ZEND_PARSE_PARAMETERS_END();
	GLFW_MONITOR_ARG(monitor, monitor_obj, 1)

	GLFWgammaramp ramp;
	if (!glfw_gamma_from(ramp_obj, 2, &ramp)) {
		RETURN_THROWS();
	}
	glfwSetGammaRamp(monitor, &ramp);
	efree(ramp.red);
}

/* ---- Windows -------------------------------------------------------------- */

#define GLFW_PARSE_WINDOW zend_object *window_obj; ZEND_PARSE_PARAMETERS_START(1, 1) Z_PARAM_OBJ_OF_CLASS(window_obj, glfw_ce_GLFWwindow) ZEND_PARSE_PARAMETERS_END(); GLFW_WINDOW_ARG(window, window_obj, 1)

ZEND_FUNCTION(glfwDefaultWindowHints)
{
	ZEND_PARSE_PARAMETERS_NONE();
	glfwDefaultWindowHints();
}

ZEND_FUNCTION(glfwWindowHint)
{
	zend_long hint, value;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(hint)
		Z_PARAM_LONG(value)
	ZEND_PARSE_PARAMETERS_END();
	GLFW_INT_ARG(native_hint, hint, 1)
	GLFW_INT_ARG(native_value, value, 2)
	glfwWindowHint(native_hint, native_value);
}

ZEND_FUNCTION(glfwWindowHintString)
{
	zend_long hint;
	zend_string *value;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(hint)
		Z_PARAM_STR(value)
	ZEND_PARSE_PARAMETERS_END();
	GLFW_INT_ARG(native_hint, hint, 1)

	glfwWindowHintString(native_hint, ZSTR_VAL(value));
}

ZEND_FUNCTION(glfwCreateWindow)
{
	zend_long width, height;
	zend_string *title;
	zend_object *monitor_obj = NULL, *share_obj = NULL;

	ZEND_PARSE_PARAMETERS_START(3, 5)
		Z_PARAM_LONG(width)
		Z_PARAM_LONG(height)
		Z_PARAM_STR(title)
		Z_PARAM_OPTIONAL
		Z_PARAM_OBJ_OF_CLASS_OR_NULL(monitor_obj, glfw_ce_GLFWmonitor)
		Z_PARAM_OBJ_OF_CLASS_OR_NULL(share_obj, glfw_ce_GLFWwindow)
	ZEND_PARSE_PARAMETERS_END();
	GLFW_INT_ARG(native_width, width, 1)
	GLFW_INT_ARG(native_height, height, 2)

	glfw_box(return_value, glfwCreateWindow(native_width, native_height, ZSTR_VAL(title),
		glfw_optional_ptr(monitor_obj), glfw_optional_ptr(share_obj)), glfw_ce_GLFWwindow);
}

/* GLFW destroys nothing for NULL: a destroyed window passes through. */
ZEND_FUNCTION(glfwDestroyWindow)
{
	zend_object *window_obj;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(window_obj, glfw_ce_GLFWwindow)
	ZEND_PARSE_PARAMETERS_END();
	GLFWwindow *window = glfw_optional_ptr(window_obj);

	glfw_callbacks_drop(window);
	glfwDestroyWindow(window);
	glfw_release_ptr(window);
}

ZEND_FUNCTION(glfwWindowShouldClose)
{
	GLFW_PARSE_WINDOW
	RETURN_LONG(glfwWindowShouldClose(window));
}

ZEND_FUNCTION(glfwSetWindowShouldClose)
{
	zend_object *window_obj;
	zend_long value;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJ_OF_CLASS(window_obj, glfw_ce_GLFWwindow)
		Z_PARAM_LONG(value)
	ZEND_PARSE_PARAMETERS_END();
	GLFW_WINDOW_ARG(window, window_obj, 1)
	GLFW_INT_ARG(native_value, value, 2)

	glfwSetWindowShouldClose(window, native_value);
}

ZEND_FUNCTION(glfwGetWindowTitle)
{
	GLFW_PARSE_WINDOW

	const char *title = glfwGetWindowTitle(window);
	if (title == NULL) {
		RETURN_NULL();
	}
	RETURN_STRING(title);
}

ZEND_FUNCTION(glfwSetWindowTitle)
{
	zend_object *window_obj;
	zend_string *title;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJ_OF_CLASS(window_obj, glfw_ce_GLFWwindow)
		Z_PARAM_STR(title)
	ZEND_PARSE_PARAMETERS_END();
	GLFW_WINDOW_ARG(window, window_obj, 1)

	glfwSetWindowTitle(window, ZSTR_VAL(title));
}

/* The C GLFWimage array of a list of GLFWimage, emalloc'd (NULL for an empty list); the pixels stay the strings'. */
static GLFWimage *glfw_images_from(HashTable *list, uint32_t arg_num)
{
	uint32_t length = zend_hash_num_elements(list);
	GLFWimage *images = length > 0 ? safe_emalloc(length, sizeof(GLFWimage), 0) : NULL;
	uint32_t i = 0;
	zval *entry;

	ZEND_HASH_FOREACH_VAL(list, entry) {
		if (Z_TYPE_P(entry) != IS_OBJECT || Z_OBJCE_P(entry) != glfw_ce_GLFWimage) {
			efree(images);
			zend_argument_type_error(arg_num, "must be a list of GLFWimage");
			return NULL;
		}
		zval *w = glfw_prop(Z_OBJ_P(entry), "width");
		zval *h = glfw_prop(Z_OBJ_P(entry), "height");
		zval *pixels = glfw_prop(Z_OBJ_P(entry), "pixels");
		/* GLFW reads 4 x width x height bytes of pixels. */
		if (!GLFW_PROBE_OFF("glfw-icon-pixels-length") && (zend_long) Z_STRLEN_P(pixels) < Z_LVAL_P(w) * Z_LVAL_P(h) * 4) {
			efree(images);
			zend_argument_value_error(arg_num, "must hold images whose pixels are at least 4 x width x height bytes"); /* binding:glfw-icon-pixels-length */
			return NULL;
		}
		images[i].width = (int) Z_LVAL_P(w);
		images[i].height = (int) Z_LVAL_P(h);
		images[i].pixels = (unsigned char *) Z_STRVAL_P(pixels);
		i++;
	} ZEND_HASH_FOREACH_END();

	return images;
}

ZEND_FUNCTION(glfwSetWindowIcon)
{
	zend_object *window_obj;
	zend_long count;
	HashTable *images_ht;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJ_OF_CLASS(window_obj, glfw_ce_GLFWwindow)
		Z_PARAM_LONG(count)
		Z_PARAM_ARRAY_HT(images_ht)
	ZEND_PARSE_PARAMETERS_END();
	GLFW_WINDOW_ARG(window, window_obj, 1)
	if (!glfw_list_count(count, zend_hash_num_elements(images_ht), 2, 3)) {
		RETURN_THROWS();
	}

	GLFWimage *images = glfw_images_from(images_ht, 3);
	if (EG(exception)) {
		RETURN_THROWS();
	}
	glfwSetWindowIcon(window, (int) count, images);
	if (images != NULL) {
		efree(images);
	}
}

#define GLFW_GET_TWO_INTS(fn, glfw_fn) \
ZEND_FUNCTION(fn) \
{ \
	zend_object *window_obj; \
	zval *refs[2]; \
	int values[2]; \
	ZEND_PARSE_PARAMETERS_START(3, 3) \
		Z_PARAM_OBJ_OF_CLASS(window_obj, glfw_ce_GLFWwindow) \
		Z_PARAM_ZVAL(refs[0]) \
		Z_PARAM_ZVAL(refs[1]) \
	ZEND_PARSE_PARAMETERS_END(); \
	GLFW_WINDOW_ARG(window, window_obj, 1) \
	glfw_fn(window, &values[0], &values[1]); \
	glfw_assign_longs(refs, values, 2); \
}

#define GLFW_SET_TWO_INTS(fn, glfw_fn) \
ZEND_FUNCTION(fn) \
{ \
	zend_object *window_obj; \
	zend_long a, b; \
	ZEND_PARSE_PARAMETERS_START(3, 3) \
		Z_PARAM_OBJ_OF_CLASS(window_obj, glfw_ce_GLFWwindow) \
		Z_PARAM_LONG(a) \
		Z_PARAM_LONG(b) \
	ZEND_PARSE_PARAMETERS_END(); \
	GLFW_WINDOW_ARG(window, window_obj, 1) \
	GLFW_INT_ARG(native_a, a, 2) \
	GLFW_INT_ARG(native_b, b, 3) \
	glfw_fn(window, native_a, native_b); \
}

GLFW_GET_TWO_INTS(glfwGetWindowPos, glfwGetWindowPos)
GLFW_SET_TWO_INTS(glfwSetWindowPos, glfwSetWindowPos)
GLFW_GET_TWO_INTS(glfwGetWindowSize, glfwGetWindowSize)
GLFW_SET_TWO_INTS(glfwSetWindowSize, glfwSetWindowSize)
GLFW_SET_TWO_INTS(glfwSetWindowAspectRatio, glfwSetWindowAspectRatio)
GLFW_GET_TWO_INTS(glfwGetFramebufferSize, glfwGetFramebufferSize)

ZEND_FUNCTION(glfwSetWindowSizeLimits)
{
	zend_object *window_obj;
	zend_long limits[4];

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_OBJ_OF_CLASS(window_obj, glfw_ce_GLFWwindow)
		Z_PARAM_LONG(limits[0])
		Z_PARAM_LONG(limits[1])
		Z_PARAM_LONG(limits[2])
		Z_PARAM_LONG(limits[3])
	ZEND_PARSE_PARAMETERS_END();
	GLFW_WINDOW_ARG(window, window_obj, 1)
	GLFW_INT_ARG(minwidth, limits[0], 2)
	GLFW_INT_ARG(minheight, limits[1], 3)
	GLFW_INT_ARG(maxwidth, limits[2], 4)
	GLFW_INT_ARG(maxheight, limits[3], 5)

	glfwSetWindowSizeLimits(window, minwidth, minheight, maxwidth, maxheight);
}

ZEND_FUNCTION(glfwGetWindowFrameSize)
{
	zend_object *window_obj;
	zval *refs[4];
	int values[4];

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_OBJ_OF_CLASS(window_obj, glfw_ce_GLFWwindow)
		Z_PARAM_ZVAL(refs[0])
		Z_PARAM_ZVAL(refs[1])
		Z_PARAM_ZVAL(refs[2])
		Z_PARAM_ZVAL(refs[3])
	ZEND_PARSE_PARAMETERS_END();
	GLFW_WINDOW_ARG(window, window_obj, 1)

	glfwGetWindowFrameSize(window, &values[0], &values[1], &values[2], &values[3]);
	glfw_assign_longs(refs, values, 4);
}

ZEND_FUNCTION(glfwGetWindowContentScale)
{
	zend_object *window_obj;
	zval *refs[2];
	float values[2];

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJ_OF_CLASS(window_obj, glfw_ce_GLFWwindow)
		Z_PARAM_ZVAL(refs[0])
		Z_PARAM_ZVAL(refs[1])
	ZEND_PARSE_PARAMETERS_END();
	GLFW_WINDOW_ARG(window, window_obj, 1)

	glfwGetWindowContentScale(window, &values[0], &values[1]);
	glfw_assign_doubles(refs, values, 2);
}

ZEND_FUNCTION(glfwGetWindowOpacity)
{
	GLFW_PARSE_WINDOW
	RETURN_DOUBLE((double) glfwGetWindowOpacity(window));
}

ZEND_FUNCTION(glfwSetWindowOpacity)
{
	zend_object *window_obj;
	double opacity;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJ_OF_CLASS(window_obj, glfw_ce_GLFWwindow)
		Z_PARAM_DOUBLE(opacity)
	ZEND_PARSE_PARAMETERS_END();
	GLFW_WINDOW_ARG(window, window_obj, 1)

	glfwSetWindowOpacity(window, (float) opacity);
}

#define GLFW_WINDOW_VOID(fn) \
ZEND_FUNCTION(fn) \
{ \
	GLFW_PARSE_WINDOW \
	fn(window); \
}

GLFW_WINDOW_VOID(glfwIconifyWindow)
GLFW_WINDOW_VOID(glfwRestoreWindow)
GLFW_WINDOW_VOID(glfwMaximizeWindow)
GLFW_WINDOW_VOID(glfwShowWindow)
GLFW_WINDOW_VOID(glfwHideWindow)
GLFW_WINDOW_VOID(glfwFocusWindow)
GLFW_WINDOW_VOID(glfwRequestWindowAttention)
GLFW_WINDOW_VOID(glfwSwapBuffers)

ZEND_FUNCTION(glfwGetWindowMonitor)
{
	GLFW_PARSE_WINDOW
	glfw_box(return_value, glfwGetWindowMonitor(window), glfw_ce_GLFWmonitor);
}

ZEND_FUNCTION(glfwSetWindowMonitor)
{
	zend_object *window_obj, *monitor_obj = NULL;
	zend_long args[5];

	ZEND_PARSE_PARAMETERS_START(7, 7)
		Z_PARAM_OBJ_OF_CLASS(window_obj, glfw_ce_GLFWwindow)
		Z_PARAM_OBJ_OF_CLASS_OR_NULL(monitor_obj, glfw_ce_GLFWmonitor)
		Z_PARAM_LONG(args[0])
		Z_PARAM_LONG(args[1])
		Z_PARAM_LONG(args[2])
		Z_PARAM_LONG(args[3])
		Z_PARAM_LONG(args[4])
	ZEND_PARSE_PARAMETERS_END();
	GLFW_WINDOW_ARG(window, window_obj, 1)
	GLFWmonitor *monitor = glfw_optional_ptr(monitor_obj);
	GLFW_INT_ARG(xpos, args[0], 3)
	GLFW_INT_ARG(ypos, args[1], 4)
	GLFW_INT_ARG(width, args[2], 5)
	GLFW_INT_ARG(height, args[3], 6)
	GLFW_INT_ARG(refresh, args[4], 7)

	glfwSetWindowMonitor(window, monitor, xpos, ypos, width, height, refresh);
}

ZEND_FUNCTION(glfwGetWindowAttrib)
{
	zend_object *window_obj;
	zend_long attrib;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJ_OF_CLASS(window_obj, glfw_ce_GLFWwindow)
		Z_PARAM_LONG(attrib)
	ZEND_PARSE_PARAMETERS_END();
	GLFW_WINDOW_ARG(window, window_obj, 1)
	GLFW_INT_ARG(native, attrib, 2)

	RETURN_LONG(glfwGetWindowAttrib(window, native));
}

ZEND_FUNCTION(glfwSetWindowAttrib)
{
	zend_object *window_obj;
	zend_long attrib, value;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJ_OF_CLASS(window_obj, glfw_ce_GLFWwindow)
		Z_PARAM_LONG(attrib)
		Z_PARAM_LONG(value)
	ZEND_PARSE_PARAMETERS_END();
	GLFW_WINDOW_ARG(window, window_obj, 1)
	GLFW_INT_ARG(native_attrib, attrib, 2)
	GLFW_INT_ARG(native_value, value, 3)

	glfwSetWindowAttrib(window, native_attrib, native_value);
}

/* ---- Window callbacks ----------------------------------------------------- */

/* The callable stored for window and slot, or NULL. */
static zval *glfw_slot(GLFWwindow *window, int slot)
{
	glfw_window_callbacks *callbacks = glfw_callbacks_for(window, false);

	return callbacks != NULL && Z_TYPE(callbacks->callbacks[slot]) != IS_UNDEF ? &callbacks->callbacks[slot] : NULL;
}

/* Calls slot's callable with (window, ...rest): rest are argc - 1 values already in argv[1..]. */
static void glfw_window_dispatch(GLFWwindow *window, int slot, uint32_t argc, zval *argv)
{
	zval *callable = glfw_slot(window, slot);

	if (callable != NULL) {
		glfw_box(&argv[0], window, glfw_ce_GLFWwindow);
		glfw_call(callable, argc, argv);
		zval_ptr_dtor(&argv[0]);
	}
}

static void glfw_pos_trampoline(GLFWwindow *w, int x, int y) { zval a[3]; ZVAL_LONG(&a[1], x); ZVAL_LONG(&a[2], y); glfw_window_dispatch(w, GLFW_CB_POS, 3, a); }
static void glfw_size_trampoline(GLFWwindow *w, int x, int y) { zval a[3]; ZVAL_LONG(&a[1], x); ZVAL_LONG(&a[2], y); glfw_window_dispatch(w, GLFW_CB_SIZE, 3, a); }
static void glfw_close_trampoline(GLFWwindow *w) { zval a[1]; glfw_window_dispatch(w, GLFW_CB_CLOSE, 1, a); }
static void glfw_refresh_trampoline(GLFWwindow *w) { zval a[1]; glfw_window_dispatch(w, GLFW_CB_REFRESH, 1, a); }
static void glfw_focus_trampoline(GLFWwindow *w, int on) { zval a[2]; ZVAL_LONG(&a[1], on); glfw_window_dispatch(w, GLFW_CB_FOCUS, 2, a); }
static void glfw_iconify_trampoline(GLFWwindow *w, int on) { zval a[2]; ZVAL_LONG(&a[1], on); glfw_window_dispatch(w, GLFW_CB_ICONIFY, 2, a); }
static void glfw_maximize_trampoline(GLFWwindow *w, int on) { zval a[2]; ZVAL_LONG(&a[1], on); glfw_window_dispatch(w, GLFW_CB_MAXIMIZE, 2, a); }
static void glfw_framebuffer_trampoline(GLFWwindow *w, int x, int y) { zval a[3]; ZVAL_LONG(&a[1], x); ZVAL_LONG(&a[2], y); glfw_window_dispatch(w, GLFW_CB_FRAMEBUFFER_SIZE, 3, a); }
static void glfw_scale_trampoline(GLFWwindow *w, float x, float y) { zval a[3]; ZVAL_DOUBLE(&a[1], x); ZVAL_DOUBLE(&a[2], y); glfw_window_dispatch(w, GLFW_CB_CONTENT_SCALE, 3, a); }

static void glfw_key_trampoline(GLFWwindow *w, int key, int scancode, int action, int mods) { zval a[5]; ZVAL_LONG(&a[1], key); ZVAL_LONG(&a[2], scancode); ZVAL_LONG(&a[3], action); ZVAL_LONG(&a[4], mods); glfw_window_dispatch(w, GLFW_CB_KEY, 5, a); }
static void glfw_char_trampoline(GLFWwindow *w, unsigned int codepoint) { zval a[2]; ZVAL_LONG(&a[1], codepoint); glfw_window_dispatch(w, GLFW_CB_CHAR, 2, a); }
static void glfw_mouse_button_trampoline(GLFWwindow *w, int button, int action, int mods) { zval a[4]; ZVAL_LONG(&a[1], button); ZVAL_LONG(&a[2], action); ZVAL_LONG(&a[3], mods); glfw_window_dispatch(w, GLFW_CB_MOUSE_BUTTON, 4, a); }
static void glfw_cursor_pos_trampoline(GLFWwindow *w, double x, double y) { zval a[3]; ZVAL_DOUBLE(&a[1], x); ZVAL_DOUBLE(&a[2], y); glfw_window_dispatch(w, GLFW_CB_CURSOR_POS, 3, a); }
static void glfw_cursor_enter_trampoline(GLFWwindow *w, int entered) { zval a[2]; ZVAL_LONG(&a[1], entered); glfw_window_dispatch(w, GLFW_CB_CURSOR_ENTER, 2, a); }
static void glfw_scroll_trampoline(GLFWwindow *w, double x, double y) { zval a[3]; ZVAL_DOUBLE(&a[1], x); ZVAL_DOUBLE(&a[2], y); glfw_window_dispatch(w, GLFW_CB_SCROLL, 3, a); }

/* Stores or clears slot's callable, points GLFW at the trampoline or at nothing, and returns the previous callable. */
#define GLFW_WINDOW_CALLBACK(fn, slot, trampoline) \
ZEND_FUNCTION(fn) \
{ \
	zend_object *window_obj; \
	zend_fcall_info fci; \
	zend_fcall_info_cache fcc; \
	zval none, *callback; \
	ZEND_PARSE_PARAMETERS_START(2, 2) \
		Z_PARAM_OBJ_OF_CLASS(window_obj, glfw_ce_GLFWwindow) \
		Z_PARAM_FUNC_OR_NULL(fci, fcc) \
	ZEND_PARSE_PARAMETERS_END(); \
	GLFW_WINDOW_ARG(window, window_obj, 1) \
	ZVAL_NULL(&none); \
	callback = ZEND_FCI_INITIALIZED(fci) ? &fci.function_name : &none; \
	glfw_window_callbacks *callbacks = glfw_callbacks_for(window, Z_TYPE_P(callback) != IS_NULL); \
	if (callbacks != NULL) { \
		glfw_swap_callback(&callbacks->callbacks[slot], callback, return_value); \
	} \
	fn(window, Z_TYPE_P(callback) == IS_NULL ? NULL : trampoline); \
}

GLFW_WINDOW_CALLBACK(glfwSetWindowPosCallback, GLFW_CB_POS, glfw_pos_trampoline)
GLFW_WINDOW_CALLBACK(glfwSetWindowSizeCallback, GLFW_CB_SIZE, glfw_size_trampoline)
GLFW_WINDOW_CALLBACK(glfwSetWindowCloseCallback, GLFW_CB_CLOSE, glfw_close_trampoline)
GLFW_WINDOW_CALLBACK(glfwSetWindowRefreshCallback, GLFW_CB_REFRESH, glfw_refresh_trampoline)
GLFW_WINDOW_CALLBACK(glfwSetWindowFocusCallback, GLFW_CB_FOCUS, glfw_focus_trampoline)
GLFW_WINDOW_CALLBACK(glfwSetWindowIconifyCallback, GLFW_CB_ICONIFY, glfw_iconify_trampoline)
GLFW_WINDOW_CALLBACK(glfwSetWindowMaximizeCallback, GLFW_CB_MAXIMIZE, glfw_maximize_trampoline)
GLFW_WINDOW_CALLBACK(glfwSetFramebufferSizeCallback, GLFW_CB_FRAMEBUFFER_SIZE, glfw_framebuffer_trampoline)
GLFW_WINDOW_CALLBACK(glfwSetWindowContentScaleCallback, GLFW_CB_CONTENT_SCALE, glfw_scale_trampoline)
GLFW_WINDOW_CALLBACK(glfwSetKeyCallback, GLFW_CB_KEY, glfw_key_trampoline)
GLFW_WINDOW_CALLBACK(glfwSetCharCallback, GLFW_CB_CHAR, glfw_char_trampoline)
GLFW_WINDOW_CALLBACK(glfwSetMouseButtonCallback, GLFW_CB_MOUSE_BUTTON, glfw_mouse_button_trampoline)
GLFW_WINDOW_CALLBACK(glfwSetCursorPosCallback, GLFW_CB_CURSOR_POS, glfw_cursor_pos_trampoline)
GLFW_WINDOW_CALLBACK(glfwSetCursorEnterCallback, GLFW_CB_CURSOR_ENTER, glfw_cursor_enter_trampoline)
GLFW_WINDOW_CALLBACK(glfwSetScrollCallback, GLFW_CB_SCROLL, glfw_scroll_trampoline)

ZEND_FUNCTION(glfwGetKeyName)
{
	zend_long key, scancode;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(key)
		Z_PARAM_LONG(scancode)
	ZEND_PARSE_PARAMETERS_END();
	GLFW_INT_ARG(native_key, key, 1)
	GLFW_INT_ARG(native_scancode, scancode, 2)

	const char *name = glfwGetKeyName(native_key, native_scancode);
	if (name == NULL) {
		RETURN_NULL();
	}
	RETURN_STRING(name);
}

ZEND_FUNCTION(glfwGetKey)
{
	zend_object *window_obj;
	zend_long key;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJ_OF_CLASS(window_obj, glfw_ce_GLFWwindow)
		Z_PARAM_LONG(key)
	ZEND_PARSE_PARAMETERS_END();
	GLFW_WINDOW_ARG(window, window_obj, 1)
	GLFW_INT_ARG(native_key, key, 2)

	RETURN_LONG(glfwGetKey(window, native_key));
}

ZEND_FUNCTION(glfwGetCursorPos)
{
	zend_object *window_obj;
	zval *refs[2];
	double values[2];

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJ_OF_CLASS(window_obj, glfw_ce_GLFWwindow)
		Z_PARAM_ZVAL(refs[0])
		Z_PARAM_ZVAL(refs[1])
	ZEND_PARSE_PARAMETERS_END();
	GLFW_WINDOW_ARG(window, window_obj, 1)

	glfwGetCursorPos(window, &values[0], &values[1]);
	ZEND_TRY_ASSIGN_REF_DOUBLE(refs[0], values[0]);
	if (EG(exception)) {
		return;
	}
	ZEND_TRY_ASSIGN_REF_DOUBLE(refs[1], values[1]);
}

/* ---- Events and time ------------------------------------------------------ */

ZEND_FUNCTION(glfwPollEvents)
{
	ZEND_PARSE_PARAMETERS_NONE();
	glfwPollEvents();
}

ZEND_FUNCTION(glfwWaitEvents)
{
	ZEND_PARSE_PARAMETERS_NONE();
	glfwWaitEvents();
}

ZEND_FUNCTION(glfwWaitEventsTimeout)
{
	double timeout;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_DOUBLE(timeout)
	ZEND_PARSE_PARAMETERS_END();

	glfwWaitEventsTimeout(timeout);
}

ZEND_FUNCTION(glfwPostEmptyEvent)
{
	ZEND_PARSE_PARAMETERS_NONE();
	glfwPostEmptyEvent();
}

ZEND_FUNCTION(glfwGetTime)
{
	ZEND_PARSE_PARAMETERS_NONE();
	RETURN_DOUBLE(glfwGetTime());
}

ZEND_FUNCTION(glfwSetTime)
{
	double time;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_DOUBLE(time)
	ZEND_PARSE_PARAMETERS_END();

	glfwSetTime(time);
}

ZEND_FUNCTION(glfwGetTimerValue)
{
	ZEND_PARSE_PARAMETERS_NONE();
	RETURN_LONG((zend_long) glfwGetTimerValue());
}

ZEND_FUNCTION(glfwGetTimerFrequency)
{
	ZEND_PARSE_PARAMETERS_NONE();
	RETURN_LONG((zend_long) glfwGetTimerFrequency());
}

/* ---- Context -------------------------------------------------------------- */

ZEND_FUNCTION(glfwMakeContextCurrent)
{
	zend_object *window_obj = NULL;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS_OR_NULL(window_obj, glfw_ce_GLFWwindow)
	ZEND_PARSE_PARAMETERS_END();

	glfwMakeContextCurrent(glfw_optional_ptr(window_obj));
}

ZEND_FUNCTION(glfwGetCurrentContext)
{
	ZEND_PARSE_PARAMETERS_NONE();
	glfw_box(return_value, glfwGetCurrentContext(), glfw_ce_GLFWwindow);
}

ZEND_FUNCTION(glfwSwapInterval)
{
	zend_long interval;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(interval)
	ZEND_PARSE_PARAMETERS_END();
	GLFW_INT_ARG(native, interval, 1)

	glfwSwapInterval(native);
}

ZEND_FUNCTION(glfwExtensionSupported)
{
	zend_string *extension;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(extension)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_LONG(glfwExtensionSupported(ZSTR_VAL(extension)));
}

ZEND_FUNCTION(glfwGetProcAddress)
{
	zend_string *procname;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(procname)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_LONG((zend_long) (uintptr_t) glfwGetProcAddress(ZSTR_VAL(procname)));
}

/* ---- Vulkan --------------------------------------------------------------- */

ZEND_FUNCTION(glfwInitVulkanLoader)
{
	zend_long loader;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(loader)
	ZEND_PARSE_PARAMETERS_END();

	glfwInitVulkanLoader((PFN_vkGetInstanceProcAddr) (uintptr_t) loader);
}

ZEND_FUNCTION(glfwVulkanSupported)
{
	ZEND_PARSE_PARAMETERS_NONE();
	RETURN_LONG(glfwVulkanSupported());
}

ZEND_FUNCTION(glfwGetRequiredInstanceExtensions)
{
	uint32_t count = 0;

	ZEND_PARSE_PARAMETERS_NONE();

	const char **extensions = glfwGetRequiredInstanceExtensions(&count);
	array_init_size(return_value, count);
	for (uint32_t i = 0; extensions != NULL && i < count; i++) {
		add_next_index_string(return_value, extensions[i]);
	}
}

ZEND_FUNCTION(glfwGetPhysicalDevicePresentationSupport)
{
	zend_long instance, device, queuefamily;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(instance)
		Z_PARAM_LONG(device)
		Z_PARAM_LONG(queuefamily)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_LONG(glfwGetPhysicalDevicePresentationSupport((VkInstance) (uintptr_t) instance, (VkPhysicalDevice) (uintptr_t) device, (uint32_t) queuefamily));
}

ZEND_FUNCTION(glfwGetInstanceProcAddress)
{
	zend_long instance;
	zend_string *procname;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(instance)
		Z_PARAM_STR(procname)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_LONG((zend_long) (uintptr_t) glfwGetInstanceProcAddress((VkInstance) (uintptr_t) instance, ZSTR_VAL(procname)));
}

ZEND_FUNCTION(glfwCreateWindowSurface)
{
	zend_long instance, allocator;
	zend_object *window_obj;
	zval *surface_ref;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_LONG(instance)
		Z_PARAM_OBJ_OF_CLASS(window_obj, glfw_ce_GLFWwindow)
		Z_PARAM_LONG(allocator)
		Z_PARAM_ZVAL(surface_ref)
	ZEND_PARSE_PARAMETERS_END();
	GLFW_WINDOW_ARG(window, window_obj, 2)

	VkSurfaceKHR surface = 0;
	VkResult result = glfwCreateWindowSurface((VkInstance) (uintptr_t) instance, window,
		(const VkAllocationCallbacks *) (uintptr_t) allocator, &surface);
	ZEND_TRY_ASSIGN_REF_LONG(surface_ref, (zend_long) (uintptr_t) surface);
	RETURN_LONG(result);
}

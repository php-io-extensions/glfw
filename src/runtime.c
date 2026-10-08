#include "runtime.h"

static zend_object_handlers glfw_handle_handlers;

static zend_object *glfw_create_object(zend_class_entry *ce)
{
	glfw_handle *intern = zend_object_alloc(sizeof(glfw_handle), ce);

	zend_object_std_init(&intern->std, ce);
	object_properties_init(&intern->std, ce);
	intern->std.handlers = &glfw_handle_handlers;
	intern->ptr = NULL;

	return &intern->std;
}

static void glfw_free_object(zend_object *object)
{
	glfw_handle *intern = glfw_handle_from(object);

	if (intern->ptr != NULL) {
		zend_hash_index_del(&GLFW_G(boxes), (zend_ulong) (uintptr_t) intern->ptr);
		intern->ptr = NULL;
	}
	zend_object_std_dtor(object);
}

void glfw_handle_setup(zend_class_entry *ce)
{
	static bool handlers_ready = false;

	if (!handlers_ready) {
		memcpy(&glfw_handle_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
		glfw_handle_handlers.offset = XtOffsetOf(glfw_handle, std);
		glfw_handle_handlers.free_obj = glfw_free_object;
		glfw_handle_handlers.clone_obj = NULL;
		handlers_ready = true;
	}

	ce->create_object = glfw_create_object;
	ce->default_object_handlers = &glfw_handle_handlers;
	ce->ce_flags |= ZEND_ACC_NOT_SERIALIZABLE;
}

void glfw_box(zval *rv, void *ptr, zend_class_entry *ce)
{
	zend_object *existing;

	if (ptr == NULL) {
		ZVAL_NULL(rv);
		return;
	}

	existing = zend_hash_index_find_ptr(&GLFW_G(boxes), (zend_ulong) (uintptr_t) ptr);
	if (existing != NULL && instanceof_function(existing->ce, ce)) {
		ZVAL_OBJ_COPY(rv, existing);
		return;
	}
	if (existing != NULL) {
		/* Another class boxed this address. Detach it so its free_obj cannot drop the new entry. */
		glfw_handle_from(existing)->ptr = NULL;
	}

	object_init_ex(rv, ce);
	glfw_handle_from(Z_OBJ_P(rv))->ptr = ptr;
	zend_hash_index_update_ptr(&GLFW_G(boxes), (zend_ulong) (uintptr_t) ptr, Z_OBJ_P(rv));
}

void *glfw_handle_ptr(zend_object *obj, uint32_t arg_num)
{
	void *ptr = glfw_handle_from(obj)->ptr;

	if (ptr == NULL) {
		const char *what = obj->ce == glfw_ce_GLFWmonitor ? "has been disconnected" : "has been destroyed";
		if (arg_num == 0) {
			zend_value_error("%s %s", ZSTR_VAL(obj->ce->name), what);
		} else {
			zend_argument_value_error(arg_num, "%s %s", ZSTR_VAL(obj->ce->name), what);
		}
	}

	return ptr;
}

bool glfw_optional_ptr(zend_object *obj, uint32_t arg_num, void **out)
{
	if (obj == NULL) {
		*out = NULL;
		return true;
	}
	*out = glfw_handle_ptr(obj, arg_num);
	return *out != NULL;
}

void glfw_release_ptr(void *ptr)
{
	zend_object *existing = zend_hash_index_find_ptr(&GLFW_G(boxes), (zend_ulong) (uintptr_t) ptr);

	if (existing != NULL) {
		glfw_handle_from(existing)->ptr = NULL;
		zend_hash_index_del(&GLFW_G(boxes), (zend_ulong) (uintptr_t) ptr);
	}
}

void glfw_release_all(zend_class_entry *ce)
{
	zend_ulong key;
	zend_object *obj;

	ZEND_HASH_FOREACH_NUM_KEY_PTR(&GLFW_G(boxes), key, obj) {
		if (obj->ce == ce) {
			glfw_handle_from(obj)->ptr = NULL;
			zend_hash_index_del(&GLFW_G(boxes), key);
		}
	} ZEND_HASH_FOREACH_END();
}

glfw_window_callbacks *glfw_callbacks_for(GLFWwindow *window, bool create)
{
	glfw_window_callbacks *callbacks = zend_hash_index_find_ptr(&GLFW_G(window_callbacks), (zend_ulong) (uintptr_t) window);

	if (callbacks == NULL && create) {
		callbacks = emalloc(sizeof(glfw_window_callbacks));
		for (int i = 0; i < GLFW_CB_COUNT; i++) {
			ZVAL_UNDEF(&callbacks->callbacks[i]);
		}
		zend_hash_index_add_new_ptr(&GLFW_G(window_callbacks), (zend_ulong) (uintptr_t) window, callbacks);
	}

	return callbacks;
}

static void glfw_callbacks_free(glfw_window_callbacks *callbacks)
{
	for (int i = 0; i < GLFW_CB_COUNT; i++) {
		zval_ptr_dtor(&callbacks->callbacks[i]);
	}
	efree(callbacks);
}

void glfw_callbacks_drop(GLFWwindow *window)
{
	glfw_window_callbacks *callbacks = glfw_callbacks_for(window, false);

	if (callbacks != NULL) {
		zend_hash_index_del(&GLFW_G(window_callbacks), (zend_ulong) (uintptr_t) window);
		glfw_callbacks_free(callbacks);
	}
}

/* Stops a live window calling back into PHP: every callback slot GLFW holds for it goes NULL. */
static void glfw_unset_native_callbacks(GLFWwindow *window)
{
	glfwSetWindowPosCallback(window, NULL);
	glfwSetWindowSizeCallback(window, NULL);
	glfwSetWindowCloseCallback(window, NULL);
	glfwSetWindowRefreshCallback(window, NULL);
	glfwSetWindowFocusCallback(window, NULL);
	glfwSetWindowIconifyCallback(window, NULL);
	glfwSetWindowMaximizeCallback(window, NULL);
	glfwSetFramebufferSizeCallback(window, NULL);
	glfwSetWindowContentScaleCallback(window, NULL);
}

void glfw_callbacks_drop_all(bool unset_native)
{
	zend_ulong key;
	glfw_window_callbacks *callbacks;

	ZEND_HASH_FOREACH_NUM_KEY_PTR(&GLFW_G(window_callbacks), key, callbacks) {
		if (unset_native) {
			glfw_unset_native_callbacks((GLFWwindow *) (uintptr_t) key);
		}
		glfw_callbacks_free(callbacks);
	} ZEND_HASH_FOREACH_END();
	zend_hash_clean(&GLFW_G(window_callbacks));
}

void glfw_call(zval *callable, uint32_t argc, zval *argv)
{
	zval retval;

	if (Z_TYPE_P(callable) == IS_UNDEF || EG(exception) != NULL) {
		return;
	}
	if (call_user_function(NULL, NULL, callable, &retval, argc, argv) == SUCCESS) {
		zval_ptr_dtor(&retval);
	}
}

void glfw_return_vidmode(zval *rv, const GLFWvidmode *mode)
{
	if (mode == NULL) {
		ZVAL_NULL(rv);
		return;
	}

	object_init_ex(rv, glfw_ce_GLFWvidmode);
	zend_object *obj = Z_OBJ_P(rv);
	zend_update_property_long(glfw_ce_GLFWvidmode, obj, ZEND_STRL("width"), mode->width);
	zend_update_property_long(glfw_ce_GLFWvidmode, obj, ZEND_STRL("height"), mode->height);
	zend_update_property_long(glfw_ce_GLFWvidmode, obj, ZEND_STRL("redBits"), mode->redBits);
	zend_update_property_long(glfw_ce_GLFWvidmode, obj, ZEND_STRL("greenBits"), mode->greenBits);
	zend_update_property_long(glfw_ce_GLFWvidmode, obj, ZEND_STRL("blueBits"), mode->blueBits);
	zend_update_property_long(glfw_ce_GLFWvidmode, obj, ZEND_STRL("refreshRate"), mode->refreshRate);
}

#ifndef GLFW_RUNTIME_H
#define GLFW_RUNTIME_H

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <stdint.h>
#include "php.h"
#include "zend_exceptions.h"
#include "php_glfw.h"

/*
 * The Vulkan types glfw3.h declares its Vulkan functions with, so the build needs no Vulkan
 * headers. They match the Vulkan ABI: dispatchable handles are pointers, VkSurfaceKHR is a
 * pointer on 64-bit targets and a uint64_t elsewhere, VkResult is a 32-bit enum.
 */
#ifndef VK_VERSION_1_0
typedef struct VkInstance_T *VkInstance;
typedef struct VkPhysicalDevice_T *VkPhysicalDevice;
# if defined(__LP64__) || defined(_WIN64) || defined(__x86_64__) || defined(__aarch64__)
typedef struct VkSurfaceKHR_T *VkSurfaceKHR;
# else
typedef uint64_t VkSurfaceKHR;
# endif
typedef int32_t VkResult;
typedef struct VkAllocationCallbacks VkAllocationCallbacks;
typedef void (*PFN_vkVoidFunction)(void);
typedef PFN_vkVoidFunction (*PFN_vkGetInstanceProcAddr)(VkInstance instance, const char *name);
# define VK_VERSION_1_0 1
#endif

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

/* The per-window callbacks, in the order glfw_window_callbacks holds them. */
enum {
	GLFW_CB_POS,
	GLFW_CB_SIZE,
	GLFW_CB_CLOSE,
	GLFW_CB_REFRESH,
	GLFW_CB_FOCUS,
	GLFW_CB_ICONIFY,
	GLFW_CB_MAXIMIZE,
	GLFW_CB_FRAMEBUFFER_SIZE,
	GLFW_CB_CONTENT_SCALE,
	GLFW_CB_KEY,
	GLFW_CB_CHAR,
	GLFW_CB_MOUSE_BUTTON,
	GLFW_CB_CURSOR_POS,
	GLFW_CB_CURSOR_ENTER,
	GLFW_CB_SCROLL,
	GLFW_CB_COUNT
};

typedef struct {
	zval callbacks[GLFW_CB_COUNT];   /* UNDEF where none is set */
} glfw_window_callbacks;

ZEND_BEGIN_MODULE_GLOBALS(glfw)
	HashTable boxes;                 /* native address => zend_object*, live handles only, not refcounted */
	HashTable window_callbacks;      /* GLFWwindow* => glfw_window_callbacks* */
	zval error_callback;             /* UNDEF when none */
	zval monitor_callback;           /* UNDEF when none */
ZEND_END_MODULE_GLOBALS(glfw)

ZEND_EXTERN_MODULE_GLOBALS(glfw)
#define GLFW_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(glfw, v)

typedef struct {
	void *ptr;                       /* the native handle; NULL once destroyed or disconnected */
	zend_object std;
} glfw_handle;

static zend_always_inline glfw_handle *glfw_handle_from(zend_object *obj)
{
	return (glfw_handle *) ((char *) obj - XtOffsetOf(glfw_handle, std));
}

extern zend_class_entry *glfw_ce_GLFWwindow;
extern zend_class_entry *glfw_ce_GLFWmonitor;
extern zend_class_entry *glfw_ce_GLFWvidmode;
extern zend_class_entry *glfw_ce_GLFWgammaramp;
extern zend_class_entry *glfw_ce_GLFWimage;

/* The PHP object holding ptr, or a new one of class ce. NULL ptr → null. */
void glfw_box(zval *rv, void *ptr, zend_class_entry *ce);
/* The live pointer in a handle; throws ValueError ("GLFWwindow has been destroyed") once released. Check EG(exception). */
void *glfw_handle_ptr(zend_object *obj, uint32_t arg_num);
/* The pointer in a handle a GLFW function takes as NULL-able: NULL for a null object or a released handle. */
static zend_always_inline void *glfw_optional_ptr(zend_object *obj)
{
	return obj != NULL ? glfw_handle_from(obj)->ptr : NULL;
}
/* Clears the handle boxing ptr, if any: its PHP object answers "destroyed" from then on. */
void glfw_release_ptr(void *ptr);
/* Releases every boxed handle of class ce. */
void glfw_release_all(zend_class_entry *ce);
void glfw_handle_setup(zend_class_entry *ce);

/* Window callbacks. */
glfw_window_callbacks *glfw_callbacks_for(GLFWwindow *window, bool create);
void glfw_callbacks_drop(GLFWwindow *window);
void glfw_callbacks_drop_all(bool unset_native);
/* Calls a stored callable; does nothing while an exception is pending. */
void glfw_call(zval *callable, uint32_t argc, zval *argv);

/* Value objects. */
void glfw_return_vidmode(zval *rv, const GLFWvidmode *mode);

void glfw_register_glfw3(int module_number);
void glfw_register_glfw3native(int module_number);

/*
 * The probe switch. A kept refusal site reads `if (!GLFW_PROBE_OFF("<id>") && (<check>))`.
 * A build configured with --enable-glfw-probes lets env GLFW_PROBE_OFF=<id> turn that one
 * site off, so tests/Probes can show the crash the site prevents; any other build compiles
 * the switch out.
 */
#ifdef GLFW_PROBES
bool glfw_probe_off(const char *id);
# define GLFW_PROBE_OFF(id) glfw_probe_off(id)
#else
# define GLFW_PROBE_OFF(id) 0
#endif

/* A list's C count, given as its own parameter: false (and a ValueError) when it is past the list. */
bool glfw_list_count(zend_long given, uint32_t length, uint32_t count_arg, uint32_t list_arg);

/* pointer() and fromPointer() for a handle class: the address as is, 0 once released; fromPointer(0) is null. */
#define GLFW_POINTER_METHODS(cls) \
	ZEND_METHOD(cls, pointer) { ZEND_PARSE_PARAMETERS_NONE(); RETURN_LONG((zend_long) (uintptr_t) glfw_handle_from(Z_OBJ_P(ZEND_THIS))->ptr); } \
	ZEND_METHOD(cls, fromPointer) { zend_long p; ZEND_PARSE_PARAMETERS_START(1, 1) Z_PARAM_LONG(p) ZEND_PARSE_PARAMETERS_END(); \
		glfw_box(return_value, (void *) (uintptr_t) p, zend_get_called_scope(execute_data)); } \
	ZEND_METHOD(cls, __construct) { ZEND_PARSE_PARAMETERS_NONE(); zend_throw_error(NULL, "%s cannot be constructed", #cls); RETURN_THROWS(); }

/* A window parameter's live pointer, or RETURN_THROWS. */
#define GLFW_WINDOW_ARG(var, obj, n) GLFWwindow *var = glfw_handle_ptr(obj, n); if (EG(exception)) { RETURN_THROWS(); }
#define GLFW_MONITOR_ARG(var, obj, n) GLFWmonitor *var = glfw_handle_ptr(obj, n); if (EG(exception)) { RETURN_THROWS(); }

#endif

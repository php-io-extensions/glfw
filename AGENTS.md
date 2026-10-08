# Agent guidance — php-io-extensions/glfw

1. **Read [`.okf/index.md`](.okf/index.md) first** before changing the API, the C, or packaging. Open only the concepts the change touches.
2. **Bindings are 1:1 at the GLFW 3.4 API, input excluded.** Function and constant names are the C names. No defaults, no composites. Keyboard, mouse, cursor, joystick and gamepad functions and constants are not bound.
3. **Translations, the only ones.** An out-parameter is by-reference. A list GLFW returns with a count is a PHP list. A function address, Vulkan handle or native handle is an `int`. A boolean return is `bool`; hints and attributes stay `int`. Failure is `glfwGetError()`.
4. **Handles.** `GLFWwindow`, `GLFWmonitor`: `final`, private `__construct`, not cloneable, not serializable, `pointer(): int`, `static fromPointer(int $pointer): static`. One PHP object per native pointer (`glfw_box`). `glfwDestroyWindow` releases a window; `glfwTerminate` releases every window and monitor; a disconnected monitor is released after the monitor callback. A released handle throws `ValueError`.
5. **Callbacks.** Window callbacks live in `GLFW_G(window_callbacks)` keyed by the window; the error and monitor callbacks in globals. A callback never runs while an exception is pending. RSHUTDOWN tells GLFW to stop calling, then frees the callables.
6. **No foreign headers.** Vulkan types (`runtime.h`) and native-access prototypes (`glfw3native.c`) are declared locally with ABI-identical types. Do not include `vulkan.h` or `glfw3native.h`.
7. **The stub is the declaration.** Edit `stubs/*.stub.php`, regenerate with `php84 /opt/homebrew/opt/php@8.4/lib/php/build/gen_stub.php stubs`, commit both. Never hand-edit `*_arginfo.h`. `@param list<…>` breaks gen_stub; describe lists in prose.
8. **Build.** `./install-macos.sh` into Homebrew `php@8.4` and `php@8.4-zts`. On the Pi, copy the tree with `fnk` and `./install-debian-trixie.sh`. Pest at `-d memory_limit=128M`. On the Pi export `WAYLAND_DISPLAY=wayland-0 DISPLAY=:0 XDG_RUNTIME_DIR=/run/user/$(id -u)`, and leave ext-gtk out of the run (GTK 3 libdecor + GTK 4 deadlock). Gate a commit on the suite's exit code.
9. **Platform facts are tested, not skipped.** Where GLFW answers `GLFW_FEATURE_UNAVAILABLE` (Wayland position/opacity/icon/gamma, macOS icon), the test asserts that code.
10. **Durable facts go in `.okf`.** Update the matching concept and append `.okf/log.md`.
11. **Version** is `PHP_GLFW_VERSION` in `php_glfw.h`: 0.10.0. `os-families`: linux, darwin.

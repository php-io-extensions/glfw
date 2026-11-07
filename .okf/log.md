# Log

## 2026-11-06

* **`glfwGetKey`** (glfw3.h:4901). `glfwGetKey(GLFWwindow $window, int $key): int` answers `GLFW_PRESS` or `GLFW_RELEASE`, the last state GLFW reported for the key to the window (`GLFW_REPEAT` only ever reaches a key callback). The released-window case is the existing `glfw-released-handle` site: no new `bindings.json` entry. A bad key (`GLFW_KEY_UNKNOWN`) is `GLFW_INVALID_ENUM` through `glfwGetError()` and reads `GLFW_RELEASE`. Limit, GLFW's own: it is the state GLFW has been told, so a modifier already held when the window gained focus may read `GLFW_RELEASE` until GLFW sees its next event. `SurfaceTest` function count 96 (Linux 104). `KeyStateTest` opens a hidden window (not run). 108 / 149.

* **`glfwGetKeyName` and `glfwGetCursorPos`** (glfw3.h:4835, 4968). `glfwGetKeyName(int $key, int $scancode): ?string` returns null where GLFW returns NULL. `glfwGetCursorPos($window, ?float &$xpos, ?float &$ypos)` takes its out-parameters by reference as `glfwGetWindowContentScale` does, with the C doubles written whole. `KeyNameTest` needs `glfwInit` only; the cursor position test is in `InputCallbackTest` and opens a hidden window (not run). 107 / 149.

* **Input callbacks and constants**: `glfwSetKeyCallback`, `glfwSetCharCallback`, `glfwSetMouseButtonCallback`, `glfwSetCursorPosCallback`, `glfwSetCursorEnterCallback`, `glfwSetScrollCallback` (glfw3.h:5198, 5241, 5320, 5352, 5383, 5417), each returning the callback it replaces, with `GLFW_RELEASE`/`PRESS`/`REPEAT`, the 122 `GLFW_KEY_*`, `GLFW_MOD_SHIFT`/`CONTROL`/`ALT`/`SUPER` and `GLFW_MOUSE_BUTTON_1`…`8`: 137 constants, 1:1 with the header. The window callback macro takes its callable through `Z_PARAM_FUNC_OR_NULL`, so PHP's own parser raises the TypeError for a callable that is not one (the extension raises none; the message still reads "must be a valid callback or null"). Not bound: polling, cursors, input modes, clipboard, joystick, gamepad. `InputConstantsTest` checks every constant against the installed header. `InputCallbackTest` opens a hidden window and has not been run. 105 / 149.

* **ext-guard**: enrolled; `bindings.json` holds three refusal sites, each with a probe in `tests/Probes` run on a `--enable-glfw-probes` build (`GLFW_PROBE_OFF=<site>` turns one off): `glfw-released-handle` (SIGSEGV, shown on macOS), `glfw-icon-pixels-length` and `glfw-list-count` (Linux only: macOS has no window icon).
* **Dropped refusals**, none of which crashed with the check off: 32-bit int range (now C conversion), icon sizes 1–4096, gamma size 0 and 0–65535 range, wait timeout ≤ 0 / NaN, queue family range, Vulkan instance 0. A destroyed window passes to GLFW as NULL where GLFW takes NULL.
* **API, 1:1**: GLFW_TRUE/FALSE functions return `int` and `glfwSetWindowShouldClose` takes `int`; focus/iconify/maximize callbacks get `int`; `glfwSet*Callback` returns the previous callable; `glfwSetWindowIcon($window, $count, $images)`; `pointer()` is 0 once released; `fromPointer` returns `?static`, null for 0.
* Audit 0. Homebrew PHP 8.4 NTS and ZTS: the whole suite passes (Linux-only tests skipped), the released-handle probes included; jovian/venusian-glfw passes against it. Not run yet: the icon probes (Linux only) and the Pi.

## 2026-10-28

* **Version**: 0.11.0 in `PHP_GLFW_VERSION` (`php_glfw.h`), `AGENTS.md`, README and the index; `branch-alias` `dev-main` is `0.11.x-dev`. Promoted with the Venusian 0.11 ecosystem. No API or behaviour change. Built and loaded on Homebrew PHP 8.4 NTS and ZTS (55 passed, 2 skipped each) and the Pi on 8.4 ZTS. On the Pi `WindowTest` and `CallbackTest` hang at their first visible window, under Wayland and Xwayland alike; the other seven files pass.
* **Open — Pi hang**: on the Pi `WindowTest` stops at "moves and resizes" and `CallbackTest` at "calls back on move, resize and framebuffer resize", both right after a `GLFW_VISIBLE` window opens; Pest never returns. Not investigated.
* **Open — GLFW 3.3 hosts**: an x86_64 Ubuntu-family box ships GLFW 3.3.10 (`libglfw3-dev`), so `configure` refuses (`glfw3 >= 3.4`) and 0.7.0 stays installed there.
* **Coverage**: `scripts/support.php` writes `SUPPORT.md` and the README's API badge: every `GLFWAPI` function of `glfw3.h` and `glfw3native.h` at the GLFW 3.4 tag (the floor), input included, bound when a stub declares the function of the same name. Headers download once into `scripts/.support-cache/` (gitignored); `--check` exits 1 when the list or badge is stale. 99 / 149 (66.4%).

## 2026-10-09


## 2026-10-08

* Bundle created with ext-glfw 0.10.0: plain C, GLFW 3.4, input excluded. 83 functions plus 4 native on macOS (Cocoa, NSGL) or 12 on Linux (X11, Wayland, GLX, EGL), 5 classes, every non-input constant. Suite 57 tests: macOS NTS + ZTS (55 passed, 2 Linux-only skipped), Pi 5 ZTS under labwc Wayland (53 passed, 4 skipped). [bindings](api/bindings.md), [handles and callbacks](architecture/handles-and-callbacks.md), [platform facts](architecture/platforms.md), [build](runbooks/build.md), [adding a binding](runbooks/adding-a-binding.md).

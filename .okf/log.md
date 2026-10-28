# Log

## 2026-10-28

* **Version**: 0.11.0 in `PHP_GLFW_VERSION` (`php_glfw.h`), `AGENTS.md`, README and the index; `branch-alias` `dev-main` is `0.11.x-dev`. Promoted with the Venusian 0.11 ecosystem. No API or behaviour change. Built and loaded on Homebrew PHP 8.4 NTS and ZTS (55 passed, 2 skipped each) and the Pi on 8.4 ZTS. On the Pi `WindowTest` and `CallbackTest` hang at their first visible window, under Wayland and Xwayland alike; the other seven files pass.
* **Open — Pi hang**: on the Pi `WindowTest` stops at "moves and resizes" and `CallbackTest` at "calls back on move, resize and framebuffer resize", both right after a `GLFW_VISIBLE` window opens; Pest never returns. Not investigated.
* **Open — GLFW 3.3 hosts**: an x86_64 Ubuntu-family box ships GLFW 3.3.10 (`libglfw3-dev`), so `configure` refuses (`glfw3 >= 3.4`) and 0.7.0 stays installed there.

## 2026-10-09


## 2026-10-08

* Bundle created with ext-glfw 0.10.0: plain C, GLFW 3.4, input excluded. 83 functions plus 4 native on macOS (Cocoa, NSGL) or 12 on Linux (X11, Wayland, GLX, EGL), 5 classes, every non-input constant. Suite 57 tests: macOS NTS + ZTS (55 passed, 2 Linux-only skipped), Pi 5 ZTS under labwc Wayland (53 passed, 4 skipped). [bindings](api/bindings.md), [handles and callbacks](architecture/handles-and-callbacks.md), [platform facts](architecture/platforms.md), [build](runbooks/build.md), [adding a binding](runbooks/adding-a-binding.md).

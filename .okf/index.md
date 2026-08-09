---
okf_version: "0.2"
---

# php-io-extensions/glfw

Cross-platform (Linux + macOS) PHP extension: Zephir bindings for **libGLFW ≥ 3.4.0** — init, windows, monitors, input, OpenGL context/swap, and Vulkan surface helpers. A small `Glfw\GLFW\GL\GLFWGL` convenience slice supports visual demos; full OpenGL draw API belongs to peer `php-io-extensions/open-gl`.

**Prefer** concepts with `status: stable` when present; content is currently `draft` pending Angel’s human verification of the OKF docs (implementation facts are grounded in shipped sources).

This is the **native extension** (`ext-glfw`). Downstream PHP wrappers live in `microscrap/glfw` — composition only in this bundle.

# Orientation

* [Package overview](orientation/overview.md) - What glfw is, version targets, and what it deliberately is not
* [Stack segmentation](orientation/stack-segmentation.md) - Boundaries vs open-gl, sdl3, metal, microscrap

# Architecture

* [Layered stack](architecture/stack.md) - Zephir → GLFW C API → libglfw (+ optional OpenGL for GLFWGL)
* [Zephir inline C](architecture/zephir-inline-c.md) - `%{ … %}` bridges, callbacks, opaque ints
* [Linking GLFW + GL](architecture/linking-glfw.md) - pkg-config glfw3, Darwin OpenGL.framework / Linux -lGL

# Public PHP API

* [Glfw\\GLFW\\GLFW](api/glfw.md) - Init, terminate, version, platform, error callback (~10)
* [Glfw\\GLFW\\GLFWError](api/glfwerror.md) - `glfwGetError` → code/description
* [Glfw\\GLFW\\Window\\GLFWWindow](api/window.md) - Windows, hints, attributes, event loop (~47)
* [Glfw\\GLFW\\Monitor\\GLFWMonitor](api/monitor.md) - Monitors, video modes, gamma (~15)
* [Glfw\\GLFW\\Input\\GLFWInput](api/input.md) - Keys, mouse, cursors, joystick/gamepad, clipboard, time (~40)
* [Glfw\\GLFW\\Context\\GLFWContext](api/context.md) - Make current, swap, proc address (~6)
* [Glfw\\GLFW\\Vulkan\\GLFWVulkan](api/vulkan.md) - Vulkan support + window surface (~5)
* [Glfw\\GLFW\\GL\\GLFWGL](api/glfwgl.md) - Minimal gl* for demos (~8) — not open-gl

# Build & packaging

* [Zephir + PIE install](build/zephir-and-pie.md) - installers, PIE, phpize path
* [Committed ext/ notes](build/packaging-ext.md) - config.m4, GCC 14, stubs, version headers

# Conventions

* [Sibling patterns](conventions/sibling-patterns.md) - Patterns from sdl3 / open-gl / metal (not deps)
* [Handle ownership](conventions/handle-ownership.md) - Opaque ints; create/destroy pairs
* [No FFI](conventions/no-ffi.md) - Extension-only binding
* [Constants in microscrap](conventions/constants-microscrap.md) - No class constants; enums elsewhere

# Traps

* [Windows excluded](traps/windows-excluded.md) - PIE os-families-exclude
* [Retina framebuffer vs window size](traps/retina-framebuffer.md) - Use glfwGetFramebufferSize for glViewport
* [REGISTER_CLASS truncation](traps/register-class-truncation.md) - Zephir 0.19 nested namespace risk
* [GCC 14 warning flags](traps/gcc14-warning-flags.md) - config.m4 demotion for Zephir C
* [GLFWGL vs open-gl](traps/gl-convenience-vs-opengl.md) - Do not grow full GL into this ext

# Playbooks

* [Minimal demo loop](playbooks/demo-loop.md) - proof_of_work / proof_monitor / proof_window
* [Regenerate committed ext/](playbooks/regenerate-ext.md) - Maintainer steps before tagging

# Indexes

* [Orientation](orientation/) — start here
* [Architecture](architecture/)
* [API](api/)
* [Build](build/)
* [Conventions](conventions/)
* [Traps](traps/)
* [Playbooks](playbooks/)

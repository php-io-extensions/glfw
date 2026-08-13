---
type: Orientation
title: Package overview
description: What glfw is, version targets, and what it deliberately is not
resource: /composer.json
tags: [glfw, orientation, php-ext]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T17:35:00Z }
sources:
  - id: composer
    resource: /composer.json
    title: PIE package manifest
  - id: config
    resource: /config.json
    title: Zephir config
  - id: readme
    resource: /README.md
    title: Package README
  - id: php-h
    resource: /ext/php_glfw.h
    title: PHP_GLFW_VERSION
  - id: demo
    resource: /examples/proof_of_work.php
    title: proof_of_work.php
---

# Summary

`php-io-extensions/glfw` is a **Linux + macOS** PHP extension (`type: php-ext`) that exposes **GLFW 3.4+** windowing, monitors, input, OpenGL context/swap, and Vulkan helpers to PHP 8.2+ as namespaced static classes under `Glfw\GLFW\…`. It links system **libglfw** and (for the small `GLFWGL` demo slice) platform OpenGL.[^composer][^readme]

| Fact | Value |
|------|--------|
| Package | `php-io-extensions/glfw` |
| Extension name | `glfw` |
| Version | `0.7.1` |
| PHP | `>= 8.2` (ZTS + NTS) |
| OS | Linux + macOS; Windows excluded |
| Namespace | `Glfw\GLFW\*` |
| Author | Project Saturn Studios, LLC |
| License | MIT |
| Binding | Zephir + inline C → `glfw*` / minimal `gl*` — **no FFI** |
| GLFW | ≥ 3.4.0 (`pkg-config glfw3`) |

Version is aligned across `composer.json`, `config.json`, and `PHP_GLFW_VERSION` in `ext/php_glfw.h`.[^composer][^config][^php-h]

# End capability (v0.7)

Documented public surface on disk includes:

1. Lifecycle / version / platform (`GLFW`, `GLFWError`)
2. Windows + event loop (`Window\GLFWWindow`)
3. Monitors + video modes / gamma (`Monitor\GLFWMonitor`)
4. Keyboard / mouse / cursor / joystick / gamepad / clipboard / time (`Input\GLFWInput`)
5. OpenGL context make-current + swap (`Context\GLFWContext`)
6. Vulkan support helpers + window surface (`Vulkan\GLFWVulkan`)
7. Minimal OpenGL convenience for demos (`GL\GLFWGL` — 8 entry points)

README claims all **124** `GLFWAPI` functions from GLFW 3.4 are bound (plus the separate `GLFWGL` slice).[^readme]

Canonical headless smoke: `examples/proof_of_work.php`.[^demo]

# What it is not

- Not a high-level PHP framework wrapper — that is **microscrap/glfw** (bindings/enums layer).
- Not a tubes framebuffer/gfx companion — that is **ogx / glfw-gfx** (out of scope here).
- Not the full OpenGL draw API — that is **php-io-extensions/open-gl**.
- Not Apple AppKit/Metal — that is `php-io-extensions/metal`.
- Not SDL3 windowing — that is `php-io-extensions/sdl3` (peer alternate path).
- Not available on Windows.
- Not an FFI wrapper and not a home for PHP class constants (`GLFW_*` / `GL_*` live in app locals or microscrap enums).

# Public namespace

Zephir classes live under `Glfw\GLFW\` (`glfw/glfw/**/*.zep`). IDE stubs: `ide/0.7.1/Glfw/GLFW/` (including `GL/GLFWGL.php`).

See [Stack segmentation](/orientation/stack-segmentation.md) and [Layered stack](/architecture/stack.md).

[^composer]: PIE package manifest
[^config]: Zephir config
[^readme]: Package README
[^php-h]: PHP_GLFW_VERSION
[^demo]: proof_of_work.php

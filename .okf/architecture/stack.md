---
type: Architecture
title: Layered stack
description: Zephir → GLFW C API → libglfw (+ optional OpenGL for GLFWGL)
resource: /config.json
tags: [glfw, architecture, zephir]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T17:35:00Z }
sources:
  - id: config
    resource: /config.json
    title: Zephir config
  - id: composer
    resource: /composer.json
    title: PIE package manifest
  - id: config-m4
    resource: /ext/config.m4
    title: Portable ext/config.m4
---

# Layers

```text
PHP (Glfw\GLFW\{GLFW,GLFWError,Window,Monitor,Input,Context,Vulkan,GL})
        │  Zephir static methods + opaque int handles
        ▼
GLFW C API (GLFW/glfw3.h)  — and OpenGL C API for GLFWGL only
        │
        ▼
libglfw (≥ 3.4.0)
   + Darwin: OpenGL.framework  (GLFWGL)
   + Linux:  libGL             (GLFWGL)
```

Unlike metal, there is **no** Objective-C bridge. Unlike open-gl’s DTO `fd` objects, GLFW opaque pointers are plain PHP `int` handles (same style as sdl3).[^config]

# Source map

| Layer | Path | Role |
|-------|------|------|
| Zephir | `glfw/glfw/**/*.zep` | Public PHP API |
| Zephir config | `config.json` | Extension metadata + destructor `glfwTerminate()` |
| Packaging | `ext/` | Committed generated C for PIE/`phpize` |
| PIE | `composer.json` | `build-path: ext`, Linux+Darwin |

# Design intent

- Thin 1:1 static methods mirroring C `glfw*` names.
- Opaque `GLFWwindow*` / `GLFWmonitor*` / `GLFWcursor*` → `int`.
- Out-params and C structs → associative arrays with field names matching GLFW.
- Callbacks accept `callable|null` (`null` clears).
- Constants stay out of the extension — see [Constants in microscrap](/conventions/constants-microscrap.md).

[^config]: Zephir config
[^composer]: PIE package manifest
[^config-m4]: Portable ext/config.m4

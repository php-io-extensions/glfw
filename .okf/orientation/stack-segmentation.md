---
type: Orientation
title: Stack segmentation
description: Boundaries vs open-gl, sdl3, metal, and microscrap/glfw
tags: [glfw, orientation, boundaries]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T17:35:00Z }
sources:
  - id: composer
    resource: /composer.json
    title: PIE package manifest
  - id: readme
    resource: /README.md
    title: Package README
  - id: demo
    resource: /examples/proof_window.php
    title: proof_window.php
  - id: glfwgl
    resource: /glfw/glfw/gl/glfwgl.zep
    title: glfwgl.zep
---

# Who owns what

| Concern | Package | Notes |
|---------|---------|--------|
| Native GLFW C API in PHP | **`php-io-extensions/glfw`** | This package — Zephir extension[^readme][^composer] |
| Typed PHP wrappers / enums / ergonomics | `microscrap/glfw` | Downstream wrap; composition only here |
| Tubes / GFX framebuffer companions | `ogx` / `glfw-gfx` (etc.) | Out of scope — do not invent here |
| Full OpenGL `gl*` draw / state API | `php-io-extensions/open-gl` | Peer; demos may pair |
| Minimal gl* for GLFW proofs | **`Glfw\GLFW\GL\GLFWGL`** | 8 methods only — not a full GL binding[^glfwgl] |
| Alternate window / GPU path | `php-io-extensions/sdl3` | Peer; not a dep |
| Native macOS AppKit + Metal | `php-io-extensions/metal` | Darwin-only product — not a dep |
| Enum / flag values (`GLFW_*`, `GL_*`) | app locals or microscrap enums | Not compiled into this extension |

# Composition sketch

```text
PHP app / tubes
  ├─ microscrap/glfw            → ergonomic wrappers + enums (optional)
  ├─ microscrap/open-gl         → full GL surface (optional)
  └─ php-io-extensions/glfw     → native GLFW (this package)
         ├─ libglfw ≥ 3.4.0
         └─ (optional) platform OpenGL for GLFWGL demos
```

Typical OpenGL demo:

```text
glfw → create window + make context current
  └─ open-gl (or GLFWGL convenience) → draw
       └─ glfwSwapBuffers / poll events
```

Visual proof in-tree uses `GLFWGL` only: `examples/proof_window.php`.[^demo]

# Hard rules

1. Do **not** document microscrap/glfw or gfx companion APIs inside this OKF — only composition boundaries.
2. Do **not** add sdl3/metal/open-gl as runtime Composer deps of this package.
3. Do **not** grow `GLFWGL` into a full OpenGL binding — that is open-gl’s job.
4. Do **not** nest a second `.okf` under `glfw/glfw/`.
5. Keep Windows out of PIE (`os-families-exclude: ["windows"]`).[^composer]

[^composer]: PIE package manifest
[^readme]: Package README
[^demo]: proof_window.php
[^glfwgl]: glfwgl.zep

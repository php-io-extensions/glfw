---
type: Architecture
title: Linking GLFW + GL
description: pkg-config glfw3, Homebrew paths, Darwin OpenGL.framework / Linux -lGL
resource: /ext/config.m4
tags: [glfw, architecture, linking, build]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T17:35:00Z }
sources:
  - id: config-m4
    resource: /ext/config.m4
    title: Portable ext/config.m4
  - id: config
    resource: /config.json
    title: Zephir config
  - id: readme
    resource: /README.md
    title: Package README
---

# Requirements

Configure requires `pkg-config` and **glfw3 ≥ 3.4.0**. Missing/outdated glfw3 fails `./configure`.[^config-m4][^readme]

# How `ext/config.m4` links

1. `PKG_CHECK` / `$PKG_CONFIG --exists glfw3` → libs/cflags via pkg-config.
2. Extra search-path hints: `-L/opt/homebrew/lib -L/usr/local/lib -lglfw` (Homebrew /usr/local layouts).
3. OpenGL for `Glfw\GLFW\GL\GLFWGL`:
   - **Darwin:** `-framework OpenGL`
   - **else:** `-lGL`
4. GCC 14 warning demotion flags + `-DGL_SILENCE_DEPRECATION` (macOS GL noise).[^config-m4]

# Zephir-time hints

`config.json` `extra-cflags` / `extra-libs` mirror Homebrew/local paths for maintainer Zephir builds.[^config]

# Guidance

- Prefer `PKG_CONFIG_PATH` that includes Homebrew’s `lib/pkgconfig` on Apple Silicon.
- Do not assume Vulkan SDK headers are present — Vulkan helpers use opaque stubs in Zephir.
- Full GL draw still needs a current context from this extension (or sdl3) before calling into open-gl / GLFWGL.

[^config-m4]: Portable ext/config.m4
[^config]: Zephir config
[^readme]: Package README

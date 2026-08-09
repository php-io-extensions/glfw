---
type: CoreType
title: Glfw\GLFW\Window\GLFWWindow
description: Window creation, attributes, callbacks, and event loop
resource: /glfw/glfw/window/glfwwindow.zep
tags: [glfw, api, window]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T17:35:00Z }
sources:
  - id: window-zep
    resource: /glfw/glfw/window/glfwwindow.zep
    title: glfwwindow.zep
  - id: readme
    resource: /README.md
    title: README
---

# Role

Windows, hints, attributes, user pointer, window/framebuffer callbacks, and the event pump.[^window-zep]

# Schema (groups)

## Hints / create / destroy

| Method | Notes |
|--------|--------|
| `glfwDefaultWindowHints()` | |
| `glfwWindowHint(int, int)` / `glfwWindowHintString(int, string)` | |
| `glfwCreateWindow(int, int, string, monitor=null, share=null)` | Returns window `int`; hard failures throw `\RuntimeException`[^readme] |
| `glfwDestroyWindow(int)` | |

## State / geometry

Includes should-close, title, icon (`GLFWimage` → `width/height/pixels`), pos/size, size limits, aspect ratio, **framebuffer size**, frame size, content scale, opacity, iconify/restore/maximize/show/hide/focus/attention, monitor attach, attribs, user pointer.

## Callbacks

`glfwSetWindow*Callback` / `glfwSetFramebufferSizeCallback` / content-scale — each takes `callable|null`.

## Event loop

| Method |
|--------|
| `glfwPollEvents()` |
| `glfwWaitEvents()` |
| `glfwWaitEventsTimeout(double)` |
| `glfwPostEmptyEvent()` |

~47 `public static` methods on `Glfw\GLFW\Window\GLFWWindow`.[^window-zep]

# Binding notes

- Opaque `GLFWwindow*` / monitor → `int`
- Out-params → assoc arrays (`xpos`/`ypos`, `width`/`height`, …)
- On HiDPI, prefer `glfwGetFramebufferSize` for GL viewports — see [Retina trap](/traps/retina-framebuffer.md)

[^window-zep]: glfwwindow.zep
[^readme]: README

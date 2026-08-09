---
type: CoreType
title: Glfw\GLFW\Context\GLFWContext
description: Make current, swap buffers, swap interval, proc address
resource: /glfw/glfw/context/glfwcontext.zep
tags: [glfw, api, context, opengl]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T17:35:00Z }
sources:
  - id: context-zep
    resource: /glfw/glfw/context/glfwcontext.zep
    title: glfwcontext.zep
---

# Role

OpenGL context management for a GLFW window. Call before drawing with `GLFWGL` or `php-io-extensions/open-gl`.[^context-zep]

# Schema

| Method | Returns | Notes |
|--------|---------|--------|
| `glfwMakeContextCurrent(int window)` | `void` | `0` clears current |
| `glfwGetCurrentContext()` | `int` | |
| `glfwSwapBuffers(int window)` | `void` | |
| `glfwSwapInterval(int interval)` | `void` | |
| `glfwExtensionSupported(string)` | `bool` | |
| `glfwGetProcAddress(string)` | `int` | Function pointer as int, or `0` |

[^context-zep]: glfwcontext.zep

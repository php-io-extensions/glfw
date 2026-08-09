---
type: CoreType
title: Glfw\GLFW\GL\GLFWGL
description: Minimal OpenGL entry points for GLFW context demos
resource: /glfw/glfw/gl/glfwgl.zep
tags: [glfw, api, opengl, convenience]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T17:35:00Z }
sources:
  - id: glfwgl-zep
    resource: /glfw/glfw/gl/glfwgl.zep
    title: glfwgl.zep
  - id: demo
    resource: /examples/proof_window.php
    title: proof_window.php
---

# Role

**Convenience only** — eight OpenGL entry points so visual proofs can clear/scissor without loading `php-io-extensions/open-gl`.[^glfwgl-zep] Not a full GL binding; see [GLFWGL vs open-gl](/traps/gl-convenience-vs-opengl.md).

# Schema

| Method | Returns |
|--------|---------|
| `glClearColor(float, float, float, float)` | `void` |
| `glClear(int mask)` | `void` |
| `glViewport(int, int, int, int)` | `void` |
| `glScissor(int, int, int, int)` | `void` |
| `glEnable(int)` / `glDisable(int)` | `void` |
| `glGetError()` | `int` |
| `glGetString(int name)` | `string` |

Requires a current context (`GLFWContext::glfwMakeContextCurrent`). Constants are not in this class — pass ints / microscrap enums.[^demo]

[^glfwgl-zep]: glfwgl.zep
[^demo]: proof_window.php

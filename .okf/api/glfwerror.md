---
type: CoreType
title: Glfw\GLFW\GLFWError
description: glfwGetError → associative code/description
resource: /glfw/glfw/glfwerror.zep
tags: [glfw, api, error]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T17:35:00Z }
sources:
  - id: error-zep
    resource: /glfw/glfw/glfwerror.zep
    title: glfwerror.zep
---

# Role

Query the last GLFW error without installing a callback.[^error-zep]

# Schema

| Method | Returns |
|--------|---------|
| `glfwGetError()` | `array{code: int, description: string}` (`description` is `""` when GLFW returns NULL) |

[^error-zep]: glfwerror.zep

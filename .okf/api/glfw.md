---
type: CoreType
title: Glfw\GLFW\GLFW
description: Init, terminate, version, platform, error callback
resource: /glfw/glfw/glfw.zep
tags: [glfw, api, init]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T17:35:00Z }
sources:
  - id: glfw-zep
    resource: /glfw/glfw/glfw.zep
    title: glfw.zep
  - id: readme
    resource: /README.md
    title: README
---

# Role

Lifecycle and platform entry points for GLFW.[^glfw-zep]

# Schema

| Method | Returns | Notes |
|--------|---------|--------|
| `glfwInit()` | `bool` | |
| `glfwTerminate()` | `void` | Also module destructor in `config.json` |
| `glfwInitHint(int, int)` | `void` | |
| `glfwInitAllocator(var = null)` | `void` | Custom allocators not exposed; null restores defaults |
| `glfwInitVulkanLoader(int = 0)` | `void` | `0` = NULL loader |
| `glfwGetVersion()` | `array` | `major` / `minor` / `rev` |
| `glfwGetVersionString()` | `string` | |
| `glfwSetErrorCallback(callable\|null)` | `void` | `null` clears |
| `glfwGetPlatform()` | `int` | |
| `glfwPlatformSupported(int)` | `bool` | |

All methods are `public static` on `Glfw\GLFW\GLFW`.[^glfw-zep][^readme]

[^glfw-zep]: glfw.zep
[^readme]: README

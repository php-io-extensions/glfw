---
type: CoreType
title: Glfw\GLFW\Vulkan\GLFWVulkan
description: Vulkan support query and window surface creation
resource: /glfw/glfw/vulkan/glfwvulkan.zep
tags: [glfw, api, vulkan]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T17:35:00Z }
sources:
  - id: vulkan-zep
    resource: /glfw/glfw/vulkan/glfwvulkan.zep
    title: glfwvulkan.zep
---

# Role

GLFW’s Vulkan helpers. Compiles without `vulkan.h` via opaque stubs in the Zephir preamble.[^vulkan-zep]

# Schema

| Method | Returns | Notes |
|--------|---------|--------|
| `glfwVulkanSupported()` | `bool` | |
| `glfwGetRequiredInstanceExtensions()` | `array` | list of strings |
| `glfwGetInstanceProcAddress(int instance, string)` | `int` | |
| `glfwGetPhysicalDevicePresentationSupport(int, int, int)` | `bool` | |
| `glfwCreateWindowSurface(int instance, int window, int allocator = 0)` | `array{result: int, surface: int}` | |

Opaque Vulkan / GLFW pointers are PHP `int` (`0` = NULL where applicable).

[^vulkan-zep]: glfwvulkan.zep

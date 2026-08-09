---
type: Convention
title: Handle ownership
description: Create/destroy opaque GLFW ints; PHP GC does not free natives
tags: [glfw, convention, memory, handles]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T17:35:00Z }
sources:
  - id: readme
    resource: /README.md
    title: Package README
  - id: window-zep
    resource: /glfw/glfw/window/glfwwindow.zep
    title: glfwwindow.zep
  - id: input-zep
    resource: /glfw/glfw/input/glfwinput.zep
    title: glfwinput.zep
  - id: config
    resource: /config.json
    title: Zephir config destructor
---

# Rules (representative)

| Object | Create | Destroy |
|--------|--------|---------|
| Window | `GLFWWindow::glfwCreateWindow` | `glfwDestroyWindow` |
| Cursor | `GLFWInput::glfwCreateCursor` / `CreateStandardCursor` | `glfwDestroyCursor` |
| Monitor | queried (`glfwGetMonitors`) | Do not free — owned by GLFW |
| Vulkan surface | `GLFWVulkan::glfwCreateWindowSurface` | Destroy via Vulkan API (not GLFW destroy helper here) |

# Semantics

- `0` means null/failure; do not destroy `0`.
- Dropping a PHP int without calling destroy **leaks** until `glfwTerminate` / process exit.
- Module unload / `config.json` destructor calls `glfwTerminate()`.[^config]
- Typical teardown: destroy windows/cursors → `GLFW::glfwTerminate()`.

# Checklist

1. Pair every create with destroy.
2. After create failure, check `GLFWError::glfwGetError()` (create may also throw `\RuntimeException`).[^readme]
3. Do not share opaque handles across process forks.

[^readme]: Package README
[^window-zep]: glfwwindow.zep
[^input-zep]: glfwinput.zep
[^config]: Zephir config destructor

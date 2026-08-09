---
type: CoreType
title: Glfw\GLFW\Monitor\GLFWMonitor
description: Monitors, video modes, gamma, monitor callback
resource: /glfw/glfw/monitor/glfwmonitor.zep
tags: [glfw, api, monitor]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T17:35:00Z }
sources:
  - id: monitor-zep
    resource: /glfw/glfw/monitor/glfwmonitor.zep
    title: glfwmonitor.zep
  - id: readme
    resource: /README.md
    title: README
---

# Role

Enumerate monitors and query video modes / gamma.[^monitor-zep]

# Schema (summary)

| Area | Methods |
|------|---------|
| Enumerate | `glfwGetMonitors()`, `glfwGetPrimaryMonitor()` |
| Geometry / meta | pos, workarea, physical size, content scale, name |
| User pointer | set/get |
| Callback | `glfwSetMonitorCallback(callable\|null)` |
| Video modes | `glfwGetVideoModes`, `glfwGetVideoMode` → `width/height/redBits/greenBits/blueBits/refreshRate`[^readme] |
| Gamma | `glfwSetGamma`, `glfwGetGammaRamp`, `glfwSetGammaRamp` |

~15 `public static` methods on `Glfw\GLFW\Monitor\GLFWMonitor`.[^monitor-zep]

[^monitor-zep]: glfwmonitor.zep
[^readme]: README

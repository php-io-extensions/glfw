---
type: CoreType
title: Glfw\GLFW\Input\GLFWInput
description: Keyboard, mouse, cursors, joystick/gamepad, clipboard, time
resource: /glfw/glfw/input/glfwinput.zep
tags: [glfw, api, input]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T17:35:00Z }
sources:
  - id: input-zep
    resource: /glfw/glfw/input/glfwinput.zep
    title: glfwinput.zep
  - id: readme
    resource: /README.md
    title: README
---

# Role

Input modes, keys/mouse, cursors, drop/scroll callbacks, joystick/gamepad, clipboard, and timer APIs.[^input-zep]

# Schema (groups)

| Area | Examples |
|------|----------|
| Modes | `glfwGetInputMode`, `glfwSetInputMode`, `glfwRawMouseMotionSupported` |
| Keys / mouse | `glfwGetKey*`, `glfwGetMouseButton`, cursor pos set/get, **`glfwGetCursorX` / `glfwGetCursorY`** (scalars; no hashtable) |
| Cursors | `glfwCreateCursor` / `CreateStandardCursor` / `DestroyCursor` / `SetCursor` |
| Callbacks | key, char, charmods, mouse button, cursor pos/enter, scroll, drop |
| Joystick / gamepad | present, axes/buttons/hats, name/GUID, mappings, gamepad state, **`glfwGetGamepadButton` / `glfwGetGamepadAxis`** (scalars; no hashtable) |
| Clipboard | `glfwSetClipboardString`, `glfwGetClipboardString` |
| Time | `glfwGetTime`, `glfwSetTime`, `glfwGetTimerValue`, `glfwGetTimerFrequency` |

`GLFWimage` for custom cursors: `["width","height","pixels"]` (`pixels` binary RGBA string).[^readme]

~40 `public static` methods on `Glfw\GLFW\Input\GLFWInput`.[^input-zep]

[^input-zep]: glfwinput.zep
[^readme]: README

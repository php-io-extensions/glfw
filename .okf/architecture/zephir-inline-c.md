---
type: Architecture
title: Zephir inline C
description: "%{ … %} blocks calling glfw* / gl*; callback bridges; opaque ints"
resource: /glfw/glfw/glfw.zep
tags: [glfw, architecture, zephir, c]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T17:35:00Z }
sources:
  - id: glfw-zep
    resource: /glfw/glfw/glfw.zep
    title: glfw.zep
  - id: window-zep
    resource: /glfw/glfw/window/glfwwindow.zep
    title: glfwwindow.zep
  - id: vulkan-zep
    resource: /glfw/glfw/vulkan/glfwvulkan.zep
    title: glfwvulkan.zep
  - id: config
    resource: /config.json
    title: Zephir config
---

# Pattern

Each module `.zep` typically:

1. Declares `namespace Glfw\GLFW\…`
2. Opens an inline C preamble (`#include <GLFW/glfw3.h>`, helpers)
3. Implements `public static function …` methods whose bodies mix Zephir locals with `%{ … %}` C snippets that call `glfw*` (or `gl*` in `GLFWGL`)[^glfw-zep]

Example shape (`GLFW::glfwInit`):

```zephir
public static function glfwInit() -> bool
{
    bool result;
    %{
        result = glfwInit() == GLFW_TRUE;
    }%
    return result;
}
```

# Opaque handles

Pointers are cast through `uintptr_t` to/from PHP `int`. Passing `0` means NULL where the C API allows it (e.g. make-context-current clear).[^window-zep]

# Callbacks

Error/window/input callbacks store a PHP `zval` callable and bridge via static C functions that `call_user_function`. Passing `null` clears the callback.[^glfw-zep]

# Vulkan stubs

`glfwvulkan.zep` defines opaque Vulkan typedefs when `VK_VERSION_1_0` is absent so GLFW Vulkan helpers compile without `vulkan.h`.[^vulkan-zep]

# Build path

- Maintainers regenerate via Zephir (`fullclean`/`build`) or installer scripts.
- Consumers/`pie` build from committed `ext/` via `phpize` + `--enable-glfw` — they do not need Zephir.

`config.json` supplies Homebrew/local include and `-lglfw` link hints for Zephir builds, plus a module destructor that calls `glfwTerminate()`.[^config]

[^glfw-zep]: glfw.zep
[^window-zep]: glfwwindow.zep
[^vulkan-zep]: glfwvulkan.zep
[^config]: Zephir config

---
type: Convention
title: Constants in microscrap
description: No class constants in the extension; GLFW/GL enums live elsewhere
tags: [glfw, convention, enums, microscrap]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T17:35:00Z }
sources:
  - id: readme
    resource: /README.md
    title: README
  - id: glfwgl
    resource: /glfw/glfw/gl/glfwgl.zep
    title: glfwgl.zep
  - id: demo
    resource: /examples/proof_window.php
    title: proof_window.php
---

# Rule

Do **not** define PHP/Zephir class constants for `GLFW_*` / `GL_*` values inside this extension.[^readme][^glfwgl]

House backed enums / constant catalogs in **microscrap/glfw** (or another shared PHP package). Call sites pass `int` / enum-backed values into `Glfw\GLFW\*` methods.

# Why

- Project convention: prefer PHP Enums (FULLY UPPERCASE cases) over class constants.
- Keeps the extension binary smaller and avoids duplicating huge `#define` tables in C.
- Lets enum packages evolve without rebuilding the extension for every constant add.

# Guidance

```php
// preferred (illustrative)
GLFWWindow::glfwWindowHint(WindowHint::VISIBLE->value, 0);

// avoid in this extension
// class GLFWWindow { public const VISIBLE = 0x00020004; }
```

Demos currently inline a few local `const` ints for smoke convenience; production code should prefer microscrap enums.[^demo]

[^readme]: README
[^glfwgl]: glfwgl.zep
[^demo]: proof_window.php

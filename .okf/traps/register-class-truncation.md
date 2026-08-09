---
type: Trap
title: REGISTER_CLASS truncation
description: Zephir 0.19 may truncate nested Glfw\GLFW\* namespaces in ZEPHIR_REGISTER_CLASS
tags: [glfw, trap, zephir, register]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T17:35:00Z }
sources:
  - id: readme
    resource: /README.md
    title: README
  - id: php-h
    resource: /ext/php_glfw.h
    title: PHP_GLFW_ZEPVERSION
---

# Symptom

Extension builds but classes are missing/wrong, or `ZEPHIR_REGISTER_CLASS` lines show shortened namespaces for `glfw/glfw/...` paths.[^readme]

# Cause

Zephir 0.19 has truncated nested namespace segments when emitting register macros (same class of bug as metal `Metal\MTL\*` → `Metal\MT\*` and open-gl `Opengl\GL\*`). This package’s tree is `Glfw\GLFW\…` under `glfw/glfw/`.[^php-h]

# Guidance

1. After `zephir generate`, run `scripts/prepare-ext.sh` (or at least `scripts/fixup-zephir-register.py`) before compile/commit.[^readme]
2. Inspect `ZEPHIR_REGISTER_CLASS` / `class_exists` for every public class if regenerating without the fixup.
3. Smoke with `php --ri glfw` and `class_exists` for `Glfw\\GLFW\\Window\\GLFWWindow` (etc.) before tagging.
4. Do not “fix” by renaming the public namespace without an explicit product decision.

[^readme]: README
[^php-h]: PHP_GLFW_ZEPVERSION

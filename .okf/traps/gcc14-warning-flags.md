---
type: Trap
title: GCC 14 warning-as-error
description: config.m4 demotes Zephir-hostile -Werror conversions on modern GCC
resource: /ext/config.m4
tags: [glfw, trap, gcc, build]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T17:35:00Z }
sources:
  - id: config-m4
    resource: /ext/config.m4
    title: config.m4
---

# Trap

Zephir-generated C trips GCC 14+ hard errors (`-Wincompatible-pointer-types`, `-Wint-conversion`, …). `ext/config.m4` demotes those back to warnings and sets `-DGL_SILENCE_DEPRECATION` for macOS GL noise in `GLFWGL`.[^config-m4]

If a clean rebuild fails with pointer-type errors after regenerating `ext/`, verify `config.m4` still carries the demotion flags before hand-editing generated kernel code.

[^config-m4]: config.m4

---
type: Convention
title: Sibling patterns
description: Patterns from sdl3 / open-gl / metal / posi (not dependencies)
tags: [glfw, convention, packaging]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T17:35:00Z }
sources:
  - id: composer
    resource: /composer.json
    title: composer.json
  - id: readme
    resource: /README.md
    title: README
---

# Borrowed patterns (style only)

| Pattern | From | How glfw uses it |
|---------|------|------------------|
| Thin Zephir static classes | sdl3 / open-gl | `Glfw\GLFW\*::*` mirrors C |
| Opaque int handles | sdl3 / metal | Windows/monitors/cursors as `int` |
| PIE `type: php-ext`, `build-path: ext` | siblings | Same layout in `composer.json`[^composer] |
| Version `0.7.1`, PHP ≥ 8.2 | siblings | Aligned release line |
| Windows excluded | sdl3 / open-gl | `os-families-exclude: ["windows"]` |
| IDE stubs path | sdl3 / open-gl | `ide/0.7.1/Glfw/GLFW/` |
| Constants outside ext | open-gl / sdl3 | microscrap / local ints[^readme] |

# Not borrowed

- No AppKit/Metal/ObjC bridge (metal only).
- No full OpenGL DTO/`fd` object model (open-gl).
- No composer `require` on peer extensions — demos compose them.

[^composer]: composer.json
[^readme]: README

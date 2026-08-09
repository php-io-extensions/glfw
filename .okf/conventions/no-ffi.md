---
type: Convention
title: No FFI
description: Extension-only binding; no PHP FFI fallback
tags: [glfw, convention, ffi]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T17:35:00Z }
sources:
  - id: composer
    resource: /composer.json
    title: composer.json
  - id: readme
    resource: /README.md
    title: README.md
---

# Rule

This package is a compiled PHP extension (`type: php-ext`). There is **no** PHP FFI code path, no pure-PHP polyfill, and no optional FFI mode.[^composer][^readme]

Consumers must install `glfw.so` (PIE or installers) and load `extension=glfw`.

Downstream PHP packages (`microscrap/glfw`) may wrap this extension’s classes — they still require the native extension.

[^composer]: composer.json
[^readme]: README.md

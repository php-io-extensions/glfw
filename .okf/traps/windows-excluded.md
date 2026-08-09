---
type: Trap
title: Windows excluded
description: PIE os-families-exclude windows — do not claim Windows support
resource: /composer.json
tags: [glfw, trap, windows, pie]
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

# Trap

`composer.json` sets `php-ext.os-families-exclude: ["windows"]`. README states Linux/macOS only.[^composer][^readme]

Do not document, CI, or invent Windows installers for this package without an explicit product decision to lift the exclude.

[^composer]: composer.json
[^readme]: README

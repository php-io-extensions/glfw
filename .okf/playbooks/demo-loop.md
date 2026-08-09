---
type: Playbook
title: Minimal demo loop
description: Headless proof_of_work plus optional monitor/window visuals
resource: /examples/proof_of_work.php
tags: [glfw, playbook, demo]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T17:35:00Z }
sources:
  - id: pow
    resource: /examples/proof_of_work.php
    title: proof_of_work.php
  - id: monitor
    resource: /examples/proof_monitor.php
    title: proof_monitor.php
  - id: window
    resource: /examples/proof_window.php
    title: proof_window.php
  - id: readme
    resource: /README.md
    title: Package README
---

# Goal

Prove the extension loads and exercises GLFW init / monitor / window paths as documented.[^readme]

# Prerequisites

- Built/installed `glfw.so`
- libglfw ≥ 3.4.0 discoverable at runtime
- Display required for `proof_window.php` (and optionally monitor UI)

# Canonical demos

```bash
# Headless smoke
php -n -d extension=ext/modules/glfw.so examples/proof_of_work.php

# Monitors / video modes
php -n -d extension=ext/modules/glfw.so examples/proof_monitor.php

# Visual window (rainbow clear + bouncing rect — ESC to quit)
php -n -d extension=ext/modules/glfw.so examples/proof_window.php
```

[^pow][^monitor][^window]

# What they exercise

| Script | Focus |
|--------|--------|
| `proof_of_work.php` | Extension load + basic GLFW lifecycle |
| `proof_monitor.php` | Monitor / video-mode queries |
| `proof_window.php` | Window + context + `GLFWGL` draw loop |

# Acceptance criteria

- Headless proof exits successfully without inventing APIs.
- Window proof creates a context, polls events, swaps buffers, and cleans up with destroy/terminate.

[^pow]: proof_of_work.php
[^monitor]: proof_monitor.php
[^window]: proof_window.php
[^readme]: Package README

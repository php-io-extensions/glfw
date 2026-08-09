---
type: Convention
title: Committed ext/ notes
description: config.m4, GCC 14 flags, stubs, and what belongs in git
resource: /ext/config.m4
tags: [glfw, build, packaging]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T17:35:00Z }
sources:
  - id: config-m4
    resource: /ext/config.m4
    title: Portable ext/config.m4
  - id: php-h
    resource: /ext/php_glfw.h
    title: php_glfw.h
  - id: config
    resource: /config.json
    title: Zephir config
  - id: composer
    resource: /composer.json
    title: PIE package manifest
---

# What ships in `ext/`

PIE/`phpize` builds from the pre-generated C tree under `ext/` (`build-path: ext`).[^composer]

| Artifact | Role |
|----------|------|
| `ext/config.m4` | `--enable-glfw`, pkg-config glfw3 ≥ 3.4.0, OpenGL link, GCC 14 demotion |
| `ext/php_glfw.h` | `PHP_GLFW_VERSION` (`0.7.0`) |
| `ext/glfw/` + kernel | Zephir-generated sources |

# GCC 14 / macOS GL

`config.m4` demotes Zephir-hostile warnings to non-errors and sets `-DGL_SILENCE_DEPRECATION`.[^config-m4] See [GCC 14 trap](/traps/gcc14-warning-flags.md).

# Stubs

`config.json` stubs path: `ide/%version%/%namespace%/`. For 0.7.x use `ide/0.7.0/Glfw/GLFW/` (includes `GL/GLFWGL.php`).[^config]

# Do not commit phpize junk

After local `phpize`/`make`, avoid committing `Makefile`, `configure`, `autom4te.cache`, `modules/*.so`, etc.

Run `bash scripts/prepare-ext.sh` before tagging — it regenerates C, rewrites portable `ext/config.m4`, applies REGISTER fixup, and strips phpize junk (same peer pattern as open-gl/metal). See [Regenerate ext](/playbooks/regenerate-ext.md).

[^config-m4]: Portable ext/config.m4
[^php-h]: php_glfw.h
[^config]: Zephir config
[^composer]: PIE package manifest

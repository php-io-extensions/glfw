---
type: Playbook
title: Regenerate committed ext/
description: Maintainer Zephir build steps before tagging 0.7.x
resource: /install-macos.sh
tags: [glfw, playbook, packaging, zephir]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T17:35:00Z }
sources:
  - id: install
    resource: /install-macos.sh
    title: install-macos.sh
  - id: config
    resource: /config.json
    title: config.json
  - id: php-h
    resource: /ext/php_glfw.h
    title: php_glfw.h
  - id: readme
    resource: /README.md
    title: README
---

# When

Before tagging a Packagist/PIE release, or after changing `.zep` / `config.json` / link flags.

# Steps

1. On Linux or macOS with Zephir + matching PHP + libglfw ≥ 3.4.0:

```bash
export PKG_CONFIG_PATH="/opt/homebrew/lib/pkgconfig:/usr/local/lib/pkgconfig:${PKG_CONFIG_PATH:-}"
bash scripts/prepare-ext.sh
# then: cd ext && phpize && ./configure --enable-glfw && make
```

Set `ZEPHIR_BIN` if `zephir` is not on `PATH`. Platform installers remain fine for machine installs.[^install][^readme]

2. Confirm version strings match **0.7.0** in `composer.json`, `config.json`, and `PHP_GLFW_VERSION` in `ext/php_glfw.h`.[^config][^php-h]

3. Verify `ZEPHIR_REGISTER_CLASS` / `class_exists` for all public classes (truncation trap).

4. Smoke:

```bash
php -n -d extension=./ext/modules/glfw.so --ri glfw
php -n -d extension=./ext/modules/glfw.so examples/proof_of_work.php
```

5. Refresh IDE stubs under `ide/0.7.0/` when the public surface changes.

6. Commit regenerable `ext/` sources + stubs that belong in git — not phpize junk.

7. Update `.okf` + `log.md` if the public surface or packaging changed.

# Notes

- Prefer `bash scripts/prepare-ext.sh` over raw `zephir generate` so REGISTER fixup + portable `config.m4` always apply.[^readme]
- Preserve `ext/config.m4` GCC 14 demotion + OpenGL link rules across regenerations (re-applied by `patch-config-m4.py`).

[^install]: install-macos.sh
[^config]: config.json
[^php-h]: php_glfw.h
[^readme]: README

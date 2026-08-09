---
type: Playbook
title: Zephir + PIE install
description: Install via PIE or platform scripts; phpize from committed ext/
resource: /composer.json
tags: [glfw, build, pie, zephir]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T17:35:00Z }
sources:
  - id: composer
    resource: /composer.json
    title: PIE package manifest
  - id: install
    resource: /install-macos.sh
    title: install-macos.sh
  - id: herd
    resource: /install-macos-herd.sh
    title: install-macos-herd.sh
  - id: debian
    resource: /install-debian-trixie.sh
    title: install-debian-trixie.sh
  - id: jetpack
    resource: /install-jetpack6.sh
    title: install-jetpack6.sh
  - id: readme
    resource: /README.md
    title: README
---

# Requirements

| Component | Notes |
|-----------|--------|
| OS | Linux or macOS (Windows excluded) |
| PHP | ≥ 8.2 with matching `phpize` / headers |
| GLFW | ≥ 3.4.0 via `pkg-config glfw3` |
| Zephir | Only for regenerating `ext/` |
| OpenGL | Needed at link/runtime for `GLFWGL` demos |

# PIE (consumers)

```bash
pie install php-io-extensions/glfw
```

Uses `type: php-ext`, `extension-name: glfw`, `build-path: "ext"`, `--enable-glfw`.[^composer]

# Platform installers

```bash
bash install-macos.sh
bash install-macos-herd.sh      # Laravel Herd
bash install-debian-trixie.sh   # Debian Trixie / Raspberry Pi OS
bash install-jetpack6.sh        # JetPack 6 / Ubuntu 22.04
```

[^install][^herd][^debian][^jetpack]

# Manual build from committed ext/

```bash
export PKG_CONFIG_PATH="/opt/homebrew/lib/pkgconfig:/usr/local/lib/pkgconfig:${PKG_CONFIG_PATH:-}"
cd ext && phpize && ./configure --enable-glfw && make
php -n -d extension="$(pwd)/modules/glfw.so" --ri glfw
```

# Maintainer prepare-ext

```bash
export PKG_CONFIG_PATH="/opt/homebrew/lib/pkgconfig:/usr/local/lib/pkgconfig:${PKG_CONFIG_PATH:-}"
bash scripts/prepare-ext.sh
```

Runs `zephir generate`, `scripts/patch-config-m4.py`, `scripts/fixup-zephir-register.py`, then strips phpize junk from `ext/`. Platform installers call the fixup after generate as well.[^readme]

[^composer]: PIE package manifest
[^install]: install-macos.sh
[^herd]: install-macos-herd.sh
[^debian]: install-debian-trixie.sh
[^jetpack]: install-jetpack6.sh
[^readme]: README

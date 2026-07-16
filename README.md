# php-glfw

[![PHP](https://img.shields.io/badge/php-%E2%89%A5%208.2-777bb4?logo=php&logoColor=white)](https://www.php.net)
[![GLFW](https://img.shields.io/badge/GLFW-%E2%89%A5%203.4.0-5586a4)](https://www.glfw.org/)
[![Built with Zephir](https://img.shields.io/badge/built%20with-Zephir-ff6a00)](https://zephir-lang.com/)
[![Platform](https://img.shields.io/badge/platform-linux%20%7C%20macOS-lightgrey)](#requirements)
[![License: MIT](https://img.shields.io/badge/license-MIT-green)](#license)

> PHP extension for GLFW 3.4 — built with [Zephir](https://zephir-lang.com/), installable via [PHP PIE](https://github.com/php/pie).

`glfw` exposes GLFW's init, window, monitor, input, context, and Vulkan APIs to
PHP 8.2+ as namespaced static classes under `Glfw\GLFW\…`. Methods mirror the C
API 1:1 and return values with the same semantics (opaque handles as `int`,
structs as arrays, PHP callables for GLFW callbacks).

This extension is the binding layer used by ScrapyardIO's Windowed Visual Output
stack (alongside `php-io-extensions/sdl3`). GLFW `#define` constants live in a
companion microscrap wrapper package, not in this extension.

---

## Requirements

| Component            | Minimum version | Notes                                                                   |
| -------------------- | --------------- | ----------------------------------------------------------------------- |
| PHP                  | 8.2             | ZTS and NTS builds both supported.                                      |
| GLFW                 | 3.4.0           | Must be discoverable via `pkg-config glfw3` or the usual search paths.  |
| OS                   | Linux / macOS   | x86_64 + aarch64 Linux, Darwin. Windows is not currently supported.     |
| Compiler             | C11 toolchain   | `gcc`, `clang`, or Apple Clang.                                         |
| `php-dev` / `phpize` | matches PHP     | Required for any build path that is not PIE.                            |

---

## Installation

### Via PHP PIE (recommended)

```bash
pie install php-io-extensions/glfw
```

### Platform installers

**macOS** (Homebrew):

```bash
bash install-macos.sh
```

**Debian Trixie / Raspberry Pi OS** (amd64, arm64):

```bash
bash install-debian-trixie.sh
```

**JetPack 6 / Ubuntu 22.04**:

```bash
bash install-jetpack6.sh
```

### Manual build with Zephir (maintainers)

```bash
export PKG_CONFIG_PATH="/opt/homebrew/lib/pkgconfig:/usr/local/lib/pkgconfig:${PKG_CONFIG_PATH:-}"
bash scripts/prepare-ext.sh   # generate + REGISTER fixup + portable config.m4 + strip phpize junk
cd ext && phpize && ./configure --enable-glfw && make
php -n -d extension=modules/glfw.so --ri glfw
```

`scripts/prepare-ext.sh` is what you run before committing / tagging for Packagist.
It rewrites `ext/config.m4` to the portable form (pkg-config + OS OpenGL link) and
strips `Makefile` / `configure` / `modules/` / `*.lo` so absolute host paths never ship.

> Zephir 0.19 truncates `ZEPHIR_REGISTER_CLASS` names for `glfw/glfw/...` paths —
> the prepare script applies that fix automatically.

---

## Quick start

```php
<?php
use Glfw\GLFW\GLFW;
use Glfw\GLFW\Window\GLFWWindow;
use Glfw\GLFW\Context\GLFWContext;

GLFW::glfwInit();

// GLFW_VISIBLE = 0x00020004 — prefer microscrap enums in real apps
GLFWWindow::glfwWindowHint(0x00020004, 0);
$window = GLFWWindow::glfwCreateWindow(800, 600, 'Hello GLFW');

while (!GLFWWindow::glfwWindowShouldClose($window)) {
    GLFWWindow::glfwPollEvents();
    GLFWContext::glfwSwapBuffers($window);
}

GLFWWindow::glfwDestroyWindow($window);
GLFW::glfwTerminate();
```

### Examples

```bash
# Headless smoke
php -n -d extension=ext/modules/glfw.so examples/proof_of_work.php

# Monitors / video modes
php -n -d extension=ext/modules/glfw.so examples/proof_monitor.php

# Visual window (rainbow clear + bouncing rect — ESC to quit)
php -n -d extension=ext/modules/glfw.so examples/proof_window.php
```

---

## API surface

| Class | Namespace | Coverage |
| ----- | --------- | -------- |
| `GLFW` | `Glfw\GLFW` | init, terminate, version, platform, error callback |
| `GLFWError` | `Glfw\GLFW` | `glfwGetError` → `["code","description"]` |
| `GLFWMonitor` | `Glfw\GLFW\Monitor` | monitors, video modes, gamma, monitor callback |
| `GLFWWindow` | `Glfw\GLFW\Window` | windows, attributes, event loop, window callbacks |
| `GLFWInput` | `Glfw\GLFW\Input` | keyboard/mouse/cursor/joystick/gamepad/clipboard/time |
| `GLFWContext` | `Glfw\GLFW\Context` | OpenGL context + swap |
| `GLFWVulkan` | `Glfw\GLFW\Vulkan` | Vulkan helpers |

All **124** `GLFWAPI` functions from GLFW 3.4 are bound.

### Binding conventions

- Opaque handles (`GLFWwindow*`, `GLFWmonitor*`, `GLFWcursor*`) → `int`
- Out-parameters → associative arrays
- `GLFWvidmode` → `width/height/redBits/greenBits/blueBits/refreshRate`
- `GLFWimage` → `["width","height","pixels"]` (`pixels` is binary RGBA string)
- Callbacks accept `callable|null` (`null` clears)
- Hard create failures throw `\RuntimeException`

---

## License

MIT — see [LICENSE](LICENSE).

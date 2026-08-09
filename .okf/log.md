# Directory Update Log

## 2026-08-09
* **Initialization**: Created OKF v0.2 knowledge bundle for `php-io-extensions/glfw` (native Zephir extension), mirroring peer depth from `open-gl/.okf`, `sdl3/.okf`, and `metal/.okf`. Documented orientation, architecture, API surface grounded in `glfw/glfw/**/*.zep`, build/packaging, conventions, traps, and playbooks. Added root `AGENTS.md` and `.gitattributes` (`export-ignore` for `.okf/` + `AGENTS.md`).
* **Update**: Version signals bumped to **0.7.0** in `composer.json`, `config.json`, and `PHP_GLFW_VERSION` (`ext/php_glfw.h`). README Version section aligned with open-gl peer style (`0.7.x` ecosystem docs line). IDE stub tree at `ide/0.7.0/` (legacy `ide/0.5.0/` removed).
* **Update**: Restored peer-style `scripts/` (`prepare-ext.sh`, `patch-config-m4.py`, `fixup-zephir-register.py`); portable `ext/config.m4` rewritten (per-dir `PHP_ADD_BUILD_DIR`, Homebrew prefix loop). Added missing `ide/0.7.0/.../GL/GLFWGL.php` stub. Removed trap `prepare-ext-missing.md`.
* **Note**: OKF concepts remain `draft` until Angel promotes to `stable`. Companion `microscrap/glfw` left on `ext-glfw ^0.5.0` by explicit decision (out of scope for this tag).

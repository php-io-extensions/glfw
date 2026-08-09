# Agent guidance — php-io-extensions/glfw

1. **Read [`.okf/index.md`](.okf/index.md) first** before changing architecture, API, or packaging.
2. Open only the concept files you need; prefer `status: stable` when present (most are currently `draft`).
3. This package is **Linux + macOS** GLFW **windowing / context / input** bindings — Windows excluded. Links **libglfw ≥ 3.4.0**. No FFI.
4. Public PHP API: static methods under `Glfw\GLFW\{GLFW,GLFWError,Window\GLFWWindow,Monitor\GLFWMonitor,Input\GLFWInput,Context\GLFWContext,Vulkan\GLFWVulkan,GL\GLFWGL}`. Opaque handles are PHP `int`; structs are assoc arrays; callbacks are `callable|null`.
5. `Glfw\GLFW\GL\GLFWGL` is a **minimal** OpenGL convenience slice for demos — full `gl*` API belongs in `php-io-extensions/open-gl`. Constants live in microscrap enums (or local ints), not class constants here.
6. Build: Zephir sources in `glfw/glfw/**/*.zep`; committed C under `ext/`. Installers: `install-macos.sh`, `install-macos-herd.sh`, `install-debian-trixie.sh`, `install-jetpack6.sh`. PIE: `pie install php-io-extensions/glfw`. Version target: **0.7.0**.
7. Demo: `examples/proof_of_work.php` (headless), `proof_monitor.php`, `proof_window.php` (visual).
8. Downstream: `microscrap/glfw` (PHP wrappers/enums) is a **peer wrap layer** — document composition only; do not nest its docs here. GFX / tubes companions (`ogx` / `glfw-gfx`) are separate.
9. When you learn a durable package fact, **update the matching `.okf` concept**, bump `generated.at`, and append `.okf/log.md`.
10. Do not invent APIs not present in `.zep` / `ext/` / README. Keep the OKF bundle at package root only — never nest `.okf` under `glfw/glfw/`.

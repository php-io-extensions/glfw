# Public PHP API

All public classes live under `Glfw\GLFW` and expose **static** methods. Opaque GLFW objects are PHP `int` handles. C structs are assoc arrays. Full method names live in `.zep` / `ide/0.7.0/`; concepts below summarize module scope grounded in sources on disk.

Method counts are `public static function` entries in the named `.zep` files (surface size, not a stability guarantee).

* [Glfw\\GLFW\\GLFW](glfw.md) - Init, terminate, version, platform (~10)
* [Glfw\\GLFW\\GLFWError](glfwerror.md) - Error query (~1)
* [Glfw\\GLFW\\Window\\GLFWWindow](window.md) - Windows & event loop (~47)
* [Glfw\\GLFW\\Monitor\\GLFWMonitor](monitor.md) - Monitors & video modes (~15)
* [Glfw\\GLFW\\Input\\GLFWInput](input.md) - Input, clipboard, time (~40)
* [Glfw\\GLFW\\Context\\GLFWContext](context.md) - Context & swap (~6)
* [Glfw\\GLFW\\Vulkan\\GLFWVulkan](vulkan.md) - Vulkan helpers (~5)
* [Glfw\\GLFW\\GL\\GLFWGL](glfwgl.md) - Minimal gl* for demos (~8)

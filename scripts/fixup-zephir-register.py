#!/usr/bin/env python3
"""Fix Zephir 0.19 ZEPHIR_REGISTER_CLASS truncation for Glfw\\GLFW\\* classes."""

from __future__ import annotations

import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
EXT = ROOT / "ext"

# Zephir 0.19 drops the last char of nested segments (GLFW → GFW, GL → G).
FIXES = {
    "Glfw\\GFW\\Window\\GLFWWindow": "Glfw\\GLFW\\Window\\GLFWWindow",
    "Glfw\\GFW\\Monitor\\GLFWMonitor": "Glfw\\GLFW\\Monitor\\GLFWMonitor",
    "Glfw\\GFW\\Input\\GLFWInput": "Glfw\\GLFW\\Input\\GLFWInput",
    "Glfw\\GFW\\Context\\GLFWContext": "Glfw\\GLFW\\Context\\GLFWContext",
    "Glfw\\GFW\\Vulkan\\GLFWVulkan": "Glfw\\GLFW\\Vulkan\\GLFWVulkan",
    "Glfw\\GFW\\GL\\GLFWGL": "Glfw\\GLFW\\GL\\GLFWGL",
    "Glfw\\GFW\\GLFWError": "Glfw\\GLFW\\GLFWError",
    "Glfw\\GFW\\GLFW": "Glfw\\GLFW\\GLFW",
    "Glfw\\GFW": "Glfw\\GLFW",
    "Glfw\\GLFW\\G\\GLFWGL": "Glfw\\GLFW\\GL\\GLFWGL",
}


def fix_file(path: Path) -> int:
    text = path.read_text(encoding="utf-8")
    original = text
    # Longer keys first so Glfw\GFW\Window… wins over bare Glfw\GFW.
    for bad, good in sorted(FIXES.items(), key=lambda item: len(item[0]), reverse=True):
        text = text.replace(bad, good)
    text = re.sub(
        r"\bGlfw_GFW_(Window_GLFWWindow|Monitor_GLFWMonitor|Input_GLFWInput|"
        r"Context_GLFWContext|Vulkan_GLFWVulkan|GL_GLFWGL|GLFWError|GLFW)\b",
        r"Glfw_GLFW_\1",
        text,
    )
    text = re.sub(r"\bGlfw_GLFW_G_GLFWGL\b", "Glfw_GLFW_GL_GLFWGL", text)
    if text != original:
        path.write_text(text, encoding="utf-8")
        return 1
    return 0


def main() -> None:
    if not EXT.exists():
        raise SystemExit("ext/ missing — run zephir generate first")
    changed = 0
    for path in EXT.rglob("*.c"):
        changed += fix_file(path)
    for path in EXT.rglob("*.h"):
        changed += fix_file(path)
    print(f"fixup-zephir-register: touched {changed} files")


if __name__ == "__main__":
    main()

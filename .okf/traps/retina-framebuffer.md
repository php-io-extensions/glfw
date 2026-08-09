---
type: Trap
title: Retina framebuffer vs window size
description: On HiDPI, glViewport needs framebuffer pixels from glfwGetFramebufferSize
tags: [glfw, trap, retina, viewport, opengl]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T17:35:00Z }
sources:
  - id: window-zep
    resource: /glfw/glfw/window/glfwwindow.zep
    title: glfwwindow.zep
  - id: demo
    resource: /examples/proof_window.php
    title: proof_window.php
---

# Symptom

Scene draws in a corner or looks blurry on Mac Retina (and other HiDPI) while `glfwGetWindowSize` looks “correct.”

# Cause

GLFW window size is often in **screen coordinates (points)**. The OpenGL framebuffer is in **pixels**, commonly 2× on Retina. `glViewport` / scissor must use framebuffer dimensions from `GLFWWindow::glfwGetFramebufferSize`.[^window-zep]

# Guidance

1. After create / on resize, query framebuffer size (not only window size).
2. Set `GLFWGL::glViewport(0, 0, $fbW, $fbH)` (or the open-gl equivalent).
3. Register `glfwSetFramebufferSizeCallback` when the window is resizable.
4. Do not hard-code window points as pixel sizes.

Same trap is documented on the open-gl and microscrap/glfw sides for the paired draw path.

[^window-zep]: glfwwindow.zep
[^demo]: proof_window.php

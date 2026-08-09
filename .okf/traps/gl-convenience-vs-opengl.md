---
type: Trap
title: GLFWGL vs open-gl
description: Keep the 8-method GLFWGL slice; full gl* belongs in php-io-extensions/open-gl
resource: /glfw/glfw/gl/glfwgl.zep
tags: [glfw, trap, opengl, boundaries]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: 2026-08-09T17:35:00Z }
sources:
  - id: glfwgl
    resource: /glfw/glfw/gl/glfwgl.zep
    title: glfwgl.zep
  - id: readme
    resource: /README.md
    title: README
  - id: demo
    resource: /examples/proof_window.php
    title: proof_window.php
---

# Trap

`Glfw\GLFW\GL\GLFWGL` exists so demos can clear/scissor without loading open-gl.[^glfwgl][^demo] Agents sometimes grow shaders/buffers/textures into this class because “GL is already linked.”

# Rule

- **This package:** window / input / context / Vulkan + the 8 convenience `gl*` methods only.
- **open-gl package:** full draw/state API and `Gl*` DTOs.
- Do not `composer require` open-gl from this extension; compose at the app/example layer.

README already positions GLFW as ScrapyardIO windowed output alongside sdl3 — not as the GL API home.[^readme]

[^glfwgl]: glfwgl.zep
[^readme]: README
[^demo]: proof_window.php

# Architecture

* [Layered stack](stack.md) - Zephir → GLFW C API → libglfw (+ optional OpenGL for GLFWGL)
* [Zephir inline C](zephir-inline-c.md) - `%{ … %}` bridges, callbacks, opaque ints
* [Linking GLFW + GL](linking-glfw.md) - pkg-config glfw3, Darwin OpenGL.framework / Linux -lGL

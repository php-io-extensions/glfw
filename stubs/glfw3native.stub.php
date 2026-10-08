<?php

/** @generate-class-entries */

/* Native handles as addresses or ids, for another extension to adopt (NSWindow::fromPointer(), ...). */

#ifdef __APPLE__
/** The window's NSWindow address. */
function glfwGetCocoaWindow(GLFWwindow $window): int {}

/** The window's content NSView address. */
function glfwGetCocoaView(GLFWwindow $window): int {}

/** The monitor's CGDirectDisplayID. */
function glfwGetCocoaMonitor(GLFWmonitor $monitor): int {}

/** The window's NSOpenGLContext address, 0 when it has none. */
function glfwGetNSGLContext(GLFWwindow $window): int {}
#endif

#ifdef __linux__
function glfwGetX11Display(): int {}

function glfwGetX11Window(GLFWwindow $window): int {}

function glfwGetX11Adapter(GLFWmonitor $monitor): int {}

function glfwGetX11Monitor(GLFWmonitor $monitor): int {}

function glfwGetWaylandDisplay(): int {}

function glfwGetWaylandWindow(GLFWwindow $window): int {}

function glfwGetWaylandMonitor(GLFWmonitor $monitor): int {}

function glfwGetGLXContext(GLFWwindow $window): int {}

function glfwGetGLXWindow(GLFWwindow $window): int {}

function glfwGetEGLDisplay(): int {}

function glfwGetEGLContext(GLFWwindow $window): int {}

function glfwGetEGLSurface(GLFWwindow $window): int {}
#endif

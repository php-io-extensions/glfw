<?php

declare(strict_types=1);

beforeEach(fn () => glfw());

it('hands over the Cocoa window, view, display and GL context', function (): void {
    if (PHP_OS_FAMILY !== 'Darwin') {
        $this->markTestSkipped('Cocoa only');
    }
    $plain = hiddenWindow();
    $gl = glWindow();

    expect(glfwGetCocoaWindow($plain))->toBeGreaterThan(0)
        ->and(glfwGetCocoaView($plain))->toBeGreaterThan(0)
        ->and(glfwGetNSGLContext($plain))->toBe(0)
        ->and(glfwGetNSGLContext($gl))->toBeGreaterThan(0)
        ->and(glfwGetCocoaMonitor(glfwGetPrimaryMonitor()))->toBeGreaterThan(0);

    if (extension_loaded('appkit')) {
        $window = NSWindow::fromPointer(glfwGetCocoaWindow($plain));
        expect($window->contentView()->pointer())->toBe(glfwGetCocoaView($plain))
            ->and(glfwGetCocoaMonitor(glfwGetPrimaryMonitor()))->toBe(CGDisplay::mainDisplayID());
        glfwMakeContextCurrent($gl);
        expect(NSOpenGLContext::currentContext()?->pointer())->toBe(glfwGetNSGLContext($gl));
        glfwMakeContextCurrent(null);
    }

    glfwDestroyWindow($gl);
    glfwDestroyWindow($plain);
});

it('hands over the X11 or Wayland handles of the platform it runs', function (): void {
    if (PHP_OS_FAMILY !== 'Linux') {
        $this->markTestSkipped('Linux only');
    }
    $window = hiddenWindow();
    $monitor = glfwGetPrimaryMonitor();

    if (glfwGetPlatform() === GLFW_PLATFORM_WAYLAND) {
        expect(glfwGetWaylandDisplay())->toBeGreaterThan(0)
            ->and(glfwGetWaylandWindow($window))->toBeGreaterThan(0)
            ->and(glfwGetWaylandMonitor($monitor))->toBeGreaterThan(0);
    } else {
        expect(glfwGetX11Display())->toBeGreaterThan(0)
            ->and(glfwGetX11Window($window))->toBeGreaterThan(0)
            ->and(glfwGetX11Adapter($monitor))->toBeGreaterThan(0)
            ->and(glfwGetX11Monitor($monitor))->toBeGreaterThan(0);
    }

    glfwDestroyWindow($window);
});

it('hands over the EGL or GLX context a GL window got', function (): void {
    if (PHP_OS_FAMILY !== 'Linux') {
        $this->markTestSkipped('Linux only');
    }
    glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
    $window = hiddenWindow(160, 120, [GLFW_CLIENT_API => GLFW_OPENGL_ES_API, GLFW_CONTEXT_VERSION_MAJOR => 2, GLFW_CONTEXT_CREATION_API => GLFW_EGL_CONTEXT_API]);

    expect(glfwGetEGLDisplay())->toBeGreaterThan(0)
        ->and(glfwGetEGLContext($window))->toBeGreaterThan(0)
        ->and(glfwGetEGLSurface($window))->toBeGreaterThan(0);
    glfwDestroyWindow($window);

    if (glfwGetPlatform() === GLFW_PLATFORM_X11) {
        $glx = hiddenWindow(160, 120, [GLFW_CLIENT_API => GLFW_OPENGL_API, GLFW_CONTEXT_CREATION_API => GLFW_NATIVE_CONTEXT_API]);
        expect(glfwGetGLXContext($glx))->toBeGreaterThan(0)
            ->and(glfwGetGLXWindow($glx))->toBeGreaterThan(0);
        glfwDestroyWindow($glx);
    }
});

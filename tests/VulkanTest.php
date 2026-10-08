<?php

declare(strict_types=1);

beforeEach(function (): void {
    glfw();
    if (! glfwVulkanSupported()) {
        $this->markTestSkipped('no Vulkan loader reached: needs ext-vulkan and FFI to hand GLFW the loader');
    }
});

it('names the instance extensions a surface needs, and finds loader functions', function (): void {
    $extensions = glfwGetRequiredInstanceExtensions();

    expect($extensions)->toContain('VK_KHR_surface')
        ->and(count($extensions))->toBe(2)
        ->and(glfwGetInstanceProcAddress(0, 'vkCreateInstance'))->toBeGreaterThan(0)
        ->and(glfwGetInstanceProcAddress(0, 'vkNoSuchFunction'))->toBe(0);
});

it('makes a Vulkan surface on a window, which the device can present to', function (): void {
    if (! function_exists('vkCreateInstance')) {
        $this->markTestSkipped('needs ext-vulkan for an instance');
    }
    $info = new VkInstanceCreateInfo();
    $info->enabledExtensionNames = [...glfwGetRequiredInstanceExtensions(), ...(PHP_OS_FAMILY === 'Darwin' ? ['VK_KHR_portability_enumeration'] : [])];
    $info->flags = PHP_OS_FAMILY === 'Darwin' ? VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR : 0;
    expect(vkCreateInstance($info, null, $instance))->toBe(VK_SUCCESS);
    vkEnumeratePhysicalDevices($instance, $devices);
    $window = hiddenWindow(160, 120);

    $result = glfwCreateWindowSurface($instance->pointer(), $window, 0, $surface);

    expect($result)->toBe(VK_SUCCESS)
        ->and($surface)->toBeGreaterThan(0)
        ->and(glfwGetPhysicalDevicePresentationSupport($instance->pointer(), $devices[0]->pointer(), 0))->toBeTrue();

    vkDestroySurfaceKHR($instance, VkSurfaceKHR::fromPointer($surface), null);
    glfwDestroyWindow($window);
    vkDestroyInstance($instance, null);
});

it('refuses a null instance', function (): void {
    $window = hiddenWindow();

    expect(fn () => glfwCreateWindowSurface(0, $window, 0, $surface))->toThrow(ValueError::class, 'must be a VkInstance, not 0');

    glfwDestroyWindow($window);
});

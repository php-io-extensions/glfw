<?php

declare(strict_types=1);

require_once __DIR__ . '/../scripts/support.php';

it('counts the GLFWAPI functions of each header, sorted, once each', function (): void {
    $header = "GLFWAPI int glfwInit(void);\nGLFWAPI const char* glfwGetVersionString(void);\n"
        . "GLFWAPI GLFWwindow* glfwCreateWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);\n"
        . "GLFWAPI int glfwInit(void);\ntypedef void (* GLFWerrorfun)(int error_code, const char* description);\n";

    expect(support_counted(['glfw3.h' => $header, 'empty.h' => "#define X 1\n"]))
        ->toBe(['glfw3.h' => ['glfwCreateWindow', 'glfwGetVersionString', 'glfwInit']]);
});

it('reads the top-level functions of a stub, not class methods', function (): void {
    $stub = "<?php\nfunction glfwInit(): bool {}\nfinal class GLFWmonitor { public function pointer(): int {} }\nfunction glfwTerminate(): void {}\n";

    expect(support_functions($stub))->toBe(['glfwInit', 'glfwTerminate']);
});

it('renders one line per function and lists the bindings that match none', function (): void {
    $md = support_render(['glfw3.h' => ['glfwInit', 'glfwTerminate']], ['glfwInit' => true, 'glfw_helper' => true], 'GLFW 3.4', '2026-10-28');

    expect($md)->toContain('- [x] `glfwInit`')
        ->toContain('- [ ] `glfwTerminate`')
        ->toContain('## glfw3.h (1 / 2)')
        ->toContain('GLFW 3.4 — 1 / 2 members bound (50.0%) — 2026-10-28')
        ->toContain('- `glfw_helper`');
});

it('computes the badge from the counts', function (): void {
    expect(support_badge('GLFW API', 99, 149))
        ->toBe('[![GLFW API](https://img.shields.io/badge/GLFW_API-66.4%25_%2899%2F149%29-blue?style=flat-square)](SUPPORT.md)');
});

it('compares a support list without its date', function (): void {
    expect(support_same("GLFW 3.4 — 2 / 4 members bound (50.0%) — 2026-10-28\n", "GLFW 3.4 — 2 / 4 members bound (50.0%) — 2026-11-01\n"))->toBeTrue()
        ->and(support_same("GLFW 3.4 — 2 / 4 members bound (50.0%) — 2026-10-28\n", "GLFW 3.4 — 3 / 4 members bound (75.0%) — 2026-10-28\n"))->toBeFalse();
});

it('sets the badge after the CI badge, then in place', function (): void {
    $readme = "# glfw\n\n[![CI](x)](y)\n\ntext\n";
    $once = support_readme($readme, '[![GLFW API](a)](SUPPORT.md)');

    expect($once)->toBe("# glfw\n\n[![CI](x)](y)\n[![GLFW API](a)](SUPPORT.md)\n\ntext\n")
        ->and(support_readme($once, '[![GLFW API](b)](SUPPORT.md)'))->toBe("# glfw\n\n[![CI](x)](y)\n[![GLFW API](b)](SUPPORT.md)\n\ntext\n");
});

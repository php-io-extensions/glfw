# Security Policy

## Supported versions

ext-glfw is pre-1.0. No 0.x release receives security fixes or advisories; fixes land in the
next release line. Security support starts with 1.0.

| Version | Security fixes |
|---------|----------------|
| < 1.0   | No             |

## Reporting a vulnerability

Please don't open a public issue for a security problem.

Report it privately through GitHub: the **Report a vulnerability** button on the
[php-io-extensions/glfw](https://github.com/php-io-extensions/glfw) repository's **Security** tab.
If that isn't available, email **info@projectsaturnstudios.com**.

Include what you found, the affected version, your platform and windowing system (Cocoa, X11
or Wayland), PHP build (NTS or ZTS) and the GLFW version (`php --ri glfw` shows it), and steps to
reproduce. Reports are read and weighed for the release line in development; before 1.0 there is
no response-time commitment.

A defect in GLFW itself belongs with that project. Report it here as well when ext-glfw should
guard against it.

## Security model

ext-glfw opens windows and talks to the display server on behalf of the PHP process. It reads no
files and makes no network requests.

- **Inputs.** Ints GLFW takes as C `int` are refused past 32 bits. A gamma ramp must hold three
  lists of one length with values 0 to 65535. An icon's pixel string must be exactly
  4 × width × height bytes, at most 4096 pixels a side, before GLFW reads it.
- **Addresses.** `fromPointer()`, Vulkan handles, `glfwInitVulkanLoader()` and the allocator
  argument of `glfwCreateWindowSurface()` take addresses as ints and trust them: an address
  from another extension is passed through as given. 0 is refused where GLFW requires a handle.
- **Handles.** A destroyed window or a disconnected monitor throws `ValueError` instead of
  reaching GLFW with a freed pointer.
- **Callbacks.** PHP callables are held by the extension and released at request end, after
  GLFW is told to stop calling them.

A report is in scope when ext-glfw itself reads or writes memory it should not, leaks, or crashes:
a list copied past its length, a handle used after GLFW freed it, a callback reached after its
callable was released.

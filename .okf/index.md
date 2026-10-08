---
okf_version: "0.2"
---

# ext-glfw

1:1 PHP bindings of GLFW 3.4 for staged windows, input excluded. Version 0.10.0. Linux and macOS.

# API

* [Bindings](api/bindings.md) — Functions, handles, value classes and constants by group.

# Architecture

* [Handles and callbacks](architecture/handles-and-callbacks.md) — Identity table, release rules, callback storage and request end.
* [Platform facts](architecture/platforms.md) — What Wayland and Cocoa leave out, as GLFW reports it; the libdecor/GTK 4 deadlock.

# Runbooks

* [Build, install, test](runbooks/build.md) — Mac NTS/ZTS and the Pi under Wayland.
* [Adding a binding](runbooks/adding-a-binding.md) — Stub, gen_stub, the C file that registers it, the surface test.

#!/bin/bash

# macOS installer for the GLFW Zephir extension — Laravel Herd edition.
#
# Targets Herd's PHP binary and drops the .so + .ini into Herd's per-version
# config directory (e.g. ~/Library/Application Support/Herd/config/php/84/).
#
# Herd does not ship php-config/phpize; the Zephir build step uses Homebrew's
# php-config/phpize. Both must be the same major.minor as the Herd PHP runtime.
#
# Usage:
#   bash install-macos-herd.sh
#
# Overrides:
#   PHP_BIN          — Herd php binary (default: $HERD_BIN/php)
#   HERD_BIN         — Herd bin directory
#   HERD_CONFIG_DIR  — Herd PHP config dir (default: .../config/php/<ver>)
#   ZEPHIR_BIN       — path to zephir executable
#   PHP_CONFIG       — php-config used for the Zephir build
#   PHP_PHPIZE       — phpize used for the Zephir build

set -Eeuo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
EXTENSION_NAME="glfw"
BUILD_SO="${SCRIPT_DIR}/ext/modules/${EXTENSION_NAME}.so"
LOG_FILE="${SCRIPT_DIR}/build.log"

HERD_HOME="${HERD_HOME:-${HOME}/Library/Application Support/Herd}"
HERD_BIN="${HERD_BIN:-${HERD_HOME}/bin}"

if [ "${EUID:-$(id -u)}" -ne 0 ]; then
    SUDO="sudo"
else
    SUDO=""
fi

die() {
    echo ""
    echo "❌ $*"
    exit 1
}

require_cmd() {
    local cmd="$1"
    command -v "$cmd" >/dev/null 2>&1 || die "Required command not found: $cmd"
}

header() {
    echo "=========================================="
    echo "GLFW Extension Installer (macOS / Herd)"
    echo "=========================================="
    echo ""
}

step() {
    echo "$*"
}

ok() {
    echo "   ✓ $*"
}

show_failure_logs() {
    if [ -f "$LOG_FILE" ]; then
        echo ""
        echo "---- Errors in ${LOG_FILE} ----"
        grep -i "error:" "$LOG_FILE" | grep -v "warning:" | grep -v "note:" || true
        echo ""
        echo "---- Last 80 lines of ${LOG_FILE} ----"
        tail -80 "$LOG_FILE" || true
    fi
    if [ -f "${SCRIPT_DIR}/compile-errors.log" ]; then
        echo ""
        echo "---- Last 120 lines of compile-errors.log ----"
        tail -120 "${SCRIPT_DIR}/compile-errors.log" || true
    fi
}

ensure_glfw_macos() {
    step "📚 Checking GLFW dependency..."

    if ! command -v brew >/dev/null 2>&1; then
        die "Homebrew is required on macOS to install GLFW. Install Homebrew first: https://brew.sh/"
    fi

    if ! command -v pkg-config >/dev/null 2>&1; then
        step "Installing pkg-config via Homebrew..."
        brew install pkg-config || die "Failed to install pkg-config."
    fi

    if [ -d "/opt/homebrew/lib/pkgconfig" ]; then
        export PKG_CONFIG_PATH="/opt/homebrew/lib/pkgconfig:${PKG_CONFIG_PATH:-}"
    fi
    if [ -d "/usr/local/lib/pkgconfig" ]; then
        export PKG_CONFIG_PATH="/usr/local/lib/pkgconfig:${PKG_CONFIG_PATH:-}"
    fi

    if pkg-config --exists glfw3; then
        ok "GLFW detected via pkg-config"
        return
    fi

    step "GLFW not found. Installing via Homebrew..."
    brew install glfw || die "Failed to install GLFW via Homebrew."

    if ! pkg-config --exists glfw3; then
        die "GLFW still not detected by pkg-config after install."
    fi

    ok "GLFW installed and detected"
}

ensure_opengl_macos() {
    step "🖼️  Verifying OpenGL runtime (macOS framework)..."

    if [ -d "/System/Library/Frameworks/OpenGL.framework" ]; then
        ok "OpenGL.framework found"
        return
    fi

    if [ -n "${SDKROOT:-}" ] && [ -d "${SDKROOT}/System/Library/Frameworks/OpenGL.framework" ]; then
        ok "OpenGL.framework found in SDKROOT"
        return
    fi

    die "OpenGL.framework was not found."
}

resolve_herd_php() {
    if [ -n "${PHP_BIN:-}" ]; then
        [ -x "$PHP_BIN" ] || die "PHP_BIN is not executable: $PHP_BIN"
        return
    fi

    if [ -x "${HERD_BIN}/php" ]; then
        PHP_BIN="${HERD_BIN}/php"
        return
    fi

    die "Herd PHP not found. Expected ${HERD_BIN}/php or set PHP_BIN."
}

resolve_build_toolchain() {
    step "🔧 Resolving PHP build toolchain (php-config / phpize)..."

    PHP_CONFIG="${PHP_CONFIG:-}"
    PHP_PHPIZE="${PHP_PHPIZE:-}"

    if [ -z "$PHP_CONFIG" ] || [ ! -x "$PHP_CONFIG" ]; then
        PHP_CONFIG="$(command -v php-config 2>/dev/null || true)"
    fi
    if [ -z "$PHP_PHPIZE" ] || [ ! -x "$PHP_PHPIZE" ]; then
        PHP_PHPIZE="$(command -v phpize 2>/dev/null || true)"
    fi

    [ -n "$PHP_CONFIG" ] && [ -x "$PHP_CONFIG" ] || die "php-config not found. Install Homebrew PHP dev headers: brew install php"
    [ -n "$PHP_PHPIZE" ] && [ -x "$PHP_PHPIZE" ] || die "phpize not found. Install Homebrew PHP dev headers: brew install php"

    local herd_ver build_ver herd_ext_suffix build_ext_suffix
    herd_ver="$("$PHP_BIN" -r 'echo PHP_MAJOR_VERSION.".".PHP_MINOR_VERSION;')"
    build_ver="$("$PHP_CONFIG" --version 2>/dev/null | awk '{print $NF}' | cut -d. -f1,2)"
    herd_ext_suffix="$(basename "$("$PHP_BIN" -r 'echo ini_get("extension_dir");')")"
    build_ext_suffix="$(basename "$("$PHP_CONFIG" --extension-dir)")"
    herd_api="${herd_ext_suffix##*-}"
    build_api="${build_ext_suffix##*-}"

    ok "Herd PHP       : $("$PHP_BIN" -r 'echo PHP_VERSION;') ($PHP_BIN)"
    ok "Build php-config: $($PHP_CONFIG --version 2>/dev/null | head -1)"
    ok "Build phpize    : $PHP_PHPIZE"

    if [ "$herd_ver" != "$build_ver" ]; then
        die "Herd PHP ${herd_ver} does not match php-config ${build_ver}. Install matching Homebrew PHP or set PHP_CONFIG."
    fi

    if [ "$herd_api" != "$build_api" ]; then
        die "Extension API suffix mismatch: Herd=${herd_api}, php-config=${build_api}."
    fi
}

header

step "🔎 Preflight checks..."
resolve_herd_php

if [ -n "${ZEPHIR_BIN:-}" ]; then
    ZEPHIR="$ZEPHIR_BIN"
elif command -v zephir >/dev/null 2>&1; then
    ZEPHIR="$(command -v zephir)"
elif [ -x "${HOME}/.composer/vendor/bin/zephir" ]; then
    ZEPHIR="${HOME}/.composer/vendor/bin/zephir"
elif [ -x "${HOME}/.config/composer/vendor/bin/zephir" ]; then
    ZEPHIR="${HOME}/.config/composer/vendor/bin/zephir"
else
    die "Zephir not found. composer global require phalcon/zephir"
fi
ok "Found zephir: $ZEPHIR"

ensure_glfw_macos
ensure_opengl_macos
resolve_build_toolchain

PHP_VER_MM="$("$PHP_BIN" -r 'echo PHP_MAJOR_VERSION.".".PHP_MINOR_VERSION;')"
PHP_VER_NN="$("$PHP_BIN" -r 'echo PHP_MAJOR_VERSION.PHP_MINOR_VERSION;')"
PHP_BIN_REAL="$("$PHP_BIN" -r 'echo PHP_BINARY;')"

HERD_CONFIG_DIR="${HERD_CONFIG_DIR:-${HERD_HOME}/config/php/${PHP_VER_NN}}"
[ -d "$HERD_CONFIG_DIR" ] || die "Herd config directory not found: ${HERD_CONFIG_DIR}"

# Herd keeps extension binaries alongside drop-in ini files in the versioned config dir.
PHP_EXT_DIR="$HERD_CONFIG_DIR"
CLI_SCAN_DIR="$HERD_CONFIG_DIR"

ok "Herd config dir : ${HERD_CONFIG_DIR}"
ok "Extension target: ${PHP_EXT_DIR}/${EXTENSION_NAME}.so"
echo ""

export CFLAGS="-Wno-error -Wno-error=incompatible-pointer-types -Wno-pointer-compare"
export CPPFLAGS="${CPPFLAGS:-} -Wno-error -Wno-error=incompatible-pointer-types"
export PATH="$(dirname "$PHP_CONFIG"):${PATH}"

step "🧹 Cleaning previous build..."
cd "${SCRIPT_DIR}"
if ! php -d memory_limit=2G "$ZEPHIR" fullclean >"$LOG_FILE" 2>&1; then
    tail -50 "$LOG_FILE" || true
    die "Clean failed. See ${LOG_FILE}."
fi
ok "Clean complete"
echo ""

step "🔨 Building extension (Zephir + Homebrew phpize)..."
if ! php -d memory_limit=2G "$ZEPHIR" generate >>"$LOG_FILE" 2>&1; then
    show_failure_logs
    die "Generate failed. See ${LOG_FILE}."
fi
if ! python3 "${SCRIPT_DIR}/scripts/fixup-zephir-register.py" >>"$LOG_FILE" 2>&1; then
    show_failure_logs
    die "Zephir REGISTER fixup failed. See ${LOG_FILE}."
fi
if ! php -d memory_limit=2G "$ZEPHIR" compile >>"$LOG_FILE" 2>&1; then
    show_failure_logs
    die "Build failed. See ${LOG_FILE}."
fi
if [ ! -f "$BUILD_SO" ]; then
    show_failure_logs
    die "Build output not found at ${BUILD_SO}."
fi
ok "Build complete"
echo ""

step "📦 Installing binary into Herd config..."
mkdir -p "$PHP_EXT_DIR"
cp -f "$BUILD_SO" "${PHP_EXT_DIR}/${EXTENSION_NAME}.so"
chmod 755 "${PHP_EXT_DIR}/${EXTENSION_NAME}.so"
ok "Copied to: ${PHP_EXT_DIR}/${EXTENSION_NAME}.so"
echo ""

step "⚙️  Enabling extension for Herd PHP ${PHP_VER_MM}..."
INI_NAME="30-${EXTENSION_NAME}.ini"
INI_PATH="${HERD_CONFIG_DIR}/${INI_NAME}"
INI_CONTENT="extension=${PHP_EXT_DIR}/${EXTENSION_NAME}.so"

echo "$INI_CONTENT" | $SUDO tee "$INI_PATH" >/dev/null
ok "Written: ${INI_PATH}"
echo ""

step "🔍 Verifying installation (Herd CLI)..."
VERIFY_ERRORS="$("$PHP_BIN" -m 2>&1 >/dev/null || true)"
extension_loaded=false
for _attempt in 1 2; do
    if "$PHP_BIN" -m 2>/dev/null | grep -q "^${EXTENSION_NAME}$"; then
        extension_loaded=true
        break
    fi
    sleep 1
done

if $extension_loaded; then
    ok "Extension loaded successfully"
    [ -n "$VERIFY_ERRORS" ] && echo "   ⚠️  PHP startup warnings: $VERIFY_ERRORS"
else
    echo ""
    echo "   PHP binary used: $PHP_BIN"
    echo "   PHP_BINARY:      $PHP_BIN_REAL"
    echo "   Extension dir:   $PHP_EXT_DIR"
    echo "   INI path:        $INI_PATH"
    [ -n "$VERIFY_ERRORS" ] && echo "   PHP stderr: $VERIFY_ERRORS"
    die "Extension not detected. Check ${INI_PATH} and run: $PHP_BIN --ini"
fi
echo ""

step "=========================================="
step "Extension Information (Herd CLI)"
step "=========================================="
"$PHP_BIN" --ri "${EXTENSION_NAME}" || true
echo ""

echo "✅ Herd installation complete!"
echo ""
echo "File locations:"
echo "  • Binary: ${PHP_EXT_DIR}/${EXTENSION_NAME}.so"
echo "  • Config: ${INI_PATH}"
echo "  • PHP:    ${PHP_BIN}"
echo ""

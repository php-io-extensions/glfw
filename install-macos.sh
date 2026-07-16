#!/bin/bash

# macOS installer for the GLFW Zephir extension.
# - Detects and installs GLFW via Homebrew if missing
# - Detects php extension dir dynamically
# - Enables extension for available SAPIs
# - Finds zephir automatically or respects $ZEPHIR_BIN

set -Eeuo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
EXTENSION_NAME="glfw"
BUILD_SO="${SCRIPT_DIR}/ext/modules/${EXTENSION_NAME}.so"
LOG_FILE="${SCRIPT_DIR}/build.log"

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
    echo "GLFW Extension Installer (macOS)"
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

    # Ensure pkg-config can see Homebrew-installed libs on both Intel and Apple Silicon.
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
        die "GLFW still not detected by pkg-config after install. Check PKG_CONFIG_PATH and your Homebrew prefix."
    fi

    ok "GLFW installed and detected"
}

ensure_opengl_macos() {
    step "🖼️  Verifying OpenGL runtime (macOS framework)..."

    if [ -d "/System/Library/Frameworks/OpenGL.framework" ]; then
        ok "OpenGL.framework found at /System/Library/Frameworks/OpenGL.framework"
        return
    fi

    if [ -n "${SDKROOT:-}" ] && [ -d "${SDKROOT}/System/Library/Frameworks/OpenGL.framework" ]; then
        ok "OpenGL.framework found in SDKROOT"
        return
    fi

    die "OpenGL.framework was not found. This runtime is expected to be built into macOS."
}

header

# Preflight
step "🔎 Preflight checks..."
require_cmd php
require_cmd php-config

# Resolve Zephir
if [ -n "${ZEPHIR_BIN:-}" ]; then
    ZEPHIR="$ZEPHIR_BIN"
elif command -v zephir >/dev/null 2>&1; then
    ZEPHIR="$(command -v zephir)"
elif [ -x "$HOME/.config/composer/vendor/bin/zephir" ]; then
    ZEPHIR="$HOME/.config/composer/vendor/bin/zephir"
else
    die "Zephir not found. Install via composer (composer global require phalcon/zephir) or set ZEPHIR_BIN."
fi
ok "Found zephir: $ZEPHIR"

ensure_glfw_macos
ensure_opengl_macos

PHP_VER_MM="$(php -r 'echo PHP_MAJOR_VERSION.".".PHP_MINOR_VERSION;')"
PHP_VER_NN="$(php -r 'echo PHP_MAJOR_VERSION.PHP_MINOR_VERSION;')"

PHP_BIN_REAL="$(php -r 'echo PHP_BINARY;' 2>/dev/null)"
PHP_BIN_DIR="$(dirname "$PHP_BIN_REAL")"
RESOLVED_PHP_CONFIG="${PHP_BIN_DIR}/php-config"

if [ -x "$RESOLVED_PHP_CONFIG" ]; then
    PHP_EXT_DIR="$("$RESOLVED_PHP_CONFIG" --extension-dir)"
elif command -v php-config >/dev/null 2>&1; then
    PHP_EXT_DIR="$(php-config --extension-dir)"
else
    die "Could not locate php-config. Install it or set PHP_EXT_DIR manually."
fi
[ -n "$PHP_EXT_DIR" ] || die "Could not determine PHP extension dir."

CLI_SCAN_DIR="$(php --ini 2>/dev/null | awk -F': ' '/Scan for additional \.ini files in:/{print $2}' || true)"
if [ -n "$CLI_SCAN_DIR" ] && [ -d "$CLI_SCAN_DIR" ] && ls "$CLI_SCAN_DIR"/*.so >/dev/null 2>&1; then
    PHP_EXT_DIR="$CLI_SCAN_DIR"
fi

ok "PHP version: ${PHP_VER_MM}"
ok "PHP binary: ${PHP_BIN_REAL}"
ok "Extension dir: ${PHP_EXT_DIR}"

# Set safe CFLAGS for stricter compilers
export CFLAGS="-Wno-error -Wno-error=incompatible-pointer-types -Wno-pointer-compare"
export CPPFLAGS="${CPPFLAGS:-} -Wno-error -Wno-error=incompatible-pointer-types"
echo ""

# Clean previous build
step "🧹 Cleaning previous build..."
cd "${SCRIPT_DIR}"
if ! "$ZEPHIR" fullclean >"$LOG_FILE" 2>&1; then
    tail -50 "$LOG_FILE" || true
    die "Clean failed. See ${LOG_FILE}."
fi
ok "Clean complete"
echo ""

# Build
step "🔨 Building extension..."
if ! "$ZEPHIR" generate >>"$LOG_FILE" 2>&1; then
    show_failure_logs
    die "Generate failed. See ${LOG_FILE}."
fi
if ! python3 "${SCRIPT_DIR}/scripts/fixup-zephir-register.py" >>"$LOG_FILE" 2>&1; then
    show_failure_logs
    die "Zephir REGISTER fixup failed. See ${LOG_FILE}."
fi
if ! "$ZEPHIR" compile >>"$LOG_FILE" 2>&1; then
    show_failure_logs
    die "Build failed. See ${LOG_FILE}."
fi
if [ ! -f "$BUILD_SO" ]; then
    show_failure_logs
    die "Build output not found at ${BUILD_SO}."
fi
ok "Build complete"
echo ""

# Install .so
step "📦 Installing binary..."
$SUDO mkdir -p "$PHP_EXT_DIR"
$SUDO cp -f "$BUILD_SO" "${PHP_EXT_DIR}/${EXTENSION_NAME}.so"
$SUDO chmod 755 "${PHP_EXT_DIR}/${EXTENSION_NAME}.so"
ok "Copied to: ${PHP_EXT_DIR}/${EXTENSION_NAME}.so"
echo ""

# Enable extension across detected SAPIs
step "⚙️  Enabling extension..."
declare -a CONF_DIR_CANDIDATES=()

if [ -n "$CLI_SCAN_DIR" ] && [ "$CLI_SCAN_DIR" != "(none)" ] && [ -d "$CLI_SCAN_DIR" ]; then
    CONF_DIR_CANDIDATES+=("$CLI_SCAN_DIR")
fi

for d in "/etc/php/${PHP_VER_MM}/cli/conf.d" "/etc/php/${PHP_VER_MM}/fpm/conf.d" "/etc/php/${PHP_VER_MM}/apache2/conf.d"; do
    [ -d "$d" ] && CONF_DIR_CANDIDATES+=("$d")
done

ALPINE_CONF="/etc/php${PHP_VER_NN}/conf.d"
[ -d "$ALPINE_CONF" ] && CONF_DIR_CANDIDATES+=("$ALPINE_CONF")

for d in "/etc/php-fpm.d" "/etc/php-fpm/conf.d"; do
    [ -d "$d" ] && CONF_DIR_CANDIDATES+=("$d")
done

CONF_DIRS=()
while IFS= read -r _line; do
    CONF_DIRS+=("$_line")
done < <(printf "%s\n" "${CONF_DIR_CANDIDATES[@]}" | awk '!seen[$0]++')

if [ "${#CONF_DIRS[@]}" -eq 0 ]; then
    echo "   ⚠️  No conf.d directories found; enabling only for current CLI context via php.d scan dir."
fi

INI_NAME="30-${EXTENSION_NAME}.ini"
INI_CONTENT="extension=${PHP_EXT_DIR}/${EXTENSION_NAME}.so"

for confd in "${CONF_DIRS[@]:-}"; do
    INI_PATH="${confd}/${INI_NAME}"
    echo "$INI_CONTENT" | $SUDO tee "$INI_PATH" >/dev/null
    ok "Written: $INI_PATH"
done
echo ""

# Verify CLI load
step "🔍 Verifying installation (CLI)..."
VERIFY_ERRORS="$("$PHP_BIN_REAL" -m 2>&1 >/dev/null || true)"
if "$PHP_BIN_REAL" -m 2>/dev/null | grep -q "^${EXTENSION_NAME}$"; then
    ok "Extension loaded successfully in CLI"
    [ -n "$VERIFY_ERRORS" ] && echo "   ⚠️  PHP startup warnings: $VERIFY_ERRORS"
else
    echo ""
    echo "   PHP binary used: $PHP_BIN_REAL"
    echo "   Extension dir:   $PHP_EXT_DIR"
    echo "   INI written to:  ${CLI_SCAN_DIR:-unknown}/${INI_NAME}"
    [ -n "$VERIFY_ERRORS" ] && echo "   PHP stderr: $VERIFY_ERRORS"
    die "Extension not detected in CLI. Check ${INI_NAME} placement and php --ini."
fi
echo ""

# Show module info
step "=========================================="
step "Extension Information (CLI)"
step "=========================================="
"$PHP_BIN_REAL" --ri glfw || true
echo ""

echo "✅ Installation complete!"
echo ""
echo "File locations:"
echo "  • Binary: ${PHP_EXT_DIR}/${EXTENSION_NAME}.so"
if [ "${#CONF_DIRS[@]}" -gt 0 ]; then
    for d in "${CONF_DIRS[@]}"; do
        echo "  • Config: ${d}/${INI_NAME}"
    done
else
    echo "  • Config: (CLI scan dir via php --ini)"
fi
echo ""

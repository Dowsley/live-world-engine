set dotenv-load := true

# vcpkg toolchain location (override by exporting VCPKG_ROOT)
export VCPKG_ROOT := env_var_or_default("VCPKG_ROOT", "/opt/vcpkg")

default: run

# Configure the build (Debug). First run downloads + builds SDL2 via vcpkg.
configure:
    cmake --preset default

# Configure for Release.
configure-release:
    cmake --preset release

# Compile (Debug). Auto-configures if needed.
build: _ensure-configured
    cmake --build build

# Compile (Release).
build-release:
    cmake --preset release
    cmake --build build

# Build then launch the game.
run: build
    cd build && ./live_world_engine

# Wipe the build directory.
clean:
    rm -rf build

# Wipe build + vcpkg's downloaded port cache for this project.
distclean: clean
    rm -rf vcpkg_installed

# Print resolved tool versions.
doctor:
    @echo "VCPKG_ROOT = $VCPKG_ROOT"
    @cmake --version | head -1
    @command -v ninja >/dev/null && ninja --version || echo "ninja: not installed (using default generator)"

_ensure-configured:
    @test -f build/CMakeCache.txt || cmake --preset default

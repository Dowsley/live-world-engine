# Live World Engine

Self-contained voxel engine with heavy emphasis on ecosystems and simulations.

Alive, breathing, and heavily inspired in Dwarf-Fortress. I'm building this as a tool for personal worldbuilding.

## Building

The project uses **SDL2** (rendering, input), **SDL2_image** (PNG loading) and **SDL2_ttf** (debug text), all pulled in via [vcpkg](https://github.com/microsoft/vcpkg) manifest mode. CMake is the build system. Same flow on macOS, Linux, and Windows.

### Prerequisites

- CMake ≥ 3.21
- A C++17 compiler (Apple Clang, GCC, or MSVC)
- vcpkg checked out somewhere, with `VCPKG_ROOT` exported

```sh
git clone https://github.com/microsoft/vcpkg ~/vcpkg
~/vcpkg/bootstrap-vcpkg.sh   # or .bat on Windows
export VCPKG_ROOT=~/vcpkg
```

### Configure & build

```sh
cmake --preset default
cmake --build build
./build/live_world_engine     # build\Debug\live_world_engine.exe on Windows MSVC
```

For a release build:

```sh
cmake --preset release
cmake --build build
```

## Engine notes

The pixel-drawing layer is a thin SDL2 wrapper at `src/platform/pixel_engine.{h,cpp}` exposing only what the game uses (`Clear`, `Draw`, `DrawString`, `GetKey`, `Sprite`). Debug text uses the first available system monospace font; drop a TTF at `assets/fonts/font.ttf` to override.

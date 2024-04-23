cmake_minimum_required(VERSION 3.28)
project(live_world_engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(X11 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(PNG REQUIRED)
find_package(Threads REQUIRED)

include_directories(
        src
        src/core
        src/core/base
        src/creatures
        src/engine
        src/engine/extensions
        src/engine/utilities
        src/lib
        src/structures
        src/tiles
        src/utils
)

add_executable(live_world_engine
        src/core/pathfinding.cpp
        src/core/settings.cpp
        src/core/world.cpp
        src/creatures/creature.cpp
        src/creatures/manager.cpp
        src/creatures/registry.cpp
        src/lib/noise.cpp
        src/lib/tinyxml2.cpp
        src/structures/color.cpp
        src/structures/vec2.cpp
        src/structures/vec3.cpp
        src/tiles/manager.cpp
        src/tiles/registry.cpp
        src/tiles/tile.cpp
        src/utils/arithmetics.cpp
        src/utils/geometry.cpp
        src/utils/logging.cpp
        src/lwe.cpp
        src/main.cpp
        src/tiles/loader.cpp
        src/creatures/loader.cpp
)

target_link_libraries(live_world_engine
        ${X11_LIBRARIES}
        ${OPENGL_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
        ${PNG_LIBRARY}
)

target_link_libraries(live_world_engine stdc++fs)

file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

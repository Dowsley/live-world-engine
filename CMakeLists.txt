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

add_custom_command(
        TARGET live_world_engine PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove_directory $<TARGET_FILE_DIR:live_world_engine>/assets
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:live_world_engine>/assets
)

add_custom_command(
        TARGET live_world_engine PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove_directory $<TARGET_FILE_DIR:live_world_engine>/data
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:live_world_engine>/data
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

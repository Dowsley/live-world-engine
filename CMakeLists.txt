cmake_minimum_required(VERSION 3.21)
project(live_world_engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(tinyxml2 CONFIG REQUIRED)
find_path(FASTNOISELITE_INCLUDE_DIRS "FastNoiseLite.h" REQUIRED)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(live_world_engine ${SOURCES})

target_include_directories(live_world_engine PRIVATE src ${FASTNOISELITE_INCLUDE_DIRS})

target_link_libraries(live_world_engine PRIVATE
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
        $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
        $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>
        tinyxml2::tinyxml2
)

add_custom_command(
        TARGET live_world_engine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E rm -rf $<TARGET_FILE_DIR:live_world_engine>/assets
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:live_world_engine>/assets
)

add_custom_command(
        TARGET live_world_engine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E rm -rf $<TARGET_FILE_DIR:live_world_engine>/data
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:live_world_engine>/data
)

cmake_minimum_required(VERSION 3.1)
project(hello-bgfx)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/bgfx.cmake)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/glfw)

add_definitions(-DBGFX_EXAMPLE_SHADERS_DIR="${BGFX_DIR}/examples/runtime/shaders")

file(GLOB files *.cpp *.hpp)
add_executable(hello-bgfx ${files})
target_link_libraries(hello-bgfx bgfx dear-imgui glfw)

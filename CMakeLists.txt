cmake_minimum_required(VERSION 3.1)
project(hello-bgfx)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/bgfx.cmake)

file(GLOB files *.cpp *.hpp)
add_executable(hello-bgfx ${files})
target_link_libraries(hello-bgfx bgfx)

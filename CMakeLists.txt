cmake_minimum_required(VERSION 3.1)
project(hello-bgfx)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(HELLO_BGFX_BUILD_SHADERS "" ON)

set(BGFX_AMALGAMATED      OFF CACHE INTERNAL "" FORCE)
set(BGFX_BUILD_EXAMPLES   OFF CACHE INTERNAL "" FORCE)
set(BGFX_CONFIG_DEBUG     OFF CACHE INTERNAL "" FORCE)
set(BGFX_CUSTOM_TARGETS   OFF CACHE INTERNAL "" FORCE)
set(BGFX_INSTALL          OFF CACHE INTERNAL "" FORCE)
set(BGFX_INSTALL_EXAMPLES OFF CACHE INTERNAL "" FORCE)
set(BGFX_USE_DEBUG_SUFFIX OFF CACHE INTERNAL "" FORCE)
set(BGFX_USE_OVR          OFF CACHE INTERNAL "" FORCE)
set(BUILD_SHARED_LIBS     OFF CACHE INTERNAL "" FORCE)
set(BX_AMALGAMATED        OFF CACHE INTERNAL "" FORCE)
if (HELLO_BGFX_BUILD_SHADERS)
  set(BGFX_BUILD_TOOLS ON CACHE INTERNAL "" FORCE)
else()
  set(BGFX_BUILD_TOOLS OFF CACHE INTERNAL "" FORCE)
endif()
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/bgfx.cmake)

# Note: This was necessary to avoid a run-time error on macOS/OpenGL. Without
# this option, the NSOpenGLViewContext's setView method was called from a
# wrong (?) thread during bgfx::init and then the app crashes. This needs to be
# investigated further.
target_compile_definitions(bgfx PUBLIC BGFX_CONFIG_MULTITHREADED=0)

set(GLFW_BUILD_DOCS     OFF CACHE INTERNAL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE INTERNAL "" FORCE)
set(GLFW_INSTALL        OFF CACHE INTERNAL "" FORCE)
set(GLFW_USE_OSMESA     OFF CACHE INTERNAL "" FORCE)
set(GLFW_VULKAN_STATIC  OFF CACHE INTERNAL "" FORCE)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/glfw)

set(GLM_DISABLE_AUTO_DETECTION     OFF CACHE INTERNAL "" FORCE)
set(GLM_QUIET                      ON  CACHE INTERNAL "" FORCE)
set(GLM_TEST_ENABLE                OFF CACHE INTERNAL "" FORCE)
set(GLM_TEST_ENABLE_CXX_11         OFF CACHE INTERNAL "" FORCE)
set(GLM_TEST_ENABLE_CXX_14         OFF CACHE INTERNAL "" FORCE)
set(GLM_TEST_ENABLE_CXX_17         OFF CACHE INTERNAL "" FORCE)
set(GLM_TEST_ENABLE_CXX_20         OFF CACHE INTERNAL "" FORCE)
set(GLM_TEST_ENABLE_CXX_98         OFF CACHE INTERNAL "" FORCE)
set(GLM_TEST_ENABLE_FAST_MATH      OFF CACHE INTERNAL "" FORCE)
set(GLM_TEST_ENABLE_LANG_EXTENSION OFF CACHE INTERNAL "" FORCE)
set(GLM_TEST_ENABLE_SIMD_AVX       OFF CACHE INTERNAL "" FORCE)
set(GLM_TEST_ENABLE_SIMD_AVX2      OFF CACHE INTERNAL "" FORCE)
set(GLM_TEST_ENABLE_SIMD_SSE2      OFF CACHE INTERNAL "" FORCE)
set(GLM_TEST_ENABLE_SIMD_SSE3      OFF CACHE INTERNAL "" FORCE)
set(GLM_TEST_ENABLE_SIMD_SSE4_1    OFF CACHE INTERNAL "" FORCE)
set(GLM_TEST_ENABLE_SIMD_SSE4_2    OFF CACHE INTERNAL "" FORCE)
set(GLM_TEST_ENABLE_SIMD_SSSE3     OFF CACHE INTERNAL "" FORCE)
set(GLM_TEST_FORCE_PURE            OFF CACHE INTERNAL "" FORCE)
set(BUILD_STATIC_LIBS              ON  CACHE INTERNAL "" FORCE)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/glm)

set(glew-cmake_BUILD_MULTI_CONTEXT  OFF CACHE INTERNAL "" FORCE)
set(glew-cmake_BUILD_SHARED         OFF CACHE INTERNAL "" FORCE)
set(glew-cmake_BUILD_SINGLE_CONTEXT ON  CACHE INTERNAL "" FORCE)
set(glew-cmake_BUILD_STATIC         ON  CACHE INTERNAL "" FORCE)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/glew-cmake)

add_definitions(-DHELLO_BGFX_RUNTIME_RESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/runtime")

if (HELLO_BGFX_BUILD_SHADERS)
  add_custom_target(
    build-shaders
    COMMAND $<TARGET_FILE:shaderc> -f ${CMAKE_CURRENT_SOURCE_DIR}/shaders/vs_blinnphong.sc -o ${CMAKE_CURRENT_SOURCE_DIR}/runtime/glsl/vs_blinnphong.bin --type v -i ${BGFX_DIR}/src --varyingdef ${CMAKE_CURRENT_SOURCE_DIR}/shaders/varying_blinnphong.def.sc
    COMMAND $<TARGET_FILE:shaderc> -f ${CMAKE_CURRENT_SOURCE_DIR}/shaders/fs_blinnphong.sc -o ${CMAKE_CURRENT_SOURCE_DIR}/runtime/glsl/fs_blinnphong.bin --type f -i ${BGFX_DIR}/src --varyingdef ${CMAKE_CURRENT_SOURCE_DIR}/shaders/varying_blinnphong.def.sc
  )
endif()

file(GLOB files src/*.cpp src/*.hpp src/primitives/*.cpp src/primitives/*.hpp shaders/*.sc)
add_executable(hello-bgfx ${files})
target_link_libraries(hello-bgfx bgfx glfw glm libglew_static)

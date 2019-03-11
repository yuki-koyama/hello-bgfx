# hello-bgfx

Hello-world project to use [bgfx](https://github.com/bkaradzic/bgfx) with [GLFW](https://github.com/glfw/glfw).

## Build

Use CMake.

## Rebuild Shaders

Enable the CMake option `HELLO_BGFX_BUILD_SHADERS`, and then build the target `build-shaders`. This target builds the tool `shaderc` in bgfx and then builds the shader sources by using it.

## Dependencies

- [bgfx.cmake](https://github.com/JoshuaBrookover/bgfx.cmake)
  - [bgfx](https://github.com/bkaradzic/bgfx)
  - [bx](https://github.com/bkaradzic/bx)
  - [bimg](https://github.com/bkaradzic/bimg)
- [GLFW](https://github.com/glfw/glfw)
- [GLM](https://github.com/g-truc/glm)

## Notes

- OpenGL only
- Right-handed
- Y up and -Z forward

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3native.h>
#include <dear-imgui/imgui.h>

namespace
{
    constexpr int window_width = 1280;
    constexpr int window_height = 720;
}

int main(int argc, char** argv)
{
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "Hello bgfx!", nullptr, nullptr);

    bgfx::PlatformData platform_data;
    platform_data.nwh = glfwGetCocoaWindow(window);
    bgfx::setPlatformData(platform_data);

    bgfx::Init bgfxInit;
    bgfxInit.type = bgfx::RendererType::Count;
    bgfxInit.resolution.width = window_width;
    bgfxInit.resolution.height = window_height;
    bgfxInit.resolution.reset = BGFX_RESET_VSYNC;
    bgfx::init(bgfxInit);

    return 0;
}

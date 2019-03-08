#include <bgfx/bgfx.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3native.h>

#define FIX_MACOS_MOJAVE_ISSUE

namespace
{
    constexpr int window_width = 1280;
    constexpr int window_height = 720;
}

int main(int argc, char** argv)
{
    if (!glfwInit())
    {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "Hello bgfx!", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    bgfx::Init bgfx_init_settings;
    bgfx_init_settings.type = bgfx::RendererType::Count;
    bgfx_init_settings.resolution.width = window_width;
    bgfx_init_settings.resolution.height = window_height;
    bgfx_init_settings.resolution.reset = BGFX_RESET_VSYNC;
    bgfx_init_settings.platformData.nwh = glfwGetCocoaWindow(window);
    bgfx::init(bgfx_init_settings);

    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);
    bgfx::setViewRect(0, 0, 0, window_width, window_height);

    glfwHideWindow(window);
    glfwShowWindow(window);

#ifdef FIX_MACOS_MOJAVE_ISSUE
    bool is_initialized_for_mojave = false;
#endif

    while (!glfwWindowShouldClose(window))
    {
#ifdef FIX_MACOS_MOJAVE_ISSUE
        if (!is_initialized_for_mojave)
        {
            glfwPollEvents();
            glfwSetWindowSize(window, window_width + 1, window_height);
            glfwSetWindowSize(window, window_width, window_height);
            is_initialized_for_mojave = true;
        }
#endif

        bgfx::frame();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    bgfx::shutdown();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

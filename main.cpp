#include <bgfx/bgfx.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3native.h>

#define FIX_MACOS_MOJAVE_ISSUE

namespace
{
    constexpr int window_width = 600;
    constexpr int window_height = 400;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
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
    glfwSetKeyCallback(window, key_callback);

    bgfx::Init bgfx_init_settings;
    bgfx_init_settings.type = bgfx::RendererType::Count;
    bgfx_init_settings.resolution.width = window_width;
    bgfx_init_settings.resolution.height = window_height;
    bgfx_init_settings.resolution.reset = BGFX_RESET_VSYNC;
    bgfx_init_settings.platformData.nwh = glfwGetCocoaWindow(window);
    bgfx::init(bgfx_init_settings);

    constexpr uint64 bg_color = 0x443355FF;
    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, bg_color, 1.0f, 0);
    bgfx::setViewRect(0, 0, 0, window_width, window_height);

#ifdef FIX_MACOS_MOJAVE_ISSUE
    bool is_initialized_for_mojave = false;
#endif

    int counter = 0;
    while (!glfwWindowShouldClose(window))
    {
#ifdef FIX_MACOS_MOJAVE_ISSUE
        if (!is_initialized_for_mojave)
        {
            constexpr int non_zero = 1;
            glfwPollEvents();
            glfwSetWindowSize(window, window_width + non_zero, window_height);
            glfwSetWindowSize(window, window_width, window_height);
            is_initialized_for_mojave = true;
        }
#endif

        const uint64 color = (counter % 60 < 5) ? 0xAA3355FF : 0x443355FF;
        bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, color, 1.0f, 0);

        bgfx::submit(0, bgfx::ProgramHandle());
        bgfx::frame();

        glfwPollEvents();

        ++ counter;
        counter %= 60;
    }

    bgfx::shutdown();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

#ifndef templatewindow_hpp
#define templatewindow_hpp

#include <chrono>
#include <bgfx/bgfx.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3native.h>

#define FIX_MACOS_MOJAVE_ISSUE

class TemplateWindow
{
public:
    TemplateWindow(const std::string& title, const int width = 640, const int height = 480)
    {
        if (!glfwInit())
        {
            throw std::runtime_error("Cannot initialize GLFW.");
        }

        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

        if (!m_window) { throw std::runtime_error("Cannot create a window."); }

        glfwMakeContextCurrent(m_window);

        glewInit();

        std::cout << "vendor   : " << glGetString(GL_VENDOR) << std::endl;
        std::cout << "renderer : " << glGetString(GL_RENDERER) << std::endl;
        std::cout << "version  : " << glGetString(GL_VERSION) << std::endl;
        std::cout << "shader   : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

        glfwMakeContextCurrent(nullptr);

        m_time_point = std::chrono::steady_clock::now();
    }

    ~TemplateWindow()
    {
        glfwMakeContextCurrent(m_window);

        if (m_is_initialized)
        {
            bgfx::shutdown();
        }

        glfwMakeContextCurrent(nullptr);
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

    void run()
    {
        const int width = getWidth();
        const int height = getHeight();

        glfwMakeContextCurrent(m_window);

        bgfx::Init bgfx_init_settings;
        bgfx_init_settings.type = bgfx::RendererType::OpenGL;
        bgfx_init_settings.resolution.width = width;
        bgfx_init_settings.resolution.height = height;
        bgfx_init_settings.resolution.reset = BGFX_RESET_VSYNC;
        bgfx_init_settings.platformData.nwh = glfwGetCocoaWindow(m_window);
        bgfx::init(bgfx_init_settings);

        initializeGraphics();

        m_is_initialized = true;

#ifdef FIX_MACOS_MOJAVE_ISSUE
        bool is_initialized_for_mojave = false;
#endif

        m_counter = 0;
        while (!glfwWindowShouldClose(m_window))
        {
#ifdef FIX_MACOS_MOJAVE_ISSUE
            if (!is_initialized_for_mojave)
            {
                constexpr int non_zero = 1;
                glfwPollEvents();
                glfwSetWindowSize(m_window, width + non_zero, height);
                glfwSetWindowSize(m_window, width, height);
                is_initialized_for_mojave = true;
            }
#endif

#if 0
            bgfx::setDebug(BGFX_DEBUG_STATS);
#endif

            updateGraphics();
            bgfx::frame();

            glfwPollEvents();
            ++ m_counter;
        }

        glfwMakeContextCurrent(nullptr);
    }

    GLFWwindow* getWindow() const { return m_window; }

    int getWidth() const
    {
        int width, height;
        glfwGetWindowSize(m_window, &width, &height);
        return width;
    }

    int getHeight() const
    {
        int width, height;
        glfwGetWindowSize(m_window, &width, &height);
        return height;
    }

    float getAspect() const
    {
        int width, height;
        glfwGetWindowSize(m_window, &width, &height);
        return static_cast<float>(width) / static_cast<float>(height);
    }

    uint32_t getCounter() const { return m_counter; }

protected:

    virtual void initializeGraphics() = 0;
    virtual void updateGraphics() = 0;

    GLFWwindow* m_window;

    bool m_is_initialized = false;

    uint64_t getElapsedTimeInMilliseconds() const
    {
        const auto current_time_point = std::chrono::steady_clock::now();
        const auto elapsed_duration   = std::chrono::duration_cast<std::chrono::milliseconds>(current_time_point - m_time_point);

        return elapsed_duration.count();
    }

private:

    uint32_t m_counter;
    std::chrono::steady_clock::time_point m_time_point;
};

#endif /* templatewindow_hpp */

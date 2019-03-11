#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "template-window.hpp"
#include "camera.hpp"
#include "primitives/cube.hpp"

namespace bgfxutil
{
    bgfx::ShaderHandle loadShader(const std::string& shader_path)
    {
        std::ifstream input_stream(shader_path, std::ios::binary);
        if (!input_stream.is_open())
        {
            throw std::runtime_error("Failed to open a shader file.");
        }

        input_stream.seekg(0, std::ios::end);
        const long file_size = input_stream.tellg();
        input_stream.seekg(0);
        const bgfx::Memory* mem = bgfx::alloc(file_size + 1);
        input_stream.read(reinterpret_cast<char*>(mem->data), file_size);
        mem->data[mem->size - 1] = '\0';

        return bgfx::createShader(mem);
    }
}

std::string getShaderDirectoryPath(const bgfx::RendererType::Enum renderer_type)
{
    const std::string base_path = HELLO_BGFX_RUNTIME_RESOURCE_DIR;
    const std::string render_type_directory_name = [&]()
    {
        switch (renderer_type)
        {
            case bgfx::RendererType::OpenGL: return "glsl";
            default: throw std::runtime_error("Renderer type not supported.");
        }
    }();
    return base_path + "/" + render_type_directory_name;
}

class Window : public TemplateWindow
{
public:

    Window(const std::string& title);
    ~Window();

protected:

    void initializeGraphics() override;
    void updateGraphics() override;

private:

    Camera m_camera;
    Cube m_cube;

    bgfx::ShaderHandle m_vertex_shader;
    bgfx::ShaderHandle m_fragment_shader;
    bgfx::ProgramHandle m_program;
};

Window::Window(const std::string& title) :
TemplateWindow(title),
m_camera(
{
    { 0.0, 0.0, - 5.0 },
    { 0.0, 0.0, 0.0 },
    { 0.0, 1.0, 0.0 },
})
{
}

Window::~Window()
{
}

void Window::initializeGraphics()
{
    constexpr uint32_t bg_color = 0x333333ff;
    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, bg_color, 1.0f, 0);
    bgfx::setViewRect(0, 0, 0, getWidth(), getHeight());

    const std::string shader_directory_path = getShaderDirectoryPath(bgfx::getRendererType());
    m_vertex_shader = bgfxutil::loadShader(shader_directory_path + "/vs_blinnphong.bin");
    m_fragment_shader = bgfxutil::loadShader(shader_directory_path + "/fs_blinnphong.bin");
    m_program = bgfx::createProgram(m_vertex_shader, m_fragment_shader, true);

    m_cube.initializePrimitive();
}

void Window::updateGraphics()
{
    const glm::mat4 view_matrix = m_camera.getViewMatrix();
    const glm::mat4 proj_matrix = glm::perspective(glm::radians(60.0f), getAspect(), 0.1f, 100.0f);
    bgfx::setViewTransform(0, glm::value_ptr(view_matrix), glm::value_ptr(proj_matrix));

    const float t = static_cast<float>(getElapsedTimeInMilliseconds()) / 1000.0;
    constexpr int n = 4;
    for (int x = - n; x <= n; ++ x)
    {
        for (int y = - n; y <= n; ++ y)
        {
            glm::mat4 model_matrix(1.0f);
            model_matrix = glm::translate(model_matrix, glm::vec3(x, y, 0.0f));
            model_matrix = glm::rotate(model_matrix, t, glm::vec3(x, y, 1.0f));
            model_matrix = glm::scale(model_matrix, glm::vec3(2.0f / n));
            bgfx::setTransform(glm::value_ptr(model_matrix));

            m_cube.submitPrimitive(m_program);
        }
    }
}

int main(int argc, char** argv)
{
    Window window("Hello bgfx!");
    window.run();
    return 0;
}

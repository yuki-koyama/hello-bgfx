#include <fstream>
#include <iostream>
#include <string>
#include <bx/math.h>
#include "templatewindow.hpp"

std::string getShaderDirectoryPath(const bgfx::RendererType::Enum renderer_type)
{
    const std::string base_path = BGFX_EXAMPLE_SHADERS_DIR;
    const std::string render_type_directory_name = [&]()
    {
        switch (renderer_type)
        {
            case bgfx::RendererType::Metal: return "metal";
            case bgfx::RendererType::OpenGL: return "glsl";
            default: throw std::runtime_error("Renderer type not supported.");
        }
    }();
    return base_path + "/" + render_type_directory_name;
}

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

struct Camera
{
    bx::Vec3 target;
    bx::Vec3 position;
    bx::Vec3 up;
};

struct Vertex
{
    float x;
    float y;
    float z;
    uint32_t abgr;
};

class Window : public TemplateWindow
{
public:

    Window(const std::string& title)
    : TemplateWindow(title)
    {
    }

    ~Window()
    {
        if (m_is_initialized)
        {
            bgfx::destroy(m_index_buffer_handle);
            bgfx::destroy(m_vertex_buffer_handle);
        }
    }

protected:

    void initializeGraphics() override
    {
        constexpr uint32_t bg_color = 0x333333ff;
        bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, bg_color, 1.0f, 0);
        bgfx::setViewRect(0, 0, 0, getWidth(), getHeight());

        static const Vertex cube_vertices[] =
        {
            { -1.0f,  1.0f,  1.0f, 0xff000000 },
            {  1.0f,  1.0f,  1.0f, 0xff0000ff },
            { -1.0f, -1.0f,  1.0f, 0xff00ff00 },
            {  1.0f, -1.0f,  1.0f, 0xff00ffff },
            { -1.0f,  1.0f, -1.0f, 0xffff0000 },
            {  1.0f,  1.0f, -1.0f, 0xffff00ff },
            { -1.0f, -1.0f, -1.0f, 0xffffff00 },
            {  1.0f, -1.0f, -1.0f, 0xffffffff },
        };

        static const uint16_t cube_triangle_list[] =
        {
            0, 1, 2,
            1, 3, 2,
            4, 6, 5,
            5, 6, 7,
            0, 2, 4,
            4, 2, 6,
            1, 5, 3,
            5, 7, 3,
            0, 4, 1,
            4, 5, 1,
            2, 3, 6,
            6, 3, 7,
        };

        bgfx::VertexDecl vertex_decl;
        vertex_decl.begin()
        .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
        .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
        .end();
        m_vertex_buffer_handle = bgfx::createVertexBuffer(bgfx::makeRef(cube_vertices, sizeof(cube_vertices)), vertex_decl);
        m_index_buffer_handle = bgfx::createIndexBuffer(bgfx::makeRef(cube_triangle_list, sizeof(cube_triangle_list)));

        const std::string shader_directory_path = getShaderDirectoryPath(bgfx::getRendererType());
        m_vertex_shader = loadShader(shader_directory_path + "/vs_cubes.bin");
        m_fragment_shader = loadShader(shader_directory_path + "/fs_cubes.bin");
        m_program = bgfx::createProgram(m_vertex_shader, m_fragment_shader, true);
    }

    void updateGraphics() override
    {
        const float t = static_cast<float>(getElapsedTimeInMilliseconds()) / 1000.0;

        float view_matrix[16];
        bx::mtxLookAt(view_matrix, m_camera.position, m_camera.target, m_camera.up);
        float proj_matrix[16];
        bx::mtxProj(proj_matrix, 60.0f, getAspect(), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
        bgfx::setViewTransform(0, view_matrix, proj_matrix);

        float model_matrix[16];
        bx::mtxRotateXY(model_matrix, 1.1f * t, 1.7f * t);
        bgfx::setTransform(model_matrix);

        bgfx::setVertexBuffer(0, m_vertex_buffer_handle);
        bgfx::setIndexBuffer(m_index_buffer_handle);

        bgfx::submit(0, m_program);
    }

private:

    Camera m_camera =
    {
        { 0.0, 0.0, 0.0 },
        { 0.0, 0.0, - 5.0 },
        { 0.0, 1.0, 0.0 },
    };

    bgfx::VertexBufferHandle m_vertex_buffer_handle;
    bgfx::IndexBufferHandle m_index_buffer_handle;

    bgfx::ShaderHandle m_vertex_shader;
    bgfx::ShaderHandle m_fragment_shader;
    bgfx::ProgramHandle m_program;
};

int main(int argc, char** argv)
{
    Window window("Hello bgfx!");
    window.run();
    return 0;
}

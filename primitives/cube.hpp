#ifndef cube_hpp
#define cube_hpp

#include <bgfx/bgfx.h>

struct PositionColorVertex
{
    float x;
    float y;
    float z;
    uint32_t abgr;
};

class Cube
{
public:
    void initializePrimitive()
    {
        static const PositionColorVertex cube_vertices[] =
        {
            {  1.0f,  1.0f,  1.0f, 0xff000000 },
            { -1.0f,  1.0f,  1.0f, 0xff0000ff },
            {  1.0f, -1.0f,  1.0f, 0xff00ff00 },
            { -1.0f, -1.0f,  1.0f, 0xff00ffff },
            {  1.0f,  1.0f, -1.0f, 0xffff0000 },
            { -1.0f,  1.0f, -1.0f, 0xffff00ff },
            {  1.0f, -1.0f, -1.0f, 0xffffff00 },
            { -1.0f, -1.0f, -1.0f, 0xffffffff },
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
            1, 0, 2,
            3, 1, 2,
        };

        bgfx::VertexDecl vertex_decl;
        vertex_decl.begin()
        .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
        .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
        .end();
        m_vertex_buffer_handle = bgfx::createVertexBuffer(bgfx::makeRef(cube_vertices, sizeof(cube_vertices)), vertex_decl);
        m_index_buffer_handle = bgfx::createIndexBuffer(bgfx::makeRef(cube_triangle_list, sizeof(cube_triangle_list)));
    }

    void submitPrimitive(bgfx::ProgramHandle program) const
    {
        bgfx::setVertexBuffer(0, m_vertex_buffer_handle);
        bgfx::setIndexBuffer(m_index_buffer_handle);

        bgfx::submit(0, program);
    }

private:
    bgfx::VertexBufferHandle m_vertex_buffer_handle;
    bgfx::IndexBufferHandle m_index_buffer_handle;
};

#endif /* cube_hpp */

#ifndef cube_hpp
#define cube_hpp

#include <cassert>
#include "abstract-primitive.hpp"

class Cube : public AbstractPrimitive
{
public:

    Cube() : AbstractPrimitive() {}

    void initializePrimitive() override
    {
        static const PositionNormalVertex vertices[] =
        {
            { { +0.5, +0.5, +0.5 }, { 0.0, 0.0, +1.0 } },
            { { -0.5, +0.5, +0.5 }, { 0.0, 0.0, +1.0 } },
            { { -0.5, -0.5, +0.5 }, { 0.0, 0.0, +1.0 } },
            { { +0.5, +0.5, +0.5 }, { 0.0, 0.0, +1.0 } },
            { { -0.5, -0.5, +0.5 }, { 0.0, 0.0, +1.0 } },
            { { +0.5, -0.5, +0.5 }, { 0.0, 0.0, +1.0 } },

            { { +0.5, +0.5, -0.5 }, { +1.0, 0.0, 0.0 } },
            { { +0.5, +0.5, +0.5 }, { +1.0, 0.0, 0.0 } },
            { { +0.5, -0.5, +0.5 }, { +1.0, 0.0, 0.0 } },
            { { +0.5, +0.5, -0.5 }, { +1.0, 0.0, 0.0 } },
            { { +0.5, -0.5, +0.5 }, { +1.0, 0.0, 0.0 } },
            { { +0.5, -0.5, -0.5 }, { +1.0, 0.0, 0.0 } },

            { { -0.5, +0.5, -0.5 }, { 0.0, 0.0, -1.0 } },
            { { +0.5, +0.5, -0.5 }, { 0.0, 0.0, -1.0 } },
            { { +0.5, -0.5, -0.5 }, { 0.0, 0.0, -1.0 } },
            { { -0.5, +0.5, -0.5 }, { 0.0, 0.0, -1.0 } },
            { { +0.5, -0.5, -0.5 }, { 0.0, 0.0, -1.0 } },
            { { -0.5, -0.5, -0.5 }, { 0.0, 0.0, -1.0 } },

            { { -0.5, +0.5, +0.5 }, { -1.0, 0.0, 0.0 } },
            { { -0.5, +0.5, -0.5 }, { -1.0, 0.0, 0.0 } },
            { { -0.5, -0.5, -0.5 }, { -1.0, 0.0, 0.0 } },
            { { -0.5, +0.5, +0.5 }, { -1.0, 0.0, 0.0 } },
            { { -0.5, -0.5, -0.5 }, { -1.0, 0.0, 0.0 } },
            { { -0.5, -0.5, +0.5 }, { -1.0, 0.0, 0.0 } },

            { { +0.5, +0.5, -0.5 }, { 0.0, +1.0, 0.0 } },
            { { -0.5, +0.5, -0.5 }, { 0.0, +1.0, 0.0 } },
            { { -0.5, +0.5, +0.5 }, { 0.0, +1.0, 0.0 } },
            { { +0.5, +0.5, -0.5 }, { 0.0, +1.0, 0.0 } },
            { { -0.5, +0.5, +0.5 }, { 0.0, +1.0, 0.0 } },
            { { +0.5, +0.5, +0.5 }, { 0.0, +1.0, 0.0 } },

            { { -0.5, -0.5, +0.5 }, { 0.0, -1.0, 0.0 } },
            { { -0.5, -0.5, -0.5 }, { 0.0, -1.0, 0.0 } },
            { { +0.5, -0.5, -0.5 }, { 0.0, -1.0, 0.0 } },
            { { -0.5, -0.5, +0.5 }, { 0.0, -1.0, 0.0 } },
            { { +0.5, -0.5, -0.5 }, { 0.0, -1.0, 0.0 } },
            { { +0.5, -0.5, +0.5 }, { 0.0, -1.0, 0.0 } },
        };

        static const uint16_t triangle_list[] =
        {
            0, 1, 2,
            3, 4, 5,
            6, 7, 8,
            9, 10, 11,
            12, 13, 14,
            15, 16, 17,
            18, 19, 20,
            21, 22, 23,
            24, 25, 26,
            27, 28, 29,
            30, 31, 32,
            33, 34, 35,
        };

        bgfx::VertexDecl vertex_decl;
        vertex_decl.begin()
        .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
        .add(bgfx::Attrib::Normal, 3, bgfx::AttribType::Float)
        .end();
        m_vertex_buffer_handle = bgfx::createVertexBuffer(bgfx::makeRef(vertices, sizeof(vertices)), vertex_decl);
        m_index_buffer_handle = bgfx::createIndexBuffer(bgfx::makeRef(triangle_list, sizeof(triangle_list)));

        m_is_initialized = true;
    }

    void submitPrimitive(bgfx::ProgramHandle program) const override
    {
        assert(m_is_initialized);

        bgfx::setVertexBuffer(0, m_vertex_buffer_handle);
        bgfx::setIndexBuffer(m_index_buffer_handle);

        bgfx::submit(0, program);
    }
};

#endif /* cube_hpp */

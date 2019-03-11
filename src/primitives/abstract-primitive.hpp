#ifndef abstract_primitive_hpp
#define abstract_primitive_hpp

#include <cassert>
#include <bgfx/bgfx.h>
#include <glm/glm.hpp>

struct PositionNormalVertex
{
    glm::vec3 position;
    glm::vec3 normal;
};

class AbstractPrimitive
{
public:

    AbstractPrimitive()
    : m_is_initialized(false)
    {
    }

    ~AbstractPrimitive()
    {
        if (m_is_initialized)
        {
            bgfx::destroy(m_vertex_buffer_handle);
        }
    }

    virtual void initializePrimitive() = 0;

    void submitPrimitive(bgfx::ProgramHandle program) const
    {
        assert(m_is_initialized);

        bgfx::setVertexBuffer(0, m_vertex_buffer_handle);
        bgfx::setIndexBuffer(m_index_buffer_handle);

        bgfx::submit(0, program);
    }

protected:

    bool m_is_initialized;

    bgfx::VertexBufferHandle m_vertex_buffer_handle;
    bgfx::IndexBufferHandle m_index_buffer_handle;
};

#endif /* abstract_primitive_hpp */

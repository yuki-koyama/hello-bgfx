#ifndef abstract_primitive_hpp
#define abstract_primitive_hpp

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
    virtual void submitPrimitive(bgfx::ProgramHandle program) const = 0;

protected:

    bool m_is_initialized;

    bgfx::VertexBufferHandle m_vertex_buffer_handle;
    bgfx::IndexBufferHandle m_index_buffer_handle;
};

#endif /* abstract_primitive_hpp */

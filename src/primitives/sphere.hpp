#ifndef sphere_hpp
#define sphere_hpp

#include <vector>
#include "abstract-primitive.hpp"

class Sphere : public AbstractPrimitive
{
public:

    Sphere() : AbstractPrimitive() {}

    void initializePrimitive() override
    {
        constexpr double pi = glm::pi<double>();

        static std::vector<PositionNormalVertex> vertices(m_latitude_resolution * m_longitude_resolution * 6);
        static std::vector<uint16_t> triangle_list(m_latitude_resolution * m_longitude_resolution * 6);

        for (int i = 0; i < m_longitude_resolution; ++ i)
        {
            const double theta_xy_1 = 2.0 * static_cast<double>(i + 0) * pi / static_cast<double>(m_longitude_resolution);
            const double theta_xy_2 = 2.0 * static_cast<double>(i + 1) * pi / static_cast<double>(m_longitude_resolution);
            const double x_1        = std::cos(theta_xy_1);
            const double x_2        = std::cos(theta_xy_2);
            const double y_1        = std::sin(theta_xy_1);
            const double y_2        = std::sin(theta_xy_2);

            for (int j = 0; j < m_latitude_resolution; ++ j)
            {
                const double theta_z_1 = static_cast<double>(j + 0) * pi / static_cast<double>(m_latitude_resolution);
                const double theta_z_2 = static_cast<double>(j + 1) * pi / static_cast<double>(m_latitude_resolution);
                const double cos_1 = std::cos(theta_z_1);
                const double cos_2 = std::cos(theta_z_2);
                const double sin_1 = std::sin(theta_z_1);
                const double sin_2 = std::sin(theta_z_2);

                const int offset = i * m_latitude_resolution * 6 + j * 6;

                const glm::vec3 vertex_0 = { sin_2 * x_1, sin_2 * y_1, cos_2 };
                const glm::vec3 vertex_1 = { sin_2 * x_2, sin_2 * y_2, cos_2 };
                const glm::vec3 vertex_2 = { sin_1 * x_2, sin_1 * y_2, cos_1 };
                const glm::vec3 vertex_3 = { sin_2 * x_1, sin_2 * y_1, cos_2 };
                const glm::vec3 vertex_4 = { sin_1 * x_2, sin_1 * y_2, cos_1 };
                const glm::vec3 vertex_5 = { sin_1 * x_1, sin_1 * y_1, cos_1 };

                vertices[offset + 0] = { vertex_0, vertex_0 };
                vertices[offset + 1] = { vertex_1, vertex_1 };
                vertices[offset + 2] = { vertex_2, vertex_2 };
                vertices[offset + 3] = { vertex_3, vertex_3 };
                vertices[offset + 4] = { vertex_4, vertex_4 };
                vertices[offset + 5] = { vertex_5, vertex_5 };
            }
        }

        for (int i = 0; i < triangle_list.size(); ++ i)
        {
            triangle_list[i] = static_cast<uint16_t>(i);
        }

        bgfx::VertexDecl vertex_decl;
        vertex_decl.begin()
        .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
        .add(bgfx::Attrib::Normal, 3, bgfx::AttribType::Float)
        .end();
        m_vertex_buffer_handle = bgfx::createVertexBuffer(bgfx::makeRef(vertices.data(), sizeof(PositionNormalVertex) * vertices.size()), vertex_decl);
        m_index_buffer_handle = bgfx::createIndexBuffer(bgfx::makeRef(triangle_list.data(), sizeof(uint16_t) * triangle_list.size()));

        m_is_initialized = true;
    }

private:

    const int m_latitude_resolution  = 20;
    const int m_longitude_resolution = 30;
};

#endif /* sphere_hpp */

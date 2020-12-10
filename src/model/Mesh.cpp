#include "model/Mesh.h"

namespace bubo {

    Mesh::Mesh() {}

    Mesh::Mesh(std::vector<glm::vec3> positions, std::vector<unsigned int> indices)
            : m_positions(positions), m_indices(indices) {}

    Mesh::Mesh(std::vector<glm::vec3> positions,
               std::vector<glm::vec2> uv,
               std::vector<unsigned int> indices)
            : m_positions(positions),
              m_UV(uv),
              m_indices(indices) {}

    Mesh::Mesh(std::vector<glm::vec3> positions,
               std::vector<glm::vec2> uv,
               std::vector<glm::vec3> normals,
               std::vector<unsigned int> indices)
            : m_positions(positions),
              m_UV(uv),
              m_normals(normals),
              m_indices(indices) {}

    Mesh::~Mesh() {}

    void Mesh::finalize() {

        if (!m_VAO) {
            m_VAO = std::make_shared<VertexArrayObject>();
        }

        std::vector<float> vertices;
        for (int i = 0; i < m_positions.size(); ++i) {

            vertices.push_back(m_positions[i].x);
            vertices.push_back(m_positions[i].y);
            vertices.push_back(m_positions[i].z);

            if (m_UV.size() > 0) {
                vertices.push_back(m_UV[i].x);
                vertices.push_back(m_UV[i].y);
            }

            if (m_normals.size() > 0) {
                vertices.push_back(m_normals[i].x);
                vertices.push_back(m_normals[i].y);
                vertices.push_back(m_normals[i].z);
            }
        }

        std::stringstream ss;
        for (int i = 0; i < vertices.size(); ++i) {
           ss << vertices.data()[i] << " ";
        }

        m_VAO->bind();
        m_VBO = std::make_shared<VertexBufferObject>(vertices.data(), vertices.size() * sizeof (float)); setVBOFormat();
        m_VAO->addVertexBuffer(m_VBO);

        if (m_indices.size() > 0) {
            m_IBO = std::make_shared<IndexBufferObject>(m_indices.data(),
                                                        m_indices.size() * sizeof (unsigned int),
                                                        m_indices.size());
            m_VAO->setIndexBuffer(m_IBO);
        }

    }

    void Mesh::setVBOFormat() {

        if (m_positions.size() > 0 && m_UV.size() > 0 && m_normals.size() > 0) {
            m_VBO->setFormat({
                {ShaderDataType::Vec3, "a_Pos"},
                {ShaderDataType::Vec2, "a_UV"},
                {ShaderDataType::Vec3, "a_Normal"}
            });
        } else if (m_positions.size() > 0 && m_UV.size() > 0) {
            m_VBO->setFormat({
                {ShaderDataType::Vec3, "a_Pos"},
                {ShaderDataType::Vec2, "a_UV"}
            });
        } else if (m_positions.size() > 0) {
            m_VBO->setFormat({
                {ShaderDataType::Vec3, "a_Pos"}
            });
        }

    }

}

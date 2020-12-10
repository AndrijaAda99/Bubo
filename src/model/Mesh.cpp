#include <list>
#include "model/Mesh.h"

namespace bubo {

    void Mesh::finalize() {

        // NOTE(Andrija)
        BUBO_ASSERT(m_meshProperty[Positions] && m_meshProperty[Indices],
                    "Position and Indices needs to be set before finalizing mesh!")

        if (!m_VAO) {
            m_VAO = std::make_shared<VertexArrayObject>();
        }

        std::vector<float> vertices;
        for (int i = 0; i < m_positions.size(); ++i) {

            vertices.push_back(m_positions[i].x);
            vertices.push_back(m_positions[i].y);
            vertices.push_back(m_positions[i].z);

            if (m_meshProperty[UVs]) {
                vertices.push_back(m_UVs[i].x);
                vertices.push_back(m_UVs[i].y);
            }

            if (m_meshProperty[Normals]) {
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

        if (m_meshProperty[Indices]) {
            m_IBO = std::make_shared<IndexBufferObject>(m_indices.data(),
                                                        m_indices.size() * sizeof (unsigned int),
                                                        m_indices.size());
            m_VAO->setIndexBuffer(m_IBO);
        }

        m_finalized = true;

    }

    void Mesh::setVBOFormat() {

        std::vector<BufferElementFormat> format;
        if (m_meshProperty[Positions]) {
            format.push_back({ShaderDataType::Vec3, "a_Pos"});
        }
        if (m_meshProperty[UVs]) {
            format.push_back({ShaderDataType::Vec2, "a_UV"});
        }
        if (m_meshProperty[Normals]) {
            format.push_back({ShaderDataType::Vec3, "a_Normal"});
        }

        m_VBO->setFormat(format);

    }

    void Mesh::setPositions(std::vector<glm::vec3> positions) {
        m_positions = positions;
        m_meshProperty[Positions] = true;
    }

    void Mesh::setUVs(std::vector<glm::vec2> uvs) {
        m_UVs = uvs;
        m_meshProperty[UVs] = true;
    }

    void Mesh::setNormals(std::vector<glm::vec3> normals) {
        m_normals = normals;
        m_meshProperty[Normals] = true;
    }

    void Mesh::setIndices(std::vector<unsigned int> indices) {
        m_indices = indices;
        m_meshProperty[Indices] = true;

    }

}

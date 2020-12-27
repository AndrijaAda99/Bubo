#include <list>
#include "scene/Mesh.h"

namespace bubo {

    void Mesh::finalize() {

        BUBO_ASSERT(m_meshProperty[Positions], "Position needs to be set before finalizing mesh!")

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

            if (m_meshProperty[TangentSpace]) {
                vertices.push_back(m_tangents[i].x);
                vertices.push_back(m_tangents[i].y);
                vertices.push_back(m_tangents[i].z);

                vertices.push_back(m_bitangents[i].x);
                vertices.push_back(m_bitangents[i].y);
                vertices.push_back(m_bitangents[i].z);
            }

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
        if (m_meshProperty[TangentSpace]) {
            format.push_back({ShaderDataType::Vec3, "a_Tangent"});
            format.push_back({ShaderDataType::Vec3, "a_Bitangent"});
        }

        m_VBO->setFormat(format);

    }

    void Mesh::setPositions(const std::vector<glm::vec3>& positions) {
        m_positions = positions;
        if (positions.size() > 0) {
            m_meshProperty[Positions] = true;
        }
    }

    void Mesh::setUVs(const std::vector<glm::vec2>& uvs) {
        m_UVs = uvs;
        if (uvs.size() > 0) {
            m_meshProperty[UVs] = true;
        }
    }

    void Mesh::setNormals(const std::vector<glm::vec3>& normals) {
        m_normals = normals;
        if (normals.size() > 0) {
            m_meshProperty[Normals] = true;
        }
    }

    void Mesh::setIndices(const std::vector<unsigned int>& indices) {
        m_indices = indices;
        if (indices.size() > 0) {
            m_meshProperty[Indices] = true;
        }
    }
    void Mesh::setTangentSpace(const std::vector<glm::vec3> &tangents, const std::vector<glm::vec3> &bitangents) {
        m_tangents = tangents;
        m_bitangents = bitangents;
        if (tangents.size() > 0) {
            m_meshProperty[TangentSpace] = true;
        }
    }

    void Mesh::bind() {
        m_VAO->bind();
    }

    void Mesh::unbind() {
        m_VAO->unbind();
    }


}

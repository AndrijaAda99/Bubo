#ifndef BUBO_MESH_H
#define BUBO_MESH_H

#include <renderer/IndexBufferObject.h>
#include <renderer/VertexArrayObject.h>
#include <renderer/VertexArrayObject.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>


namespace bubo {

#define NUMBER_OF_MESH_PROPERTY_TYPES (5)

    enum MeshPropertyType {
        Positions       = 0,
        UVs             = 1,
        Normals         = 2,
        Indices         = 3,
        TangentSpace    = 4
    };

    class Mesh {
    public:
        Mesh() {}
        ~Mesh() {}

        void setPositions(const std::vector<glm::vec3>& positions);
        void setUVs(const std::vector<glm::vec2>& uvs);
        void setNormals(const std::vector<glm::vec3>& normals);
        void setIndices(const std::vector<unsigned int>& indices);
        void setTangentSpace(const std::vector<glm::vec3> &tangents, const std::vector<glm::vec3> &bitangents);

        std::shared_ptr<VertexArrayObject> getVAO() { return m_VAO; }

        void finalize();
        void bind();
        void unbind();

        bool isFinalized() { return m_finalized; }
        bool isIndexed() { return m_meshProperty[Indices]; }

        int getVertexCount() { return m_positions.size(); }
        int getIndexCount() { return m_indices.size(); }

    private:
        void setVBOFormat();

    private:
        std::vector<glm::vec3> m_positions;
        std::vector<glm::vec2> m_UVs;
        std::vector<glm::vec3> m_normals;
        std::vector<glm::vec3> m_tangents;
        std::vector<glm::vec3> m_bitangents;

        std::vector<unsigned int> m_indices;

        std::shared_ptr<VertexBufferObject> m_VBO;
        std::shared_ptr<IndexBufferObject> m_IBO;
        std::shared_ptr<VertexArrayObject> m_VAO;

        std::vector<bool> m_meshProperty = std::vector<bool> (NUMBER_OF_MESH_PROPERTY_TYPES, false);

        bool m_finalized = false;
    };

}

#endif //BUBO_MESH_H

#ifndef BUBO_MESH_H
#define BUBO_MESH_H

#include <renderer/IndexBufferObject.h>
#include <renderer/VertexArrayObject.h>
#include <renderer/VertexArrayObject.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>


namespace bubo {

    class Mesh {
    public:
        Mesh();
        Mesh(std::vector<glm::vec3> positions, std::vector<unsigned int> indices);
        Mesh(std::vector<glm::vec3> positions, std::vector<glm::vec2> uv, std::vector<unsigned int> indices);
        Mesh(std::vector<glm::vec3> positions, std::vector<glm::vec2> uv,
             std::vector<glm::vec3> normals, std::vector<unsigned int> indices);

        ~Mesh();

        void setMPositions(std::vector<glm::vec3> positions) { m_positions = positions; }
        void setUV(std::vector<glm::vec2> uv) { m_UV = uv; }
        void setNormals(std::vector<glm::vec3> normals) { m_normals = normals; }
        void setIndices(std::vector<unsigned int> indices) { m_indices = indices; }

        std::shared_ptr<VertexArrayObject> getVAO() { return m_VAO; }

        void finalize();

    private:
        void setVBOFormat();

    private:
        std::vector<glm::vec3> m_positions;
        std::vector<glm::vec2> m_UV;
        std::vector<glm::vec3> m_normals;

        std::vector<unsigned int> m_indices;

        std::shared_ptr<VertexBufferObject> m_VBO;
        std::shared_ptr<IndexBufferObject> m_IBO;
        std::shared_ptr<VertexArrayObject> m_VAO;
    };

}

#endif //BUBO_MESH_H

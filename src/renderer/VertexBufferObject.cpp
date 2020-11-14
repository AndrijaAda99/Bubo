#include "renderer/VertexBufferObject.h"

#include "glad/glad.h"

namespace bubo {

    VertexBufferObject::VertexBufferObject(float *vertices, size_t size) {
        glGenBuffers(1, &m_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_id);

        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    VertexBufferObject::~VertexBufferObject() {
        glDeleteBuffers(1, &m_id);
    }

    void VertexBufferObject::bind() {
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
    }

    void VertexBufferObject::unbind() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

}
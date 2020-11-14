#include "renderer/IndexBufferObject.h"

#include "glad/glad.h"

namespace bubo {

    IndexBufferObject::IndexBufferObject(uint32_t *indices, size_t size, uint32_t count) : m_count(count) {
        glGenBuffers(1, &m_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
    }

    IndexBufferObject::~IndexBufferObject() {
        glDeleteBuffers(1, &m_id);
    }

    void IndexBufferObject::bind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    }

    void IndexBufferObject::unbind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

}

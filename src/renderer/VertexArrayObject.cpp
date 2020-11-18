#include "renderer/VertexArrayObject.h"

#include "glad/glad.h"

namespace bubo {

    GLenum parseType(ShaderDataType type) {
        switch (type) {
            case ShaderDataType::None:  BUBO_ASSERT(false, "ShaderDataType cannot be None!")
            case ShaderDataType::Bool:  return GL_BOOL;
            case ShaderDataType::Int:   return GL_INT;
            case ShaderDataType::Float: return GL_FLOAT;
            case ShaderDataType::Vec2:  return GL_FLOAT;
            case ShaderDataType::Vec3:  return GL_FLOAT;
            case ShaderDataType::Vec4:  return GL_FLOAT;
            case ShaderDataType::Mat3:  return GL_FLOAT;
            case ShaderDataType::Mat4:  return GL_FLOAT;
            default: BUBO_ASSERT(false, "Invalid ShaderDataType specified!")
        }
    }

    VertexArrayObject::VertexArrayObject() {
        glGenVertexArrays(1, &m_id);
    }

    VertexArrayObject::~VertexArrayObject() {
        glDeleteVertexArrays(1, &m_id);
    }

    void VertexArrayObject::bind() {
        glBindVertexArray(m_id);
    }

    void VertexArrayObject::unbind() {
        glBindVertexArray(0);
    }

    void VertexArrayObject::addVertexBuffer(std::shared_ptr<VertexBufferObject> vertexBuffer) {
        glBindVertexArray(m_id);
        vertexBuffer->bind();

        BUBO_ASSERT(vertexBuffer->getFormat().getFormat().size(), "Vertex Buffer Format is not specified!")

        unsigned int index = 0;
        for (const auto& element : vertexBuffer->getFormat()) {
            switch (element.type) {
                case ShaderDataType::Bool:
                case ShaderDataType::Int:
                case ShaderDataType::Float:
                case ShaderDataType::Vec2:
                case ShaderDataType::Vec3:
                case ShaderDataType::Vec4: {
                    glEnableVertexAttribArray(index);
                    glVertexAttribPointer(index,
                                          element.getCount(),
                                          parseType(element.type),
                                          element.normalized ? GL_TRUE : GL_FALSE,
                                          vertexBuffer->getFormat().getStride(),
                                          reinterpret_cast<void *>(element.offset));
                    index++;
                    break;
                }
                case ShaderDataType::Mat3:
                case ShaderDataType::Mat4: {
                    unsigned int count = element.getCount();
                    for (int i = 0; i < count; ++i) {
                        glEnableVertexAttribArray(index);
                        glVertexAttribPointer(index,
                                              count,
                                              parseType(element.type),
                                              element.normalized ? GL_TRUE : GL_FALSE,
                                              vertexBuffer->getFormat().getStride(),
                                              reinterpret_cast<void *>(element.offset + sizeof (float) * count * i));
                        index++;
                    }
                    break;
                }
                default: BUBO_ASSERT(false, "Invalid ShaderDataType specified!")
            }
        }

        m_vertexBuffers.push_back(vertexBuffer);
    }

    void VertexArrayObject::setIndexBuffer(std::shared_ptr<IndexBufferObject> indexBuffer) {
        glBindVertexArray(m_id);
        indexBuffer->bind();
        m_indexBuffer = indexBuffer;
    }

}

#ifndef BUBO_VERTEXARRAYOBJECT_H
#define BUBO_VERTEXARRAYOBJECT_H

#include "VertexBufferObject.h"
#include "IndexBufferObject.h"

namespace bubo {

    class VertexArrayObject {

    public:
        VertexArrayObject();
        ~VertexArrayObject();

        void bind();
        void unbind();

        void addVertexBuffer(std::shared_ptr<VertexBufferObject> vertexBuffer);
        void setVertexBuffer(std::shared_ptr<IndexBufferObject> indexBuffer);

        std::shared_ptr<IndexBufferObject> getIndexBuffer() { return m_indexBuffer; }

    private:
        unsigned int m_id;

        std::vector<std::shared_ptr<VertexBufferObject>> m_vertexBuffers;
        std::shared_ptr<IndexBufferObject> m_indexBuffer;

    };

}

#endif //BUBO_VERTEXARRAYOBJECT_H

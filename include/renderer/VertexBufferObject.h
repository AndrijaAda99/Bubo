#ifndef BUBO_VERTEXBUFFEROBJECT_H
#define BUBO_VERTEXBUFFEROBJECT_H

namespace bubo {

    class VertexBufferObject {
    public:
        VertexBufferObject(float *vertices, size_t size);
        ~VertexBufferObject();

        void bind();
        void unbind();

    private:
        unsigned int m_id;
    };

}

#endif //BUBO_VERTEXBUFFEROBJECT_H

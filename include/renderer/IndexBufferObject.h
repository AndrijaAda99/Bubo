#ifndef BUBO_INDEXBUFFEROBJECT_H
#define BUBO_INDEXBUFFEROBJECT_H

namespace bubo {

    class IndexBufferObject {
    public:
        IndexBufferObject(uint32_t *indices, size_t size, uint32_t count);
        ~IndexBufferObject();

        void bind();
        void unbind();

        unsigned int getCount() { return m_count; };

    private:
        unsigned int m_id;
        unsigned int m_count;
    };

}

#endif //BUBO_INDEXBUFFEROBJECT_H

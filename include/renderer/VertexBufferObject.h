#ifndef BUBO_VERTEXBUFFEROBJECT_H
#define BUBO_VERTEXBUFFEROBJECT_H

namespace bubo {

    enum class ShaderDataType {
        None = 0, Bool, Int, Float,
        Vec2, Vec3, Vec4,
        Mat3, Mat4
    };

    struct BufferElementFormat {
        ShaderDataType type;
        std::string name;
        bool normalized;
        unsigned int size;
        unsigned int offset;

        static unsigned int getSizeFromType(ShaderDataType type) {
            switch (type) {
                case ShaderDataType::None: BUBO_ASSERT(false, "ShaderDataType cannot be None!")
                case ShaderDataType::Bool: return 1;
                case ShaderDataType::Int: return 4;
                case ShaderDataType::Float: return 4;
                case ShaderDataType::Vec2: return 4 * 2;
                case ShaderDataType::Vec3: return 4 * 3;
                case ShaderDataType::Vec4: return 4 * 4;
                case ShaderDataType::Mat3: return 4 * 3 * 3;
                case ShaderDataType::Mat4: return 4 * 4 * 4;
                default: BUBO_ASSERT(false, "Invalid ShaderDataType specified!")
            }
        }

        BufferElementFormat(ShaderDataType type_, std::string name_, bool normalized_ = false)
            : type(type_), name(name_), normalized(normalized_), size(getSizeFromType(type_)), offset(0) {}

        unsigned int getCount() const {
            switch (type) {
                case ShaderDataType::None: BUBO_ASSERT(false, "ShaderDataType cannot be None!")
                case ShaderDataType::Bool:  return 1;
                case ShaderDataType::Int:   return 1;
                case ShaderDataType::Float: return 1;
                case ShaderDataType::Vec2:  return 2;
                case ShaderDataType::Vec3:  return 3;
                case ShaderDataType::Vec4:  return 4;
                case ShaderDataType::Mat3:  return 3;
                case ShaderDataType::Mat4:  return 4;
                default: BUBO_ASSERT(false, "Invalid ShaderDataType specified!")
            }
        }
    };

    class BufferFormat {
    public:
        BufferFormat(std::vector<BufferElementFormat> format) : m_format(format) {
            for (auto& element : m_format) {
                element.offset = m_stride;
                m_stride += element.size;
            }
        }

        const std::vector<BufferElementFormat> &getFormat() const { return m_format; }
        unsigned int getStride() const { return m_stride; }

        std::vector<BufferElementFormat>::iterator begin() { return m_format.begin(); }
        std::vector<BufferElementFormat>::iterator end() { return m_format.end(); }
        std::vector<BufferElementFormat>::const_iterator begin() const { return m_format.begin(); }
        std::vector<BufferElementFormat>::const_iterator end() const { return m_format.end(); }

    private:
        std::vector<BufferElementFormat> m_format;
        unsigned int m_stride = 0;
    };

    class VertexBufferObject {
    public:
        VertexBufferObject(float *vertices, size_t size);
        ~VertexBufferObject();

        void bind();
        void unbind();

        void setFormat(std::vector<BufferElementFormat> format) { m_format = format; }
        const BufferFormat& getFormat() const { return m_format; }

    private:
        unsigned int m_id;
        BufferFormat m_format = BufferFormat(std::initializer_list<BufferElementFormat>());
    };

}

#endif //BUBO_VERTEXBUFFEROBJECT_H

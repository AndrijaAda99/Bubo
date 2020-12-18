#ifndef BUBO_FRAMEBUFFER_H
#define BUBO_FRAMEBUFFER_H

namespace bubo {

    struct FramebufferProperties {
        uint32_t width;
        uint32_t height;
    };

    class Framebuffer {
    public:
        Framebuffer(const FramebufferProperties& properties);
        ~Framebuffer();

        void bind();
        void unbind();

        void resize(uint32_t width, uint32_t height);

        void bindColorAttachment();

    private:
        void create();
        void clear();
    private:
        unsigned int m_id;
        unsigned int m_colorAttachment;
        unsigned int m_renderAttachment;
        FramebufferProperties m_properties;

    };

}

#endif //BUBO_FRAMEBUFFER_H

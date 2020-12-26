#include "renderer/Framebuffer.h"

#include "glad/glad.h"

namespace bubo {

    Framebuffer::Framebuffer(const bubo::FramebufferProperties &properties)
            : m_properties(properties) {
        create();
    }

    Framebuffer::~Framebuffer() {
        clear();
    }

    void Framebuffer::create() {

        if (m_id) {
            clear();
        }

        glGenFramebuffers(1, &m_id);
        glBindFramebuffer(GL_FRAMEBUFFER, m_id);

        glGenTextures(1, &m_colorAttachment);
        glBindTexture(GL_TEXTURE_2D, m_colorAttachment);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_properties.width, m_properties.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorAttachment, 0);

        glGenRenderbuffers(1, &m_renderAttachment);
        glBindRenderbuffer(GL_RENDERBUFFER, m_renderAttachment);

        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_properties.width, m_properties.height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderAttachment);

        glBindTexture(GL_TEXTURE_2D, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Framebuffer::bind() {
        glBindFramebuffer(GL_FRAMEBUFFER, m_id);
        glViewport(0, 0, m_properties.width, m_properties.height);
    }

    void Framebuffer::unbind() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Framebuffer::resize(uint32_t width, uint32_t height) {
        m_properties.width = width;
        m_properties.height = height;

        create();
    }

    void Framebuffer::clear() {
        glDeleteFramebuffers(1, &m_id);
        glDeleteTextures(1, &m_colorAttachment);
        glDeleteRenderbuffers(1, &m_renderAttachment);
    }

    void Framebuffer::bindColorAttachment() {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_colorAttachment);
    }

}

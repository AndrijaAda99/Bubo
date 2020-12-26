#include "renderer/Texture.h"

#include "glad/glad.h"

#include "stb/stb_image.h"


namespace bubo {

    Texture::Texture(const std::string &path) {
        glGenTextures(1, &m_id);
        glBindTexture(GL_TEXTURE_2D, m_id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int width, height, channels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        BUBO_ASSERT(data, "Could not load image! Path:" + path)
        m_width = width;
        m_height = height;

        int internalFormat = 0, format = 0;
        if (channels == 4) {
            internalFormat = GL_RGBA8;
            format = GL_RGBA;
        } else if (channels == 3) {
            internalFormat = GL_RGB8;
            format = GL_RGB;
        } else if (channels == 1) {
            internalFormat = GL_RED;
            format = GL_RED;
        }

        BUBO_ASSERT(internalFormat && format, "Channel format not supported!")

        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }

    Texture::~Texture() {
        glDeleteTextures(1, &m_id);
    }

    void Texture::bind(unsigned int unit) const {
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_2D, m_id);
    }

    TextureCube::TextureCube(const std::array<std::string, 6> &paths) {
        glGenTextures(1, &m_id);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        for (int i = 0; i < 6; ++i) {

            int width, height, channels;
            stbi_set_flip_vertically_on_load(false);
            BUBO_DEBUG_TRACE("Loading cube texture: {0}", paths[i].c_str());
            unsigned char* data = stbi_load(paths[i].c_str(), &width, &height, &channels, 0);
            BUBO_ASSERT(data, "Could not load image! Path:" + paths[i])
            m_width = width;
            m_height = height;

            int internalFormat = 0, format = 0;
            if (channels == 4) {
                internalFormat = GL_RGBA8;
                format = GL_RGBA;
            } else if (channels == 3) {
                internalFormat = GL_RGB8;
                format = GL_RGB;
            } else if (channels == 1) {
                internalFormat = GL_RED;
                format = GL_RED;
            }

            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, internalFormat,
                         m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);

        }

    }

    TextureCube::~TextureCube() {
        glDeleteTextures(1, &m_id);
    }

    void TextureCube::bind(unsigned int unit) const {
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);
    }

}
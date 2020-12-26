#ifndef BUBO_TEXTURE_H
#define BUBO_TEXTURE_H


namespace bubo {

    class Texture {

    public:
        Texture(const std::string& path);
        ~Texture();

        void bind(unsigned int unit) const;

        const unsigned int getWidth() const { return m_width; }
        const unsigned int getHeight() const { return m_height; }
        const unsigned int getID() const { return m_id; }

    private:
        unsigned int m_width, m_height;
        unsigned int m_id;
    };

    class TextureCube {
    public:
        TextureCube(const std::array<std::string, 6>& paths);
        ~TextureCube();

        void bind(unsigned int unit) const;

        const unsigned int getWidth() const { return m_width; }
        const unsigned int getHeight() const { return m_height; }
        const unsigned int getID() const { return m_id; }

    private:
        unsigned int m_width, m_height;
        unsigned int m_id;

    };

}


#endif //BUBO_TEXTURE_H

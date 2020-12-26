#ifndef BUBO_SKYBOX_H
#define BUBO_SKYBOX_H

#include "Scene.h"

namespace bubo {

    class Skybox {
    public:
        Skybox(const std::string &path);
        ~Skybox();

        void bind();
        void unbind();

    private:
        void init(const std::string &path);
        void destroy();

    private:
        TextureCube* m_cubeMap;
        Mesh* m_cubeMesh;

    };

}

#endif //BUBO_SKYBOX_H

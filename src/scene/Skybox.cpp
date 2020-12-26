#include "scene/Skybox.h"

namespace bubo {

    Skybox::Skybox(const std::string &path) {
        init(path);
    }

    Skybox::~Skybox() {
        destroy();
    }

    void Skybox::init(const std::string &path) {

        std::array<std::string, 6> paths = {
                path + "/right.jpg",
                path + "/left.jpg",
                path + "/top.jpg",
                path + "/bottom.jpg",
                path + "/front.jpg",
                path + "/back.jpg"
        };

        BUBO_DEBUG_TRACE("Loading skybox textures from path: {0}", path.c_str());
        m_cubeMap = new TextureCube(paths);

        BUBO_DEBUG_TRACE("Setting up skybox mesh data!");
        m_cubeMesh = new Mesh();

        m_cubeMesh->setPositions({
            glm::vec3(-1.0f,  1.0f, -1.0f),
            glm::vec3(-1.0f, -1.0f, -1.0f),
            glm::vec3( 1.0f, -1.0f, -1.0f),
            glm::vec3( 1.0f, -1.0f, -1.0f),
            glm::vec3( 1.0f,  1.0f, -1.0f),
            glm::vec3(-1.0f,  1.0f, -1.0f),

            glm::vec3(-1.0f, -1.0f,  1.0f),
            glm::vec3(-1.0f, -1.0f, -1.0f),
            glm::vec3(-1.0f,  1.0f, -1.0f),
            glm::vec3(-1.0f,  1.0f, -1.0f),
            glm::vec3(-1.0f,  1.0f,  1.0f),
            glm::vec3(-1.0f, -1.0f,  1.0f),

            glm::vec3( 1.0f, -1.0f, -1.0f),
            glm::vec3( 1.0f, -1.0f,  1.0f),
            glm::vec3( 1.0f,  1.0f,  1.0f),
            glm::vec3( 1.0f,  1.0f,  1.0f),
            glm::vec3( 1.0f,  1.0f, -1.0f),
            glm::vec3( 1.0f, -1.0f, -1.0f),

            glm::vec3(-1.0f, -1.0f,  1.0f),
            glm::vec3(-1.0f,  1.0f,  1.0f),
            glm::vec3( 1.0f,  1.0f,  1.0f),
            glm::vec3( 1.0f,  1.0f,  1.0f),
            glm::vec3( 1.0f, -1.0f,  1.0f),
            glm::vec3(-1.0f, -1.0f,  1.0f),

            glm::vec3(-1.0f,  1.0f, -1.0f),
            glm::vec3( 1.0f,  1.0f, -1.0f),
            glm::vec3( 1.0f,  1.0f,  1.0f),
            glm::vec3( 1.0f,  1.0f,  1.0f),
            glm::vec3(-1.0f,  1.0f,  1.0f),
            glm::vec3(-1.0f,  1.0f, -1.0f),

            glm::vec3(-1.0f, -1.0f, -1.0f),
            glm::vec3(-1.0f, -1.0f,  1.0f),
            glm::vec3( 1.0f, -1.0f, -1.0f),
            glm::vec3( 1.0f, -1.0f, -1.0f),
            glm::vec3(-1.0f, -1.0f,  1.0f),
            glm::vec3( 1.0f, -1.0f,  1.0f)
        });

        m_cubeMesh->finalize();

    }

    void Skybox::destroy() {
        delete m_cubeMesh;
        delete m_cubeMap;
    }

    void Skybox::bind() {
        m_cubeMesh->bind();
        m_cubeMap->bind(0);
    }

    void Skybox::unbind() {
        m_cubeMesh->unbind();
    }

}

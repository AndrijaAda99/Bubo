#ifndef BUBO_RENDERER_H
#define BUBO_RENDERER_H

#include <scene/Mesh.h>
#include <scene/Scene.h>
#include "VertexArrayObject.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Material.h"
#include "Framebuffer.h"

namespace bubo {

    class Renderer {
    public:
        static void init(uint32_t width, uint32_t height);
        static void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

        static void beginScene(const Camera& camera);
        static void endScene();

        static void submit(Mesh* mesh, Material* material, glm::mat4 transform);
        static void renderScene(SceneNode* node);

        static void destroy();

    private:

        struct RendererData_t {
            glm::mat4 viewProjectionMatrix;
            glm::vec3 cameraPosition;

            std::unique_ptr<Framebuffer> framebuffer = nullptr;
            std::unique_ptr<VertexArrayObject> framebufferVAO = nullptr;
        };

        static std::unique_ptr<RendererData_t> s_data;

    };

}

#endif //BUBO_RENDERER_H

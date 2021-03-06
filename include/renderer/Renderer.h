#ifndef BUBO_RENDERER_H
#define BUBO_RENDERER_H

#include <scene/Mesh.h>
#include <scene/Scene.h>
#include <scene/Skybox.h>
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
        static void onUpdate(float deltaTime);
        static void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

        static void beginScene(const Camera& camera);
        static void endScene();

        static void submit(Mesh* mesh, Material* material, glm::mat4 transform);
        static void submitLights(Shader* shader);
        static void renderScene(SceneNode* node);

        static void destroy();

    private:
        static void initFramebuffer(uint32_t width, uint32_t height);
        static void beginFramebuffer();
        static void endFramebuffer();

        static void initSkybox();
        static void renderSkybox();

        struct RendererData_t {
            glm::mat4 viewProjectionMatrix;
            glm::mat4 noTranslationViewProjectionMatrix;
            glm::vec3 cameraPosition;

            std::unique_ptr<Framebuffer> framebuffer = nullptr;
            std::unique_ptr<VertexArrayObject> framebufferVAO = nullptr;
            std::unique_ptr<Skybox> skybox = nullptr;

            float gamma = 2.2f;
            float levels = 6.0f;
        };

        static std::unique_ptr<RendererData_t> s_data;

    };

}

#endif //BUBO_RENDERER_H

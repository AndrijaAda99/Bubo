#ifndef BUBO_RENDERER_H
#define BUBO_RENDERER_H

#include <scene/Mesh.h>
#include <scene/Scene.h>
#include "VertexArrayObject.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Material.h"

namespace bubo {

    class Renderer {
    public:
        static void init();
        static void clear();
        static void setColor(const glm::vec4& color);
        static void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

        static void beginScene(const Camera& camera);
        static void endScene();

        static void submit(std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, std::shared_ptr<Mesh> mesh, const glm::mat4& model);

        static void submit(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material, glm::mat4 model);
        static void submit(Mesh* mesh, std::shared_ptr<Material> material, glm::mat4 model);
        static void submit(Mesh* mesh, Material* material, glm::mat4 transform);
        static void renderScene(SceneNode* node);

    private:
        static void drawIndexedMesh(std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, std::shared_ptr<Mesh> mesh, const glm::mat4& model);
        static void drawMesh(std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, std::shared_ptr<Mesh> mesh, const glm::mat4& model);

        struct RendererData_t {
            glm::mat4 viewProjectionMatrix;
            glm::vec3 cameraPosition;
        };

        static std::unique_ptr<RendererData_t> s_data;

    };

}

#endif //BUBO_RENDERER_H

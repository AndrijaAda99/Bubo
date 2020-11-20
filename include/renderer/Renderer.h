#ifndef BUBO_RENDERER_H
#define BUBO_RENDERER_H

#include "VertexArrayObject.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"

namespace bubo {

    class Renderer {
    public:
        static void clear();
        static void setColor(const glm::vec4& color);
        static void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

        static void beginScene(std::shared_ptr<Camera> camera);
        static void endScene();

        static void submit(std::shared_ptr<Shader> shader, std::shared_ptr<VertexArrayObject> vertexArray);
        static void submit(std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, std::shared_ptr<VertexArrayObject> vertexArray);
    private:
        struct RendererData_t {
            glm::mat4 viewProjectionMatrix;
        };

        static std::unique_ptr<RendererData_t> s_data;

    };

}

#endif //BUBO_RENDERER_H

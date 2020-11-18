#ifndef BUBO_RENDERER_H
#define BUBO_RENDERER_H

#include "VertexArrayObject.h"
#include "Shader.h"
#include "Texture.h"

namespace bubo {

    class Renderer {
    public:
        static void clear();
        static void setColor(const glm::vec4& color);
        static void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

        static void beginScene();
        static void endScene();

        static void submit(std::shared_ptr<Shader> shader, std::shared_ptr<VertexArrayObject> vertexArray);
        static void submit(std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, std::shared_ptr<VertexArrayObject> vertexArray);

    };

}

#endif //BUBO_RENDERER_H

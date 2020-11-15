#include "renderer/Renderer.h"

#include "glad/glad.h"

namespace bubo {

    void Renderer::beginScene() {
    }

    void Renderer::endScene() {
    }

    void Renderer::submit(std::shared_ptr<Shader> shader, std::shared_ptr<VertexArrayObject> vertexArray) {
        shader->bind();
        vertexArray->bind();
        glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, 0);
    }

    void Renderer::setColor(const glm::vec4& color) {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void Renderer::setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
        glViewport(x, y, width, height);
    }

    void Renderer::clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

}

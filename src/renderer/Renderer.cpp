#include "renderer/Renderer.h"

#include "glad/glad.h"

namespace bubo {

    std::unique_ptr<Renderer::RendererData_t> Renderer::s_data = std::make_unique<Renderer::RendererData_t>();

    void Renderer::beginScene(std::shared_ptr<Camera> camera) {
        s_data->viewProjectionMatrix = camera->getViewProjection();
    }

    void Renderer::endScene() {
    }

    void Renderer::submit(std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, 
                          std::shared_ptr<VertexArrayObject> vertexArray, const glm::mat4& model) {
        texture->bind(0);
        shader->bind();
        shader->setMat4("u_ViewProjection", s_data->viewProjectionMatrix);
        shader->setMat4("u_Model", model);
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

    void Renderer::init() {
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);
    }

}

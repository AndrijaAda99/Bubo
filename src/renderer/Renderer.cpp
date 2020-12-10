#include "renderer/Renderer.h"

#include "glad/glad.h"

namespace bubo {

    std::unique_ptr<Renderer::RendererData_t> Renderer::s_data = std::make_unique<Renderer::RendererData_t>();

    void Renderer::beginScene(const Camera &camera) {
        s_data->viewProjectionMatrix = camera.getViewProjection();
        s_data->cameraPosition = camera.getPosition();
    }

    void Renderer::endScene() {
    }

    void Renderer::drawIndexedMesh(std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture,
                                   std::shared_ptr<Mesh> mesh, const glm::mat4 &model) {
        texture->bind(0);
        shader->bind();
        shader->setMat4("u_ViewProjection", s_data->viewProjectionMatrix);
        shader->setMat4("u_Model", model);
        mesh->getVAO()->bind();
        glDrawElements(GL_TRIANGLES, mesh->getIndexCount(), GL_UNSIGNED_INT, 0);
        mesh->getVAO()->unbind();
        shader->unbind();
    }

    void Renderer::drawMesh(std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture,
                            std::shared_ptr<Mesh> mesh, const glm::mat4 &model) {

        texture->bind(0);

        shader->bind();
        shader->setMat4("u_ViewProjection", s_data->viewProjectionMatrix);
        shader->setMat4("u_Model", model);
        shader->setFloat3("u_lightPos", glm::vec3(100.0f));
        shader->setFloat3("u_lightColor", glm::vec3(1.0f));
        shader->setFloat3("u_objectColor", glm::vec3(1.0f, 0.5f, 0.32f));
        shader->setFloat3("u_viewPos", s_data->cameraPosition);

        mesh->getVAO()->bind();
        glDrawArrays(GL_TRIANGLES, 0, mesh->getVertexCount());
        mesh->getVAO()->unbind();

        shader->unbind();

    }

    void Renderer::submit(std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture,
                          std::shared_ptr<Mesh> mesh, const glm::mat4 &model) {

        BUBO_ASSERT(mesh->isFinalized(), "Mesh need to be finalized before rendering!")

        if (mesh->isIndexed()) {
            drawIndexedMesh(shader, texture, mesh, model);
        } else {
            drawMesh(shader, texture, mesh, model);
        }

    }

    void Renderer::setColor(const glm::vec4 &color) {
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
        glEnable(GL_MULTISAMPLE);
    }

}
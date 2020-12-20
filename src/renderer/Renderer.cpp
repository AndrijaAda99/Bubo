#include <core/Assert.h>
#include "renderer/Renderer.h"

#include "glad/glad.h"

namespace bubo {

    std::unique_ptr<Renderer::RendererData_t> Renderer::s_data = std::make_unique<Renderer::RendererData_t>();

    void Renderer::beginScene(const Camera &camera) {

        s_data->viewProjectionMatrix = camera.getViewProjection();
        s_data->cameraPosition = camera.getPosition();

        s_data->framebuffer->bind();
        glEnable(GL_DEPTH_TEST);

        glClearColor(.1f, .1f, .1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    }

    void Renderer::endScene() {
        s_data->framebuffer->unbind();
        glDisable(GL_DEPTH_TEST);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glEnable(GL_COLOR_BUFFER_BIT);

#ifdef POSTPROCESSING_POSTERIZATION
        ShaderLibrary::get("posterizationShader")->bind();
        ShaderLibrary::get("posterizationShader")->setFloat("u_Gamma", 0.3f);
        ShaderLibrary::get("posterizationShader")->setFloat("u_NumColors", 4.0f);
#else
        ShaderLibrary::get("framebufferShader")->bind();
#endif
        s_data->framebufferVAO->bind();
        s_data->framebuffer->bindColorAttachment();
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    void Renderer::setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
        glViewport(x, y, width, height);
        s_data->framebuffer->resize(width, height);
    }

    void Renderer::init(uint32_t width, uint32_t height) {
        FramebufferProperties properties;
        properties.width = width;
        properties.height = height;

        s_data->framebuffer = std::make_unique<Framebuffer>(properties);
        s_data->framebufferVAO = std::make_unique<VertexArrayObject>();

        float quadVertices[] = {
                // positions   // texCoords
                -1.0f,  1.0f,  0.0f, 1.0f,
                -1.0f, -1.0f,  0.0f, 0.0f,
                1.0f, -1.0f,  1.0f, 0.0f,

                -1.0f,  1.0f,  0.0f, 1.0f,
                1.0f, -1.0f,  1.0f, 0.0f,
                1.0f,  1.0f,  1.0f, 1.0f
        };


        std::shared_ptr<VertexBufferObject> framebufferVBO = std::make_shared<VertexBufferObject>(quadVertices, sizeof (quadVertices));
        framebufferVBO->setFormat({
                                          {ShaderDataType::Vec2, "a_Pos"},
                                          {ShaderDataType::Vec2, "a_TexCoords"}
                                  });

        s_data->framebufferVAO->addVertexBuffer(framebufferVBO);
        s_data->framebufferVAO->unbind();

        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_MULTISAMPLE);
    }

    void Renderer::renderScene(SceneNode *node) {
        if (node->mesh && node->material) {
            Renderer::submit(node->mesh, node->material, node->getTransform());
        }

        for (SceneNode *child : node->getChildren()) {
            Renderer::renderScene(child);
        }
    }

    void Renderer::submit(Mesh *mesh, Material *material, glm::mat4 transform) {

        material->setMat4("u_ViewProjection", s_data->viewProjectionMatrix);
        material->setVec3("u_viewPos", s_data->cameraPosition);
        material->setMat4("u_Model", transform);

        material->setVec3("u_Material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
        material->setFloat("u_Material.shininess", 32.0f);

        material->setVec3("u_directionalLight.direction", glm::vec3(-1.0f, -1.0f, -1.0f));
        material->setVec3("u_directionalLight.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
        material->setVec3("u_directionalLight.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
        material->setVec3("u_directionalLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));

        material->setVec3("u_pointLight.position",glm::vec3(0.0f, 5.0f, -10.0f));
        material->setVec3("u_pointLight.ambient", glm::vec3(0.2f, 0.2f, 0.0f));
        material->setVec3("u_pointLight.diffuse", glm::vec3(0.5f, 0.5f, 0.0f));
        material->setVec3("u_pointLight.specular",glm::vec3(1.0f, 1.0f, 0.0f));

        material->setSamplers();
        material->setUniforms();

        mesh->bind();
        if (mesh->isIndexed()) {
            glDrawElements(GL_TRIANGLES, mesh->getIndexCount(), GL_UNSIGNED_INT, 0);
        } else {
            glDrawArrays(GL_TRIANGLES, 0, mesh->getVertexCount());
        }
        mesh->unbind();
    }

    void Renderer::destroy() {
        s_data->framebuffer.release();
        s_data->framebufferVAO.release();
        s_data.release();
    }

}
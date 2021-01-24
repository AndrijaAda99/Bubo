#include <scene/Lights.h>
#include <core/Input.h>
#include "renderer/Renderer.h"

#include "glad/glad.h"

namespace bubo {

    std::unique_ptr<Renderer::RendererData_t> Renderer::s_data = std::make_unique<Renderer::RendererData_t>();

    void Renderer::beginScene(const Camera &camera) {

        s_data->viewProjectionMatrix = camera.getViewProjection();
        s_data->noTranslationViewProjectionMatrix = camera.getNoTranslationViewProjection();
        s_data->cameraPosition = camera.getPosition();

        Renderer::beginFramebuffer();

        glClearColor(.1f, .1f, .1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    }

    void Renderer::endScene() {
        Renderer::renderSkybox();
        Renderer::endFramebuffer();
    }

    void Renderer::setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
        glViewport(x, y, width, height);
        s_data->framebuffer->resize(width, height);
    }

    void Renderer::init(uint32_t width, uint32_t height) {

        BUBO_DEBUG_TRACE("Initializing framebuffer...");
        Renderer::initFramebuffer(width, height);

        BUBO_DEBUG_TRACE("Initializing skybox...");
        Renderer::initSkybox();

        glViewport(0, 0, width, height);

        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_MULTISAMPLE);
        glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

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

        material->getShader()->setMat4("u_ViewProjection", s_data->viewProjectionMatrix);
        material->getShader()->setVec3("u_ViewPos", s_data->cameraPosition);
        material->getShader()->setMat4("u_Model", transform);

        material->getShader()->setFloat("u_Material.shininess", 32.0f);

        Renderer::submitLights(material->getShader());

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
        s_data->framebuffer.reset();
        s_data->framebufferVAO.reset();
        s_data->skybox.reset();
        s_data.reset();
    }

    void Renderer::initFramebuffer(uint32_t width, uint32_t height) {

        FramebufferProperties properties;
        properties.width = width;
        properties.height = height;

        s_data->framebuffer = std::make_unique<Framebuffer>(properties);
        s_data->framebufferVAO = std::make_unique<VertexArrayObject>();

        float quadVertices[] = {
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

    }

    void Renderer::beginFramebuffer() {
        s_data->framebuffer->bind();
        glEnable(GL_DEPTH_TEST);
    }

    void Renderer::endFramebuffer() {

        s_data->framebuffer->unbind();

        glDisable(GL_DEPTH_TEST);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glEnable(GL_COLOR_BUFFER_BIT);

#ifdef POSTPROCESSING_POSTERIZATION
        ShaderLibrary::get("posterizationShader")->bind();
        ShaderLibrary::get("posterizationShader")->setFloat("u_Gamma", s_data->gamma);
        ShaderLibrary::get("posterizationShader")->setFloat("u_Levels", s_data->levels);
#else
        ShaderLibrary::get("framebufferShader")->bind();
#endif
        s_data->framebufferVAO->bind();
        s_data->framebuffer->bindColorAttachment();

        glDrawArrays(GL_TRIANGLES, 0, 6);

    }

    void Renderer::initSkybox() {

        s_data->skybox = std::make_unique<Skybox>("../../res/assets/skybox");

        ShaderLibrary::get("skyboxShader")->bind();
        ShaderLibrary::get("skyboxShader")->setInt("u_Skybox", 0);
        ShaderLibrary::get("skyboxShader")->unbind();

    }

    void Renderer::renderSkybox() {

        glDepthFunc(GL_LEQUAL);

        ShaderLibrary::get("skyboxShader")->bind();
        ShaderLibrary::get("skyboxShader")->setMat4("u_ViewProjection", s_data->noTranslationViewProjectionMatrix);

        s_data->skybox->bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);
        s_data->skybox->unbind();

        ShaderLibrary::get("skyboxShader")->unbind();

        glDepthFunc(GL_LESS);

    }

    void Renderer::submitLights(Shader *shader) {

        shader->setVec3("u_DirectionalLight.direction", Lights::getDirectionalLight().getDirection());
        shader->setVec3("u_DirectionalLight.ambient",   Lights::getDirectionalLight().getAmbient());
        shader->setVec3("u_DirectionalLight.diffuse",   Lights::getDirectionalLight().getDiffuse());
        shader->setVec3("u_DirectionalLight.specular",  Lights::getDirectionalLight().getSpecular());

        for (int i = 0; i < Lights::getNumOfPointLights(); ++i) {
            std::stringstream ss;
            ss << "u_PointLight[" << i << "].";

            shader->setVec3(ss.str().append("position"), Lights::getPointLights()[i].getPosition());
            shader->setVec3(ss.str().append("ambient"), Lights::getPointLights()[i].getAmbient());
            shader->setVec3(ss.str().append("diffuse"), Lights::getPointLights()[i].getDiffuse());
            shader->setVec3(ss.str().append("specular"), Lights::getPointLights()[i].getSpecular());

            shader->setFloat(ss.str().append("constant"), Lights::getPointLights()[i].getConstantFactor());
            shader->setFloat(ss.str().append("linear"), Lights::getPointLights()[i].getLinearFactor());
            shader->setFloat(ss.str().append("quadratic"), Lights::getPointLights()[i].getQuadraticFactor());

            ss.clear();
        }

    }

    void Renderer::onUpdate(float deltaTime) {

#ifdef POSTPROCESSING_POSTERIZATION
        if (Input::isKeyPressed(KEY_K)) {
            s_data->gamma += 0.5f * deltaTime;
        }
        if (Input::isKeyPressed(KEY_J)) {
            s_data->gamma -= 0.5f * deltaTime;
        }
        if (Input::isKeyPressed(KEY_L)) {
            s_data->levels += 1.0f * deltaTime;
        }
        if (Input::isKeyPressed(KEY_H)) {
            s_data->levels -= 1.0f * deltaTime;
        }
#endif

    }

}
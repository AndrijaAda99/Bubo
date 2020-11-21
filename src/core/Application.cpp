#include "core/Application.h"

#include "renderer/Renderer.h"
#include <glm/trigonometric.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace bubo {

    Application* Application::s_appInstance = nullptr;

    Application::Application() {
        BUBO_ASSERT(!s_appInstance, "Application already created!")
        s_appInstance = this;

        m_window = std::make_unique<Window>(WindowProperties_t());
        m_window->setEventCallbackFunction(BIND_EVENT_FUNC(onEvent));
        m_window->setVSync(false);

        m_camera = std::make_shared<PerspectiveCamera>(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);

        m_shaderProgram = std::make_unique<Shader>("../../res/shaders/vertex.shader", "../../res/shaders/fragment.shader");

        m_texture = std::make_shared<Texture>("../../res/assets/textures/container.jpg");
        m_shaderProgram->setInt("u_Texture", 0);

        float vertices[] = {
                 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
                 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
                -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
                -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
        };

        unsigned int indices[] {
                0, 1, 3,
                1, 2, 3
        };

        m_vertexArray = std::make_shared<VertexArrayObject>();

        m_vertexBuffer = std::make_shared<VertexBufferObject>(vertices, sizeof (vertices));
        m_vertexBuffer->setFormat({
            {ShaderDataType::Vec3, "a_Pos"},
            {ShaderDataType::Vec3, "a_Color"},
            {ShaderDataType::Vec2, "a_TexCoord"}
        });

        m_vertexArray->addVertexBuffer(m_vertexBuffer);

        m_indexBuffer = std::make_shared<IndexBufferObject>(indices, sizeof (indices), 6);
        m_vertexArray->setIndexBuffer(m_indexBuffer);

        Renderer::init();
    }

    Application::~Application() {}

    void Application::run() {

        while (m_running) {
            m_camera->setPosition(glm::vec3(3 * sin(glfwGetTime()), 0.0f, 3 * cos(glfwGetTime())));

            m_shaderProgram->bind();
            m_shaderProgram->setFloat4("u_Color",
                                       glm::vec4((sin(2*glfwGetTime()) + 1) / 4.0f,
                                                 (cos(2*glfwGetTime()) + 1) / 4.0f,
                                                 (sin(2*glfwGetTime()) + 1) / 4.0f,
                                                 0.0f));
            m_shaderProgram->unbind();

            Renderer::setColor(glm::vec4(.1f, .1f, .1f, 1.0f));
            Renderer::clear();

            Renderer::beginScene(m_camera);

            for (int i = 0; i < 10; ++i) {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, (float) -2*i));
                model = glm::rotate(model, glm::radians((float) 10 * i), glm::vec3(0.0f, 0.0f, 1.0f));
                model = glm::scale(model, glm::vec3((float) i, 1.0f, 1.0f));
                Renderer::submit(m_shaderProgram, m_texture, m_vertexArray, model);
            }

            Renderer::endScene();

            m_window->update();
        }

    }

    void Application::onEvent(Event &e) {
        EventDispatcher dispatcher(e);

        dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(onWindowClose));
        dispatcher.dispatch<WindowResizeEvent>(BIND_EVENT_FUNC(onWindowResize));
    }

    bool Application::onWindowClose(WindowCloseEvent &e) {
        m_running = false;
        return true;
    }

    bool Application::onWindowResize(WindowResizeEvent &e) {
        BUBO_DEBUG_TRACE(e.toString());
        Renderer::setViewport(0, 0, e.getWindowWidth(), e.getWindowHeight());
        return true;
    }
}
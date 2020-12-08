#include "core/Application.h"

#include "renderer/Renderer.h"
#include <glm/trigonometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <events/MouseEvent.h>


namespace bubo {

    Application* Application::s_appInstance = nullptr;

    Application::Application() {
        BUBO_ASSERT(!s_appInstance, "Application already created!")
        s_appInstance = this;

        m_window = std::make_unique<Window>(WindowProperties_t());
        m_window->setEventCallbackFunction(BIND_EVENT_FUNC(onEvent));
#ifdef VSYNC
        m_window->setVSync(true);
#else
        m_window->setVSync(false);
#endif

        m_CameraController = std::make_shared<PerspectiveCameraController>();

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

        float currentTime = glfwGetTime();
        float accumulator = 0.0f;

        while (m_running) {

            float newTime = glfwGetTime();
            float frameTime = newTime - currentTime;
            currentTime = newTime;

#ifdef DISPLAY_FPS
            BUBO_DEBUG_TRACE("FPS: {0}", 1.0f / frameTime);
#endif

            accumulator += frameTime;
            while (accumulator >= m_deltaTime) {
                m_CameraController->onUpdate(m_deltaTime);
                accumulator -= m_deltaTime;
            }


            m_shaderProgram->bind();
            m_shaderProgram->setFloat4("u_Color",
                                       glm::vec4((sin(2*glfwGetTime()) + 1) / 4.0f,
                                                 (cos(2*glfwGetTime()) + 1) / 4.0f,
                                                 (sin(2*glfwGetTime()) + 1) / 4.0f,
                                                 0.0f));
            m_shaderProgram->unbind();

            Renderer::setColor(glm::vec4(.1f, .1f, .1f, 1.0f));
            Renderer::clear();

            Renderer::beginScene(m_CameraController->getCamera());

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

        dispatcher.dispatch<MouseMovedEvent>(BIND_EVENT_FUNC(onMouseMoved));
        dispatcher.dispatch<MouseButtonPressedEvent>(BIND_EVENT_FUNC(onMousePressed));
        dispatcher.dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FUNC(onMouseReleased));

        dispatcher.dispatch<KeyPressedEvent>(BIND_EVENT_FUNC(onKeyPressed));
        dispatcher.dispatch<KeyReleasedEvent>(BIND_EVENT_FUNC(onKeyReleased));
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

    bool Application::onMouseMoved(MouseMovedEvent &e) {
        float deltaX = e.getMouseX() - m_window->getMouseX();
        float deltaY =  m_window->getMouseY() - e.getMouseY();

        m_CameraController->onMouseMoved(deltaX, deltaY, m_deltaTime);

        m_window->setMouseX(e.getMouseX());
        m_window->setMouseY(e.getMouseY());

        return true;
    }

    bool Application::onMousePressed(MouseButtonPressedEvent &e) {
        BUBO_DEBUG_TRACE(e.toString());
        return true;
    }

    bool Application::onMouseReleased(MouseButtonReleasedEvent &e) {
        BUBO_DEBUG_TRACE(e.toString());
        return true;
    }

    bool Application::onKeyPressed(KeyPressedEvent &e) {
        BUBO_DEBUG_TRACE(e.toString());
        return true;
    }

    bool Application::onKeyReleased(KeyReleasedEvent &e) {
        BUBO_DEBUG_TRACE(e.toString());
        return true;
    }

}
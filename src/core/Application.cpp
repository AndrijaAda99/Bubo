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

        BUBO_DEBUG_INFO("Setting up Camera!");
        m_CameraController = std::make_shared<PerspectiveCameraController>();

        BUBO_DEBUG_INFO("Setting up Shader Program!");
        auto shaderProgram = std::make_shared<Shader>("../../res/shaders/vertex.shader", "../../res/shaders/fragment.shader");

        BUBO_DEBUG_INFO("Loading textures!");
        auto diffuseTexture = std::make_shared<Texture>("../../res/assets/textures/container2.png");
        auto specularTexture = std::make_shared<Texture>("../../res/assets/textures/container2_specular.png");

        BUBO_DEBUG_INFO("Setting up materials!");
        m_Material = std::make_shared<Material>(shaderProgram);
        m_Material->setTexture("u_Material.diffuse", diffuseTexture, 0);
        m_Material->setTexture("u_Material.specular", specularTexture, 1);

        std::vector<glm::vec3> pos = {
                {-0.5f, -0.5f, -0.5f},
                { 0.5f, -0.5f, -0.5f},
                { 0.5f,  0.5f, -0.5f},
                { 0.5f,  0.5f, -0.5f},
                {-0.5f,  0.5f, -0.5f},
                {-0.5f, -0.5f, -0.5f},

                {-0.5f, -0.5f,  0.5f},
                { 0.5f, -0.5f,  0.5f},
                { 0.5f,  0.5f,  0.5f},
                { 0.5f,  0.5f,  0.5f},
                {-0.5f,  0.5f,  0.5f},
                {-0.5f, -0.5f,  0.5f},

                {-0.5f,  0.5f,  0.5f},
                {-0.5f,  0.5f, -0.5f},
                {-0.5f, -0.5f, -0.5f},
                {-0.5f, -0.5f, -0.5f},
                {-0.5f, -0.5f,  0.5f},
                {-0.5f,  0.5f,  0.5f},

                { 0.5f,  0.5f,  0.5f},
                { 0.5f,  0.5f, -0.5f},
                { 0.5f, -0.5f, -0.5f},
                { 0.5f, -0.5f, -0.5f},
                { 0.5f, -0.5f,  0.5f},
                { 0.5f,  0.5f,  0.5f},

                {-0.5f, -0.5f, -0.5f},
                { 0.5f, -0.5f, -0.5f},
                { 0.5f, -0.5f,  0.5f},
                { 0.5f, -0.5f,  0.5f},
                {-0.5f, -0.5f,  0.5f},
                {-0.5f, -0.5f, -0.5f},

                {-0.5f,  0.5f, -0.5f},
                { 0.5f,  0.5f, -0.5f},
                { 0.5f,  0.5f,  0.5f},
                { 0.5f,  0.5f,  0.5f},
                {-0.5f,  0.5f,  0.5f},
                {-0.5f,  0.5f, -0.5f}
        };

        std::vector<glm::vec3> normals = {
                { 0.0f,  0.0f, -1.0f},
                { 0.0f,  0.0f, -1.0f},
                { 0.0f,  0.0f, -1.0f},
                { 0.0f,  0.0f, -1.0f},
                { 0.0f,  0.0f, -1.0f},
                { 0.0f,  0.0f, -1.0f},

                { 0.0f,  0.0f,  1.0f},
                { 0.0f,  0.0f,  1.0f},
                { 0.0f,  0.0f,  1.0f},
                { 0.0f,  0.0f,  1.0f},
                { 0.0f,  0.0f,  1.0f},
                { 0.0f,  0.0f,  1.0f},

                {-1.0f,  0.0f,  0.0f},
                {-1.0f,  0.0f,  0.0f},
                {-1.0f,  0.0f,  0.0f},
                {-1.0f,  0.0f,  0.0f},
                {-1.0f,  0.0f,  0.0f},
                {-1.0f,  0.0f,  0.0f},

                { 1.0f,  0.0f,  0.0f},
                { 1.0f,  0.0f,  0.0f},
                { 1.0f,  0.0f,  0.0f},
                { 1.0f,  0.0f,  0.0f},
                { 1.0f,  0.0f,  0.0f},
                { 1.0f,  0.0f,  0.0f},

                { 0.0f, -1.0f,  0.0f},
                { 0.0f, -1.0f,  0.0f},
                { 0.0f, -1.0f,  0.0f},
                { 0.0f, -1.0f,  0.0f},
                { 0.0f, -1.0f,  0.0f},
                { 0.0f, -1.0f,  0.0f},

                { 0.0f,  1.0f,  0.0f},
                { 0.0f,  1.0f,  0.0f},
                { 0.0f,  1.0f,  0.0f},
                { 0.0f,  1.0f,  0.0f},
                { 0.0f,  1.0f,  0.0f},
                { 0.0f,  1.0f,  0.0f}
        };

        std::vector<glm::vec2> uvs = {
                {0.0f,  0.0f},
                {1.0f,  0.0f},
                {1.0f,  1.0f},
                {1.0f,  1.0f},
                {0.0f,  1.0f},
                {0.0f,  0.0f},

                {0.0f,  0.0f},
                {1.0f,  0.0f},
                {1.0f,  1.0f},
                {1.0f,  1.0f},
                {0.0f,  1.0f},
                {0.0f,  0.0f},

                {1.0f,  0.0f},
                {1.0f,  1.0f},
                {0.0f,  1.0f},
                {0.0f,  1.0f},
                {0.0f,  0.0f},
                {1.0f,  0.0f},

                {1.0f,  0.0f},
                {1.0f,  1.0f},
                {0.0f,  1.0f},
                {0.0f,  1.0f},
                {0.0f,  0.0f},
                {1.0f,  0.0f},

                {0.0f,  1.0f},
                {1.0f,  1.0f},
                {1.0f,  0.0f},
                {1.0f,  0.0f},
                {0.0f,  0.0f},
                {0.0f,  1.0f},

                {0.0f,  1.0f},
                {1.0f,  1.0f},
                {1.0f,  0.0f},
                {1.0f,  0.0f},
                {0.0f,  0.0f},
                {0.0f,  1.0f},
        };

        BUBO_DEBUG_INFO("Setting up Mesh!");
        m_Mesh = std::make_shared<Mesh>();
        m_Mesh->setPositions(pos);
        m_Mesh->setNormals(normals);
        m_Mesh->setUVs(uvs);
        m_Mesh->finalize();

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

            Renderer::setColor(glm::vec4(.1f, .1f, .1f, 1.0f));
            Renderer::clear();

            Renderer::beginScene(m_CameraController->getCamera());

            for (int i = 0; i < 10; ++i) {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, (float) -2*i));
                model = glm::rotate(model, glm::radians((float) 10 * i), glm::vec3(0.0f, 0.0f, 1.0f));
                model = glm::scale(model, glm::vec3(i + 1.0f, 1.0f, 1.0f));
                Renderer::submit(m_Mesh, m_Material, model);
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
        m_CameraController->setPerspective(45.0f,
                                           (float) e.getWindowHeight() / (float) e.getWindowHeight(),
                                           0.1f,
                                           100.0f);
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
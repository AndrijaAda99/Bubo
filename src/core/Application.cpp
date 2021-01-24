#include "core/Application.h"

#include "renderer/Renderer.h"
#include <glm/trigonometric.hpp>
#include <events/MouseEvent.h>
#include <scene/Lights.h>

#include "scene/ModelLoader.h"


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

        BUBO_DEBUG_INFO("Setting up Camera...");
        m_CameraController = std::make_shared<PerspectiveCameraController>();

        BUBO_DEBUG_INFO("Setting up Shader Programs...");
        ShaderLibrary::makeDefaultShaders();

        BUBO_DEBUG_INFO("Initializing Lights Data...");
        Lights::init(2);

        BUBO_DEBUG_INFO("Setting up Scene...");
        for (int i = 0; i < 10; ++i) {
            auto backpack = ModelLoader::LoadModel("../../res/assets/backpack/backpack.obj", true);
            backpack->setScale(glm::vec3(0.8f + (rand() / (float) RAND_MAX)));
            backpack->setPosition(glm::vec3(
                    25.0f * (rand() / (float) RAND_MAX) - 17.5f,
                    0.0f,
                    25.0f * (rand() / (float) RAND_MAX) - 50.0f));
            backpack->setRotation(glm::vec4(
                    0.0f, 1.0f, 0.0f,
                    40.0f * (rand() / (float) RAND_MAX)));
            m_backpacks.push_back(backpack);
        }

        for (auto backpack : m_backpacks) {
            Scene::getRoot()->addChild(backpack);
        }

        BUBO_DEBUG_TRACE("Root num of children: {0}", Scene::getRoot()->getChildren().size());

        BUBO_DEBUG_INFO("Initializing Renderer...");
        Renderer::init(m_window->getWidth(), m_window->getHeight());
    }

    Application::~Application() {
        Renderer::destroy();
        ModelLoader::destroyMeshData();
        ModelLoader::destroyMaterialData();
        ModelLoader::destroyTextures();
        ShaderLibrary::destroyShaders();
        Lights::destroy();
    }

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
                Lights::onUpdate(currentTime, m_deltaTime);
                Renderer::onUpdate(m_deltaTime);
                accumulator -= m_deltaTime;
            }

            Scene::updateScene();

            Renderer::beginScene(m_CameraController->getCamera());

            Renderer::renderScene(Scene::getRoot());

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
        if(e.getKeycode() == KEY_ESCAPE)
            m_running = false;
        return true;
    }

    bool Application::onKeyReleased(KeyReleasedEvent &e) {
        BUBO_DEBUG_TRACE(e.toString());
        return true;
    }

}
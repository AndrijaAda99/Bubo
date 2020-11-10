#include "core/Application.h"

namespace bubo {

    Application* Application::s_appInstance = nullptr;

    Application::Application() {
        BUBO_ASSERT(!s_appInstance, "Application already created!")
        s_appInstance = this;

        m_window = std::make_unique<Window>(WindowProperties_t());
        m_window->setEventCallbackFunction(BIND_EVENT_FUNC(onEvent));
   }

    Application::~Application() = default;

    void Application::run() {

        while (m_running) {
            glClearColor(sin(glfwGetTime()), cos(glfwGetTime()), sin(glfwGetTime()), 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
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
        glViewport(0, 0, e.getWindowWidth(), e.getWindowHeight());
        return true;
    }
}
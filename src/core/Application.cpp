#include "core/Application.h"

namespace bubo {

    Application* Application::s_appInstance = nullptr;

    Application::Application() {
        BUBO_ASSERT(!s_appInstance, "Application already created!")
        s_appInstance = this;

        m_window = std::make_unique<Window>(WindowProperties_t());
   }

    Application::~Application() = default;

    void Application::run() {
        while (m_running) {
            glClearColor(sin(glfwGetTime()), cos(glfwGetTime()), sin(glfwGetTime()), 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            m_window->update();
        }
    }

}
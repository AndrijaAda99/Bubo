#include "core/Application.h"

namespace bubo {

    Application* Application::s_appInstance = nullptr;

    Application::Application() {
        BUBO_ASSERT(!s_appInstance, "Application already created!")
        s_appInstance = this;

        m_window = std::make_unique<Window>(WindowProperties_t());
        m_window->setEventCallbackFunction(BIND_EVENT_FUNC(onEvent));

        m_shaderProgram = std::make_unique<Shader>("../../res/shaders/vertex.shader", "../../res/shaders/fragment.shader");

        float vertices[] = {
                -0.5f, -0.5f, 0.0f,
                 0.5f, -0.5f, 0.0f,
                 0.0f,  0.5f, 0.0f
        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof (float), (void*) 0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);

    }

    Application::~Application() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    };

    void Application::run() {

        while (m_running) {
            glClearColor(.1f, .1f, .1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            m_shaderProgram->use();
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);
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
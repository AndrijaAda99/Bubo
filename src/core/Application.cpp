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
                 0.5f,  0.5f, 0.0f,
                 0.5f, -0.5f, 0.0f,
                -0.5f, -0.5f, 0.0f,
                -0.5f,  0.5f, 0.0f
        };

        unsigned int indices[] {
                0, 1, 3,
                1, 2, 3
        };

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        m_vertexBuffer = std::make_unique<VertexBufferObject>(vertices, sizeof (vertices));
        m_indexBuffer = std::make_unique<IndexBufferObject>(indices, sizeof (indices), 6);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof (float), (void*) 0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);

    }

    Application::~Application() {
        glDeleteVertexArrays(1, &VAO);
    }

    void Application::run() {

        while (m_running) {
            glClearColor(.1f, .1f, .1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            m_shaderProgram->bind();
            m_shaderProgram->setFloat4("u_Color",
                                       glm::vec4((sin(2*glfwGetTime()) + 1) / 2.0f,
                                                         (cos(2*glfwGetTime()) + 1) / 2.0f,
                                                         (sin(2*glfwGetTime()) + 1) / 2.0f,
                                                         1.0f));

            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, m_indexBuffer->getCount(), GL_UNSIGNED_INT, 0);
            m_shaderProgram->unbind();
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
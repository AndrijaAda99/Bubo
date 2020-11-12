#include "core/Window.h"

#include "events/MouseEvent.h"
#include "events/WindowEvent.h"
#include "events/KeyEvent.h"

namespace bubo {

    Window::Window(const WindowProperties_t &windowProperties) {
        BUBO_DEBUG_TRACE("Initializing window...");
        init(windowProperties);
        BUBO_TRACE("Window initialized!");
    }

    Window::~Window() {
        BUBO_DEBUG_TRACE("Shutting down window...");
        shutdown();
        BUBO_TRACE("Window successfully closed.");
    }

    void Window::init(const WindowProperties_t &windowProperties) {
        int success = glfwInit();
        BUBO_ASSERT(success, "Could not initialize GLFW!")

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_windowData.width = windowProperties.width;
        m_windowData.height = windowProperties.height;
        m_windowData.title = windowProperties.title;

        BUBO_INFO("Creating window: {0} ({1}, {2})", windowProperties.title,
                                                     windowProperties.width,
                                                     windowProperties.height);
        m_window = glfwCreateWindow((int) getWidth(), (int) getHeight(),
                                    m_windowData.title.c_str(), nullptr, nullptr);
        BUBO_ASSERT(m_window, "Could not create GLFW window!")

        glfwMakeContextCurrent(m_window);
        glfwSetWindowUserPointer(m_window, &m_windowData);

        success = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        BUBO_ASSERT(success, "Could not initialize GLAD!")

        glViewport(0, 0, getWidth(), getHeight());

        // TODO: Set Events
        glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height){
            WindowData_t& windowData = *(WindowData_t*) glfwGetWindowUserPointer(window);
            windowData.width = width;
            windowData.height = height;

            WindowResizeEvent event(width, height);
            windowData.callbackFunc(event);
        });

        glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window){
            WindowData_t& windowData = *(WindowData_t*) glfwGetWindowUserPointer(window);

            WindowCloseEvent event;
            windowData.callbackFunc(event);
        });

    }

    void Window::shutdown() {
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

    void Window::update() {
        glfwPollEvents();
        glfwSwapBuffers(m_window);
    }

}

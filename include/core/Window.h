#ifndef BUBO_WINDOW_H
#define BUBO_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "events/Event.h"
#include "Input.h"

namespace bubo {

    using EventCallbackFunc = std::function<void(Event&)>;

    struct WindowProperties_t {
        const std::string title;
        uint32_t width;
        uint32_t height;

        explicit WindowProperties_t(std::string title_="Bubo Project", uint32_t width_ = 800, uint32_t height_ = 600) :
                title(std::move(title_)), width(width_), height(height_) {
        };
    };

    class Window {

    public:

        explicit Window(const WindowProperties_t& windowProperties);
        ~Window();

        void update();

        GLFWwindow *getGLFWWindow() const { return m_window; }

        float getMouseX() const { return m_mouse.xPos; }
        float getMouseY() const { return m_mouse.yPos; }

        void setMouseX(float xPos) { m_mouse.xPos = xPos; }
        void setMouseY(float yPos) { m_mouse.yPos = yPos; }

        unsigned int getWidth() const { return m_windowData.width; }
        unsigned int getHeight() const { return m_windowData.height; }

        void setEventCallbackFunction(EventCallbackFunc callbackFunc_) {
            m_windowData.callbackFunc = callbackFunc_;
        }

        void setVSync(bool value);

    private:
        void init(const WindowProperties_t& windowProperties);
        void shutdown();
    private:
        struct WindowData_t {
            std::string title;
            unsigned int width, height;
            bool isVSync;
            EventCallbackFunc callbackFunc;
        };
        struct Mouse_t {
            float xPos, yPos;
        };

        GLFWwindow* m_window = nullptr;
        WindowData_t m_windowData;
        Mouse_t m_mouse;
    };

}


#endif //BUBO_WINDOW_H

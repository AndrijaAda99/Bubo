#ifndef BUBO_WINDOW_H
#define BUBO_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "events/Event.h"

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

        unsigned int getWidth() const { return m_windowData.width; }
        unsigned int getHeight() const { return m_windowData.height; }

        void setEventCallbackFunction(EventCallbackFunc callbackFunc_) {
            m_windowData.callbackFunc = callbackFunc_;
        }

        GLFWwindow *getMWindow() const { return m_window; }

    private:
        virtual void init(const WindowProperties_t& windowProperties);
        virtual void shutdown();
    private:
        struct WindowData_t {
            std::string title;
            unsigned int width, height;
            EventCallbackFunc callbackFunc;
        };

        GLFWwindow* m_window = nullptr;
        WindowData_t m_windowData;
    };

}


#endif //BUBO_WINDOW_H

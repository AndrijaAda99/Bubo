#ifndef BUBO_WINDOWEVENT_H
#define BUBO_WINDOWEVENT_H

#include "Event.h"

namespace bubo {

    class WindowCloseEvent : public Event {
    public:
        WindowCloseEvent() = default;

        SET_EVENT_CLASS_TYPE(WindowClose);
    };

    class WindowResizeEvent : public Event {
    public:
        WindowResizeEvent(int windowWidth_, int windowHeight_) : m_windowWidth(windowWidth_), m_windowHeight(windowHeight_) {}

        int getWindowWidth() const { return m_windowWidth; }
        int getWindowHeight() const { return m_windowHeight; }

        std::string toString() const override {
            std::stringstream ss;
            ss << "WindowResizeEvent: (" << getWindowWidth() << ", " << getWindowHeight() << ")";
            return ss.str();
        }

        SET_EVENT_CLASS_TYPE(WindowResize);
    private:
        int m_windowWidth;
        int m_windowHeight;
    };
}

#endif //BUBO_WINDOWEVENT_H

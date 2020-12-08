#ifndef BUBO_MOUSEEVENT_H
#define BUBO_MOUSEEVENT_H

#include "Event.h"

namespace bubo {

    enum MouseKeycode {
        BUTTON_1       = 0,
        BUTTON_2       = 1,
        BUTTON_3       = 2,
        BUTTON_4       = 3,
        BUTTON_5       = 4,
        BUTTON_6       = 5,
        BUTTON_7       = 6,
        BUTTON_8       = 7,
        BUTTON_LAST    = BUTTON_8,
        BUTTON_LEFT    = BUTTON_1,
        BUTTON_RIGHT   = BUTTON_2,
        BUTTON_MIDDLE  = BUTTON_3
    };

    class MouseMovedEvent : public Event {

    public:
        MouseMovedEvent(int mouseX_, int mouseY_) : m_mouseX(mouseX_), m_mouseY(mouseY_) {}

        int getMouseX() const { return m_mouseX; }
        int getMouseY() const { return m_mouseY; }

        std::string toString() const override {
            std::stringstream ss;
            ss << "MouseMovedEvent: (" << getMouseX() << ", " << getMouseY() << ")";
            return ss.str();
        }

        SET_EVENT_CLASS_TYPE(MouseMoved);

    private:
        int m_mouseX;
        int m_mouseY;

    };

    class MouseButtonEvent : public Event {
    public:
        MouseKeycode getMouseKeycode() const { return m_mouseKeycode; }
    protected:
        MouseButtonEvent(MouseKeycode keycode) : m_mouseKeycode(keycode) {}

        MouseKeycode m_mouseKeycode;
    };

    class MouseButtonPressedEvent : public MouseButtonEvent {
    public:
        MouseButtonPressedEvent(MouseKeycode keycode) : MouseButtonEvent(keycode) {}

        std::string toString() const override {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: (" << getMouseKeycode() << ")";
            return ss.str();
        }

        SET_EVENT_CLASS_TYPE(MouseButtonPressed);

    };

    class MouseButtonReleasedEvent : public MouseButtonEvent {
    public:
        MouseButtonReleasedEvent(MouseKeycode keycode) : MouseButtonEvent(keycode) {}

        std::string toString() const override {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: (" << getMouseKeycode() << ")";
            return ss.str();
        }
        SET_EVENT_CLASS_TYPE(MouseButtonReleased);

    };
}

#endif //BUBO_MOUSEEVENT_H

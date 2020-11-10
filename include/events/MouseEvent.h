#ifndef BUBO_MOUSEEVENT_H
#define BUBO_MOUSEEVENT_H

#include "Event.h"

namespace bubo {

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

    // TODO: Finish implementing mouse events

    class MouseButtonEvent : public Event {

    };

    class MouseButtonPressedEvent : MouseButtonEvent {

        SET_EVENT_CLASS_TYPE(MouseButtonPressed);

    };

    class MouseButtonReleasedEvent : MouseButtonEvent {

        SET_EVENT_CLASS_TYPE(MouseButtonReleased);

    };
}

#endif //BUBO_MOUSEEVENT_H

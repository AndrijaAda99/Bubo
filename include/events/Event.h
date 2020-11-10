#ifndef BUBO_EVENT_H
#define BUBO_EVENT_H

namespace bubo {

    enum class EventType {
        MouseButtonPressed, MouseButtonReleased, MouseMoved,
        KeyPressed, KeyReleased, KeyTyped,
        WindowClose, WindowResize
    };

    class Event {
    public:
        virtual ~Event() = default;

        virtual EventType getEventType() const = 0;
        virtual const char* getName() const = 0;
        virtual std::string toString() const { return getName(); }

        bool isHandled() const { return handled; }

        void setHandled(bool handled_) { Event::handled = handled_; }

    protected:
        bool handled = false;
    };

#define SET_EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
                                   EventType getEventType() const override { return GetStaticType(); }\
                                   const char *getName() const override { return #type; }

    class EventDispatcher {
    public:
        explicit EventDispatcher(Event& event) : m_event(event) {};

        template<typename T, typename F>
        bool dispatch(const F& func) {
            if (!m_event.isHandled()) {
                if (m_event.getEventType() == T::GetStaticType()) {
                    m_event.setHandled(func(static_cast<T&>(m_event)));
                    return true;
                }
            }
            return false;
        }
    private:
        Event& m_event;
    };

}

#endif //BUBO_EVENT_H

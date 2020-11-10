#ifndef BUBO_APPLICATION_H
#define BUBO_APPLICATION_H

#include "core/Window.h"
#include "events/WindowEvent.h"

namespace bubo {

    class Application {

    public:
        Application();
        ~Application();

        void run();
        void onEvent(Event& e);

        bool onWindowClose(WindowCloseEvent& e);
        static bool onWindowResize(WindowResizeEvent& e);
    private:
        std::unique_ptr<Window> m_window;
        static Application* s_appInstance;

        bool m_running = true;
    };

}

#endif //BUBO_APPLICATION_H

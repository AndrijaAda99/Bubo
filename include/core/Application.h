#ifndef BUBO_APPLICATION_H
#define BUBO_APPLICATION_H

#include "core/Window.h"

namespace bubo {

    class Application {

    public:
        Application();
        ~Application();

        void run();
    private:
        std::unique_ptr<Window> m_window;
        static Application* s_appInstance;

        bool m_running = true;
    };

}

#endif //BUBO_APPLICATION_H

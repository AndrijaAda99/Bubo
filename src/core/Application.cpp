#include "core/Application.h"

namespace bubo {

    Application* Application::s_appInstance = nullptr;

    Application::Application() {
        BUBO_ASSERT(!s_appInstance, "Application already created!");
        s_appInstance = this;
   }

    Application::~Application() {
    }

    void Application::run() {
        // TODO: Main Loop
    }

}
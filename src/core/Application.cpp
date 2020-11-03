#include "core/Application.h"


namespace bubo {

    Application::Application() {
        BUBO_INFO("Hello, App!");
        BUBO_TRACE("Trace");
        BUBO_WARN("Warn");
        BUBO_ERROR("err");
        BUBO_CRITICAL("crit");
    }

    Application::~Application() {
        BUBO_DEBUG_INFO("Bye, App!");
    }

    void Application::run() {
        // TODO: Main Loopz
    }

}
#include "core/Application.h"


int main() {
    bubo::Logger::init();
    BUBO_INFO("SPDLOG successfully initialized!");

    BUBO_TRACE("Application initializing...");
    auto *application = new bubo::Application();
    BUBO_INFO("Application successfully initialized!");

    BUBO_TRACE("Application running...");
    application->run();
    BUBO_INFO("Application stopped running!");

    BUBO_TRACE("Shutting down application...");
    delete application;
    BUBO_INFO("Application successfully closed!");

    exit(EXIT_SUCCESS);
}

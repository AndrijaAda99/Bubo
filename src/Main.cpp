#include "core/Application.h"


int main() {
    bubo::Logger::init();
    BUBO_INFO("SPDLOG successfuly initialized!");

    auto *application = new bubo::Application();
    application->run();
    delete application;

    return 0;
}

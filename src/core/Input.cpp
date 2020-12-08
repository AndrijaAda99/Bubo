#include "core/Input.h"

#include <core/Application.h>
#include <GLFW/glfw3.h>

namespace bubo {

    bool Input::isKeyPressed(Keycode keycode) {
        auto window = Application::getApplication().getWindow().getGLFWWindow();
        auto state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::isMousePressed(MouseKeycode keycode) {
        auto window = Application::getApplication().getWindow().getGLFWWindow();
        auto state = glfwGetMouseButton(window, keycode);
        return state == GLFW_PRESS;
    }

    std::pair<float, float> Input::getMousePos() {
        auto window = Application::getApplication().getWindow().getGLFWWindow();
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);
        return { (float) xPos, (float) yPos };
    }

    float Input::getMouseX() {
        return getMousePos().first;
    }

    float Input::getMouseY() {
        return getMousePos().second;
    }
}

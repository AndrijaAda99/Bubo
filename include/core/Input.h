#ifndef BUBO_INPUT_H
#define BUBO_INPUT_H

#include "events/MouseEvent.h"
#include "events/KeyEvent.h"


namespace bubo {

    class Input {

    public:
        static bool isKeyPressed(Keycode keycode);

        static bool isMousePressed(MouseKeycode keycode);

        static std::pair<float, float> getMousePos();

        static float getMouseX();
        static float getMouseY();

    };

}

#endif //BUBO_INPUT_H

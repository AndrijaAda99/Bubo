#ifndef BUBO_APPLICATION_H
#define BUBO_APPLICATION_H

#include <renderer/Texture.h>
#include <renderer/Camera.h>
#include <events/MouseEvent.h>
#include <events/KeyEvent.h>
#include <scene/Mesh.h>
#include <renderer/Material.h>
#include <scene/Scene.h>
#include "core/Window.h"
#include "renderer/Shader.h"
#include "events/WindowEvent.h"

namespace bubo {

    class Application {

    public:
        Application();
        ~Application();

        void run();
        void onEvent(Event& e);

        static Application& getApplication() { return *s_appInstance; }

        float getDeltaTime() { return m_deltaTime; }
        float getDeltaTimeMilliseconds() { return m_deltaTime * 1000; }

        Window& getWindow() { return *m_window; }

    private:
        bool onWindowClose(WindowCloseEvent& e);
        bool onWindowResize(WindowResizeEvent& e);
        bool onMouseMoved(MouseMovedEvent& e);
        bool onMousePressed(MouseButtonPressedEvent& e);
        bool onMouseReleased(MouseButtonReleasedEvent& e);
        bool onKeyPressed(KeyPressedEvent& e);
        bool onKeyReleased(KeyReleasedEvent& e);

    private:
        std::unique_ptr<Window> m_window;
        static Application* s_appInstance;

        float m_deltaTime = 1.0f / 60.0f;

        std::shared_ptr<PerspectiveCameraController> m_CameraController;

        SceneNode* m_backpack;

        bool m_running = true;

    };

}

#endif //BUBO_APPLICATION_H

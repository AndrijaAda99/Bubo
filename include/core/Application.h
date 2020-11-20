#ifndef BUBO_APPLICATION_H
#define BUBO_APPLICATION_H

#include <renderer/VertexBufferObject.h>
#include <renderer/IndexBufferObject.h>
#include <renderer/VertexArrayObject.h>
#include <renderer/Texture.h>
#include <renderer/Camera.h>
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

        bool onWindowClose(WindowCloseEvent& e);
        static bool onWindowResize(WindowResizeEvent& e);
    private:
        std::unique_ptr<Window> m_window;
        static Application* s_appInstance;

        std::shared_ptr<Shader> m_shaderProgram;
        std::shared_ptr<VertexArrayObject> m_vertexArray;
        std::shared_ptr<VertexBufferObject> m_vertexBuffer;
        std::shared_ptr<IndexBufferObject> m_indexBuffer;
        std::shared_ptr<Texture> m_texture;

        std::shared_ptr<Camera> m_camera;

        bool m_running = true;
    };

}

#endif //BUBO_APPLICATION_H

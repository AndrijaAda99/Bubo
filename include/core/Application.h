#ifndef BUBO_APPLICATION_H
#define BUBO_APPLICATION_H

#include <renderer/VertexBufferObject.h>
#include <renderer/IndexBufferObject.h>
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

        unsigned int VAO, EBO;
        std::unique_ptr<Shader> m_shaderProgram;
        std::unique_ptr<VertexBufferObject> m_vertexBuffer;
        std::unique_ptr<IndexBufferObject> m_indexBuffer;

        bool m_running = true;
    };

}

#endif //BUBO_APPLICATION_H

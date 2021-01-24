cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        Bubo
        Main.cpp
        core/Application.cpp
        core/Logger.cpp
        core/Window.cpp
        core/Input.cpp
        renderer/Shader.cpp
        renderer/VertexBufferObject.cpp
        renderer/IndexBufferObject.cpp
        renderer/VertexArrayObject.cpp
        renderer/Framebuffer.cpp
        renderer/Renderer.cpp
        renderer/Texture.cpp
        renderer/Camera.cpp
        renderer/Material.cpp
        scene/Mesh.cpp
        scene/ModelLoader.cpp
        scene/Scene.cpp
        scene/Skybox.cpp
        scene/Lights.cpp
)

target_precompile_headers(
        Bubo
        PRIVATE
            <iostream>
            <memory>
            <utility>
            <algorithm>
            <functional>
            <string>
            <sstream>
            <array>
            <vector>
            <map>
            <unordered_map>
            <unordered_set>
            ../include/core/Config.h
            ../include/core/Logger.h
            ../include/core/Assert.h
        )

target_link_libraries(
        Bubo
        PRIVATE
            assimp
            spdlog::spdlog
            glad
            glfw
            OpenGL::GL
            pthread
            X11
            Xrandr
            Xi
            dl
        )

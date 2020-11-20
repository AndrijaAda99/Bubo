cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        Bubo
            Main.cpp
            core/Application.cpp
            core/Logger.cpp
            core/Window.cpp
            renderer/Shader.cpp
            renderer/VertexBufferObject.cpp
            renderer/IndexBufferObject.cpp
            renderer/VertexArrayObject.cpp
            renderer/Renderer.cpp
            renderer/Texture.cpp
        renderer/Camera.cpp)

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
            <unordered_map>
            <unordered_set>
            ../include/core/Config.h
            ../include/core/Logger.h
            ../include/core/Assert.h
        )

target_link_libraries(
        Bubo
        PUBLIC
            spdlog
            glad
            glfw
            OpenGL::GL
            pthread
            X11
            Xrandr
            Xi
            dl
        )

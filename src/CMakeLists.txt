cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD 14)

add_executable(Bubo Main.cpp core/Application.cpp core/Logger.cpp)

target_precompile_headers(Bubo
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
            ../include/core/Logger.h
        )

target_link_libraries(Bubo spdlog)

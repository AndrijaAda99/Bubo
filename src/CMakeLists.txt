cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD 14)

add_executable(Bubo Main.cpp core/Application.cpp core/Logger.cpp ../include/core/Config.h)

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
            ../include/core/Config.h
            ../include/core/Logger.h
            ../include/core/Assert.h
        )

target_link_libraries(Bubo spdlog)

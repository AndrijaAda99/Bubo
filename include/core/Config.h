#ifndef BUBO_CONFIG_H
#define BUBO_CONFIG_H

#define DEBUG_MODE
// #define DISPLAY_FPS
#define VSYNC

#define BIND_EVENT_FUNC(func) [this](auto&&... args) -> decltype(auto) { return this->func(std::forward<decltype(args)>(args)...); }
#define STB_IMAGE_IMPLEMENTATION

#define POSTPROCESSING_POSTERIZATION

#endif //BUBO_CONFIG_H

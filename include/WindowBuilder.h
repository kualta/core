#ifndef CORE_WINDOWBUILDER_H
#define CORE_WINDOWBUILDER_H

#include "Window.h"


class WindowBuilder {

public:
    /// Returns id of the created window on success
    static uint32_t SpawnWindow(const std::string& title, const core::Rect& rect);
    static uint32_t SpawnWindow(const std::string& title, const core::Vector2& pos, int width, int height);
    static uint32_t SpawnWindow(const std::string& title, const core::Vector2& pos, const core::Vector2& res);
};


#endif //CORE_WINDOWBUILDER_H

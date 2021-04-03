#ifndef CORE_WINDOWBUILDER_H
#define CORE_WINDOWBUILDER_H

#include "Essential.h"

namespace core {

class WindowBuilder : public ObjectId, public Singleton<WindowBuilder> {

public:
    /// Returns id of the created window on success
    static uint32_t SpawnWindow(const std::string& title, const Rect& rect);
    static uint32_t SpawnWindow(const std::string& title, const Vector2& pos, int width, int height);
    static uint32_t SpawnWindow(const std::string& title, const Vector2& pos, const Vector2& res);
};

} // namespace


#endif //CORE_WINDOWBUILDER_H

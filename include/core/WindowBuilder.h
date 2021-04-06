#ifndef CORE_WINDOWBUILDER_H
#define CORE_WINDOWBUILDER_H

#include "Essential.h"
#include "ObjectId.h"
#include "Singleton.h"

namespace core {

class WindowBuilder : public ObjectId, public Singleton<WindowBuilder> {

public:
    /// Returns id of the created window on success
    static uint32_t SpawnWindow(const std::string& title, const Rect& rect);
};

} // namespace core


#endif //CORE_WINDOWBUILDER_H

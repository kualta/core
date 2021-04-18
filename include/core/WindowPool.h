#ifndef CORE_WINDOWPOOL_H
#define CORE_WINDOWPOOL_H

#include "Essential.h"
#include "Singleton.h"
#include "Object.h"
#include <memory>
#include <vector>

namespace core {

class WindowPool : public Singleton<WindowPool>, public Object {
public:

    ~WindowPool();

    /**
     * Adds pointer to window to the windows pool
     */
    static void RegisterWindow(const std::shared_ptr<core::Window> &windowPtr);

protected:
    static std::vector<std::shared_ptr<Window>> windowPool;
};

} // namespace core


#endif //CORE_WINDOWPOOL_H

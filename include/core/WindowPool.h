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

    /**
     * Adds pointer to window to the windows pool
     */
    static void AddWindowToPool(const std::shared_ptr<core::Window> &windowPtr);

    /**
     * Creates a pointer to the window and adds it to the windows pool
     */
    static void AddWindowToPool(const core::Window& window);

    /**
     * Erases all elements from windows pool vector
     */
    static void DestroyAll();

protected:
    static std::vector<std::shared_ptr<Window>> windowsPool;
};

} // namespace core


#endif //CORE_WINDOWPOOL_H

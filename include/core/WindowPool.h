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
    static void AddWindowToPool(const std::shared_ptr<core::Window> &windowPtr);
    static void AddWindowToPool(const core::Window& window);

    static void DestroyAll();

protected:
    static std::vector<std::shared_ptr<Window>> windowsPool;
};


}


#endif //CORE_WINDOWPOOL_H

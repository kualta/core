#ifndef CORE_WINDOWPOOL_H
#define CORE_WINDOWPOOL_H

#include <vector>
#include <memory>
#include "Singleton.h"
#include "Window.h"
#include "ObjectId.h"


namespace core {


class WindowPool : public Singleton<WindowManager>, public ObjectId {

public:
    static void AddWindowToPool(const std::shared_ptr<core::Window>& windowPtr);
    static void AddWindowToPool(const core::Window& window);

    static void DestroyAll();

protected:
    static std::vector<std::shared_ptr<Window>> windowsPool;
};


}


#endif //CORE_WINDOWPOOL_H

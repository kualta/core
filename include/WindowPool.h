#ifndef CORE_WINDOWPOOL_H
#define CORE_WINDOWPOOL_H

#include <memory>
#include <list>

#include "Singleton.h"
#include "ObjectId.h"
#include "Window.h"


namespace core {


class WindowPool : public Singleton<WindowPool>, public ObjectId {

public:
    static void AddWindowToPool(const std::shared_ptr<core::Window>& windowPtr);
    static void AddWindowToPool(const core::Window& window);

    static void DestroyAll();

protected:
    static std::list<std::shared_ptr<Window>> windowsPool;
};


}


#endif //CORE_WINDOWPOOL_H

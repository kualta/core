#ifndef CORE_WINDOWMANAGER_H
#define CORE_WINDOWMANAGER_H

#include "Singleton.h"
#include "Window.h"
#include "ObjectId.h"

#include <vector>
#include <memory>


namespace core {

class WindowManager : public Singleton<WindowManager>, public ObjectId {
public:
    WindowManager();

    static void AddWindowToPool(const Window& window);
    static void AddWindowToPool(const std::shared_ptr<Window>& windowPtr);

    void DestroyAll();

protected:
    static std::vector<std::shared_ptr<Window>> windowsPool;

private:

};


}


#endif //CORE_WINDOWMANAGER_H

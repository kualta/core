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

    /// Returns id of the created window on success
    static uint32_t SpawnWindow(const std::string& title, const Rect& rect);
    static uint32_t SpawnWindow(const std::string& title, const Vector2& pos, int width, int height);
    static uint32_t SpawnWindow(const std::string& title, const Vector2& pos, const Vector2& res);
    static void AddWindowToPool(const Window& window);
    static void AddWindowToPool(const std::shared_ptr<Window>& windowPtr);

    void DestroyAll();

protected:
    static std::vector<std::shared_ptr<Window>> windowsPool;

private:

};


}


#endif //CORE_WINDOWMANAGER_H

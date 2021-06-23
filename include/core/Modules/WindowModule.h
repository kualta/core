#ifndef CORE_MODULE_WINDOW_H
#define CORE_MODULE_WINDOW_H

#include <core/IModule.h>
#include <core/Pool.h>

#include <core/Window.h>
#include <core/WindowBuilder.h>
#include <core/BgfxWindowRenderer.h>

#include <memory>

namespace core {

class WindowModule : public IModule {
public:
    WindowModule();
    ~WindowModule();

    void Tick() override;

    Pool<Window> windowPool;
};

}

#endif //CORE_MODULE_WINDOW_H

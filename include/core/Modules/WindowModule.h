#ifndef CORE_MODULE_WINDOW_H
#define CORE_MODULE_WINDOW_H

#include <core/IModule.h>
#include <core/Pool.h>

#include <core/Window.h>
#include <core/WindowBuilder.h>
#include <core/Modules/BgfxWindowRenderer.h>
#include <core/Modules/IRenderModule.h>

#include <memory>

namespace core {

class WindowModule : public IModule {
public:
    WindowModule(IRenderModule* rModule);
    ~WindowModule();

    void Tick() override;

    Pool<Window>   windowPool;
    IRenderModule* renderModule;
};

}

#endif //CORE_MODULE_WINDOW_H

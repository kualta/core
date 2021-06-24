#ifndef CORE_IRENDERMODULE_H
#define CORE_IRENDERMODULE_H

#include <core/IModule.h>
#include <core/IWindowRenderer.h>

namespace core {

class IRenderModule : public IModule {
public:

    IWindowRenderer* windowRenderer;

protected:
    explicit IRenderModule(const string& moduleName = "ERR",
                           const string& type       = "ERR",
                           IWindowRenderer* wRend   = nullptr);

    virtual void Frame() = 0;

    void Tick() override;

    const string renderType;

};

}

#endif //CORE_IRENDERMODULE_H

#ifndef CORE_IRENDERMODULE_H
#define CORE_IRENDERMODULE_H

#include <core/IModule.h>
#include <core/IWindowRenderer.h>
#include <core/Modules/InputModule.h>

namespace core {

class IRenderModule : public IModule {
public:

    IWindowRenderer* windowRenderer;
    InputModule*     inputModule;

protected:
    IRenderModule(const string &moduleName, IWindowRenderer *windowRenderer);

    virtual void Frame() = 0;

private:

    void Tick() override;

};

}

#endif //CORE_IRENDERMODULE_H

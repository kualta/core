#ifndef CORE_IRENDERMODULE_H
#define CORE_IRENDERMODULE_H

#include <core/IModule.h>

namespace core {

class IRenderModule : public IModule {
protected:
    explicit IRenderModule(const string& moduleName = "ERR",
                           string type = "ERR");

    virtual void Frame() = 0;

    void Tick() override;

    const string renderType;

};

}

#endif //CORE_IRENDERMODULE_H

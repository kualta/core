#ifndef CORE_ENGINEMODULE_H
#define CORE_ENGINEMODULE_H

#include <core/IModule.h>
#include <core/EngineLoop.h>

#include <memory>

namespace core {

class EngineModule : public IModule {
public:
    explicit EngineModule(InputModule* input);

    void Start() override;

    int32_t Main();

protected:

    std::unique_ptr<EngineLoop> engineLoop;
    InputModule*                inputModule;

};


}


#endif //CORE_ENGINEMODULE_H

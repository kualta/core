#ifndef CORE_ENGINEMODULE_H
#define CORE_ENGINEMODULE_H

#include <core/IModule.h>
#include <core/EngineLoop.h>

#include <memory>

namespace core {

class EngineModule : public IModule {
public:
    explicit EngineModule(InputModule* input);
    ~EngineModule();

    void Update() override;

    int32_t Main();

protected:
    std::unique_ptr<EngineLoop> mainLoop;
    InputModule*                Input;

};


}


#endif //CORE_ENGINEMODULE_H

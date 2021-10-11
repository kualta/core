#ifndef CORE_ENGINEMODULE_H
#define CORE_ENGINEMODULE_H

#include <core/IModule.h>
#include <core/Engine/EngineLoop.h>

#include <memory>

namespace core {

class EngineModule : public IModule {
public:
    explicit EngineModule(InputModule* input);

    void Start() override;

    static void SetTargetFrameRate(int32_t fps);
    static int32_t GetTargetFrameRate();

    int32_t Main();

    static constexpr int32_t fixedTickRate = 30;   // < Target ticks per second

protected:

    static int32_t              targetFrameRate; // < Target frames per second

    std::unique_ptr<EngineLoop> engineLoop;
    InputModule*                inputModule;

};


}


#endif //CORE_ENGINEMODULE_H

#ifndef CORE_ENGINEMODULE_H
#define CORE_ENGINEMODULE_H

#include <core/IModule.h>
#include <core/EngineLoop.h>

#include <memory>

namespace core {

class EngineModule : public IModule {
public:
    EngineModule();
    ~EngineModule();

    int32_t Main();

protected:

    std::unique_ptr<EngineLoop> mainLoop;
private:

};


}


#endif //CORE_ENGINEMODULE_H

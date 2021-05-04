#ifndef CORE_INPUTMODULE_H
#define CORE_INPUTMODULE_H

#include <core/IModule.h>

#include <memory>

namespace core {


class InputModule : public IModule {
public:
    InputModule();
    ~InputModule();

    bool GetAnyKey();

    bool exitRequested { false };

protected:

private:

};


}


#endif //CORE_INPUTMODULE_H

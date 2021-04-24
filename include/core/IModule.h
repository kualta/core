#ifndef CORE_IMODULE_H
#define CORE_IMODULE_H

namespace core {

enum MOD_STATE {

};

class IModule {
public:

    virtual MOD_STATE Start() = 0;
    virtual MOD_STATE Stop() = 0;

};

}

#endif //CORE_IMODULE_H

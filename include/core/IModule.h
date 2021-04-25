#ifndef CORE_IMODULE_H
#define CORE_IMODULE_H

#include "Essential.h"

namespace core {

enum M_STATUS {
    C_SUCCESS = 0,
    C_STARTUP_FAILED,
    C_UNRESOLVED_DEPENDENCY,
    C_INVALID_INPUT,
};
struct StatusDesc {
    M_STATUS code;
    string message;
} statusDesc[] = {
        { C_SUCCESS, "No error" },
        { C_STARTUP_FAILED, "Could not start module" },
        { C_UNRESOLVED_DEPENDENCY, "Module depedencies were not resolved properly" },
        { C_INVALID_INPUT, "Invalid input" },
};

class IModule {
public:

    virtual M_STATUS Start() = 0;
    virtual M_STATUS Stop() = 0;

};

}

#endif //CORE_IMODULE_H

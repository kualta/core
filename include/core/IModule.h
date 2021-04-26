#ifndef CORE_IMODULE_H
#define CORE_IMODULE_H

#include <utility>

#include "Essential.h"
#include "Logger.h"

namespace core {

enum M_STATUS {
    C_SUCCESS = 0,
    C_ERR_STARTUP_FAILED,
    C_ERR_UNRESOLVED_DEPENDENCY,
    C_ERR_INVALID_INPUT,
};
struct StatusDesc {
    M_STATUS code;
    string message;
} statusDesc[] = {
        {C_SUCCESS,                   "No error" },
        {C_ERR_STARTUP_FAILED,        "Could not start module" },
        {C_ERR_UNRESOLVED_DEPENDENCY, "Module depedencies were not resolved properly" },
        {C_ERR_INVALID_INPUT,         "Invalid input" },
};

class IModule {
public:
    explicit IModule(string name = "Unnamed") : moduleName(std::move(name) + "module") { };

    virtual M_STATUS Start() = 0;
    virtual M_STATUS Stop() = 0;

    string moduleName;

};

}

#endif //CORE_IMODULE_H

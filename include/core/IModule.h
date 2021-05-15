/*
 * This is a stand-alone header file, no IModule.cpp is presented.
 */
#ifndef CORE_IMODULE_H
#define CORE_IMODULE_H

#include <utility>

#include "Essential.h"
#include "Instantiable.h"
#include "Logger.h"

namespace core {

enum M_STATUS {
    C_SUCCESS = 0,
    C_ERR_STARTUP_FAILED,
    C_ERR_UNRESOLVED_DEPENDENCY,
    C_ERR_INVALID_INPUT,
};

class IModule : public Instantiable<IModule>, public Object {
public:

    virtual void Update() = 0;

    objectTag tag { GENERAL };

protected:
    explicit IModule(string moduleName = "Unnamed", objectTag moduleTag = GENERAL)
    : Object(std::move(moduleName) + " module"), tag(moduleTag) {
        Logger::Log(INFO, tag) << "Initialized " << name;
    };
    ~IModule() {
        Logger::Log(INFO, tag) << "Destroyed " << name;
    }

};


}

#endif //CORE_IMODULE_H

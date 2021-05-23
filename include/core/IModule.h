/*
 * This is a stand-alone header file, no IModule.cpp is presented.
 */
#ifndef CORE_IMODULE_H
#define CORE_IMODULE_H

#include "Essential.h"
#include "Instantiable.h"
#include "ITicker.h"
#include "Logger.h"

#include <utility>

namespace core {

enum M_STATUS {
    C_SUCCESS = 0,
    C_ERR_STARTUP_FAILED,
    C_ERR_UNRESOLVED_DEPENDENCY,
    C_ERR_INVALID_INPUT,
};

class IModule : public Instantiable<IModule>, public Object, public ITicker {
public:

    objectTag tag { GENERAL };

protected:
    explicit IModule(string moduleName = "Unnamed", objectTag moduleTag = GENERAL)
    : Object(std::move(moduleName) + " module"), tag(moduleTag) {
        Logger::Log(tag, INFO) << "Initialized " << name;
    };
    ~IModule() {
        Logger::Log(tag, INFO) << "Destroyed " << name;
    }

};


}

#endif //CORE_IMODULE_H

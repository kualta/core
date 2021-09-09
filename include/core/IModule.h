/*
 * This is a stand-alone header file, no IModule.cpp is presented.
 */
#ifndef CORE_IMODULE_H
#define CORE_IMODULE_H

#include "Essential.h"
#include "Instantiable.h"
#include "ITicker.h"
#include "Logger.h"
#include "ObjectTag.h"

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

    /**
     * Called after main loop exit is requested
     */
    virtual void Stop() { };

    objectTag tag { GENERAL };

protected:
    explicit IModule(const string& moduleName = "Unnamed", objectTag moduleTag = GENERAL)
    : Object(moduleName + " module"), tag(moduleTag)
    {
        Logger::Log(tag, INFO) << "Initialized " << name;
    };
    ~IModule() {
        Logger::Log(tag, INFO) << "Destroyed " << name;
    }

};


}

#endif //CORE_IMODULE_H

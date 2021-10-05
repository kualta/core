/*
 * This is a stand-alone header file. No IModule.cpp is presented.
 */
#ifndef CORE_IMODULE_H
#define CORE_IMODULE_H

#include "Essentials.h"
#include "Instantiable.h"
#include "ObjectTag.h"
#include "ITicker.h"
#include "Logger.h"

#include <utility>

namespace core {

class IModule : public Instantiable<IModule>, public Object, public ITicker {
public:


    ObjectTag tag {GENERAL };

protected:
    explicit IModule(const string& moduleName = "Unnamed", ObjectTag moduleTag = GENERAL)
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

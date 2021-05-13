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

protected:
    explicit IModule(string name = "Unnamed") : Object(std::move(name) + " module") { };

};


}

#endif //CORE_IMODULE_H

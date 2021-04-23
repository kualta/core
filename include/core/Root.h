#ifndef CORE_ROOT_H
#define CORE_ROOT_H

#include "Essential.h"
#include "Singleton.h"
#include "Object.h"
#include "Pool.h"

#include <memory>

namespace core {

class Root : public Singleton<Root>, public Object {
public:

    /**
     *  Initializes the engine
     */
    Root();

    /**
     *  Uninitializes the engine
     */
    ~Root();

};

}


#endif //CORE_ROOT_H

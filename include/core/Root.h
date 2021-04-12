#ifndef CORE_ROOT_H
#define CORE_ROOT_H

#include "Essential.h"
#include "Singleton.h"
#include "Object.h"

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

    std::unique_ptr<Logger> logger;
    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<WindowPool> windowPool;
};


}


#endif //CORE_ROOT_H

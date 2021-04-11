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

    const std::unique_ptr<Logger> &GetLogManager() const;
    const std::unique_ptr<RenderManager> &GetRenderManager() const;

protected:
    std::unique_ptr<Logger> logManager;
    std::unique_ptr<WindowPool> windowPool;
    std::unique_ptr<RenderManager> renderManager;

private:
};


}


#endif //CORE_ROOT_H

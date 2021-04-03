#ifndef CORE_ROOT_H
#define CORE_ROOT_H

#include "Essential.h"

namespace core {


class Root : public Singleton<Root>, public ObjectId {

public:
    Root();
    ~Root();

    const std::unique_ptr<LogManager> &GetLogManager() const;
    const std::unique_ptr<RenderManager> &GetRenderManager() const;

protected:
    std::unique_ptr<LogManager> logManager;
    std::unique_ptr<WindowPool> windowPool;
    std::unique_ptr<RenderManager> renderManager;

private:
};


}


#endif //CORE_ROOT_H

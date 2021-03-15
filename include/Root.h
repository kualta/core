#ifndef CORE_ROOT_H
#define CORE_ROOT_H

#include <memory>
#include "core.h"
#include "Singleton.h"

class Root : public Singleton<Root> {

public:

protected:
    std::vector<std::shared_ptr<Window>> windowsPool_;

    std::unique_ptr<LogManager> logManager_;

private:

};


#endif //CORE_ROOT_H

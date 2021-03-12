#ifndef INTERFACERS_LIB_CORE_INCLUDE_ROOT_H_
#define INTERFACERS_LIB_CORE_INCLUDE_ROOT_H_

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


#endif //INTERFACERS_LIB_CORE_INCLUDE_ROOT_H_

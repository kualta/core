#ifndef CORE_WINDOWMANAGER_H
#define CORE_WINDOWMANAGER_H

#include "Singleton.h"
#include "Window.h"

#include <vector>
#include <memory>


namespace core {

// TODO: TO BE IMPLEMENTED
class WindowManager : public Singleton<WindowManager> {
public:
    /// Returns uint32_t id of the created window on success,
    ///         0 if creation failed
    uint32_t CreateWindow();

protected:
    std::vector<std::shared_ptr<Window>> windowsPool_;

private:

};


}


#endif //CORE_WINDOWMANAGER_H

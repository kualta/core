#ifndef CORE_MODULE_WINDOW_H
#define CORE_MODULE_WINDOW_H

namespace core {

class WindowModule : public Module {

    WindowModule();

    std::unique_ptr<Pool<Window>> windowPool;
};

}

#endif //CORE_MODULE_WINDOW_H

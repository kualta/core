#include "core.h"

#include "bgfx/bgfx.h"
#include <iostream>

namespace core {


    void init() {

        bgfx::init();

        std::cout << "- Core initialization complete -" << std::endl;
    }


}

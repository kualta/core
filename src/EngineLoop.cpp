#include <core/EngineLoop.h>

namespace core {


int32_t EngineLoop::Enter() {

    while ( !exitRequested ) {


    }
    Logger::Log(INFO, INTERNAL) << "Quit main loop";

}

}
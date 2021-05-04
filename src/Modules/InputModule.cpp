#include <core/Modules/InputModule.h>

namespace core {


InputModule::InputModule() {

    Logger::Log(INFO, INPUT) << "Initialized Input module";
}
InputModule::~InputModule() {
    Logger::Log(INFO, INPUT) << "Destroyed Input module";

}


}
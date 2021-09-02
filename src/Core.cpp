#include <core/Core.h>

#include <memory>

namespace core {

using ModuleMap = TypeMap<std::unique_ptr<IModuleContainer>>;
ModuleMap Core::moduleMap { };

Core::Core(Core &&other) {
    *this = std::move(other);
}
IModule* Core::GetModule(int32_t id) {
    auto it = moduleMap.find(id);
    if ( it == moduleMap.end() ) {
        Logger::Log(GENERAL, ERR) << "Module with id " << id << " not found!";
        throw std::runtime_error("Module with id " + std::to_string(id) + " not found!");
    }
    return static_cast<IModule*>(it->second->Get());
};
Core &Core::operator=(Core &&other) noexcept {
    return *this;
}
Core::~Core() {
    Logger::Log(INTERNAL, INFO) << "### Core destruction started ###";
}

}
#include <core/Core.h>

#include <memory>

namespace core {

using ModuleMap = TypeMap<std::unique_ptr<IModuleContainer>>;
ModuleMap Core::moduleMap { };

Core::Core(Core &&other) {
    *this = std::move(other);
}
Core &Core::operator=(Core &&other) noexcept {
    return *this;
}

}
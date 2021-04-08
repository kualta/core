#ifndef INTERFACERS_ENTITY_H
#define INTERFACERS_ENTITY_H

#include <memory>
#include <vector>
#include "Essential.h"
#include "Object.h"

namespace core {

class Entity : public Object {
public:

protected:
    std::vector<std::unique_ptr<Component>> componentList;

private:
};

} // namespace core



#endif //INTERFACERS_ENTITY_H

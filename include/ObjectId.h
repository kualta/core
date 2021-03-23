#ifndef CORE_OBJECTID_H
#define CORE_OBJECTID_H

#include <cstdint>

namespace core {

/// Every countable object class _must_ inherit from this. This includes all singleton classes,
/// since there could be multiple core::Root objects. First core::Root always have id of 1.
class ObjectId {

public:
    uint32_t GetId() const { return id; };

protected:
    // FIXME: Current implementation is not thread-safe
    ObjectId() : id(++objectCounter) {};

private:
    static uint32_t objectCounter;
    uint32_t id;

};


}
#endif //CORE_OBJECTID_H

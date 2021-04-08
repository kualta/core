#ifndef CORE_OBJECTID_H
#define CORE_OBJECTID_H

#include "Essential.h"

namespace core {

/**
 *  Every countable class inherits from Object. This includes all singleton classes,
 *  since there could be multiple core::Root objects. First core::Root always has an id of 1.
 */
class Object {

public:
    string name;
    uint32_t GetId() const { return id; };

    static void Destroy(Object obj);

protected:
    // FIXME: Current implementation is not thread-safe
    Object() : id(++objectCounter) {  };

private:
    static uint32_t objectCounter;
    uint32_t id;

};

}
#endif //CORE_OBJECTID_H

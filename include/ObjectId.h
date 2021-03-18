///
/// This is a stand-alone header file, no ObjectId.cpp is presented.
///
#ifndef CORE_OBJECTID_H
#define CORE_OBJECTID_H

#include <cstdint>

namespace core {


class ObjectId {

public:
    static uint32_t objectCounter { 1 };
    uint32_t id;

protected:
    // FIXME: Current implementation is not thread-safe (I suppose?)
    ObjectId() : id(++objectCounter) {};
};


}
#endif //CORE_OBJECTID_H

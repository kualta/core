#ifndef CORE_OBJECTID_H
#define CORE_OBJECTID_H

#include "Essential.h"

#include <utility>

namespace core {

/**
 *  Base class of every countable class
 *  @note All singleton classes inherit from this as well.
 */
class Object {
public:

    /**
     * @return uint32_t ID of an object
     */
    uint32_t GetId() const;

    /**
     * @return string containing name and ID of this object
     * @details format: "name" ID(123)
     */
    string GetInfo() const;

    bool operator==(const Object &rhs) const;
    bool operator!=(const Object &rhs) const;

    string name;

protected:
    // FIXME: Current id implementation is not thread-safe
    explicit Object(string name = "");
    ~Object();

private:
    static uint32_t objectCounter;
    uint32_t id;
};

} // namespace core

#endif //CORE_OBJECTID_H

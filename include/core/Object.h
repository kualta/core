#ifndef CORE_OBJECTID_H
#define CORE_OBJECTID_H

#include <utility>

#include "Essential.h"

namespace core {

/**
 *  Base class of every countable class
 *  @details All singleton classes inherit from this as well, since there could be multiple core::Root objects.
 *  @details First core::Root always has an id of 1.
 */
class Object {
public:

    /**
     * @return uint32_t ID of an object
     */
    uint32_t GetId() const;

    /**
     * Destroys this object
     */
    virtual void Destroy();

    /**
     * Destroys object
     * @param obj - Object to destroy
     */
    static void Destroy(Object& obj);

    bool operator==(const Object &rhs) const;
    bool operator!=(const Object &rhs) const;

    string name;

protected:
    // FIXME: Current id implementation is not thread-safe
    explicit Object(string name = "") : id(++objectCounter), name(std::move(name)) {  };

private:
    static uint32_t objectCounter;
    uint32_t id;
};

} // namespace core

#endif //CORE_OBJECTID_H

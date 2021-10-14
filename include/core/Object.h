#ifndef CORE_OBJECTID_H
#define CORE_OBJECTID_H

#include "Essentials.h"

#include <utility>
#include <atomic>

namespace core {

/**
 *  Base class of every countable class
 *  @note All singleton classes inherit from this as well.
 */
class Object {
public:
    /** Copying is not allowed */
    Object(const Object&) = delete;

    /** Move constructor */
    Object(Object&&) = default;

    /**
     * @return uint32_t ID of an object
     */
    uint32_t GetId() const;

    /**
     * @return string containing name and ID of this object
     * @details format: "name" ID(123)
     */
    string GetInfo() const;

    /** Copying is not allowed */
    Object& operator=(const Object&) = delete;

    /** Move assignment */
    Object& operator=(Object&&) noexcept = default;

    bool operator==(const Object &rhs) const;
    bool operator!=(const Object &rhs) const;


protected:
    explicit Object(string name = "");
    virtual ~Object();

    string name;

private:
    static std::atomic<uint32_t> objectCounter;
    uint32_t id;
};

} // namespace core

#endif //CORE_OBJECTID_H

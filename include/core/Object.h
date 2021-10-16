#ifndef CORE_OBJECTID_H
#define CORE_OBJECTID_H

#include "Essentials.h"

#include <utility>
#include <atomic>

namespace core {

/**
 *  Base class of every countable class
 */
class Object {
public:
    /** Move constructor */
    Object(Object&& other) noexcept;

    /** Copying is not allowed */
    Object(const Object&) = delete;

    /**
     * @return std::string Name of the object
     */
    const string& GetName();

    /**
     * @return uint32_t ID of the object
     */
    uint32_t GetId() const;

    /**
     * @return string with name and ID of the object
     * @details format: "name" ID(123)
     */
    string GetInfo() const;

    /** Copying is not allowed */
    Object& operator=(const Object&) = delete;

    /** Move assignment */
    Object& operator=(Object&& other) noexcept;

    bool operator==(const Object &rhs) const;
    bool operator!=(const Object &rhs) const;

protected:

    explicit Object(string name = "") noexcept;
    virtual ~Object();

    string name;

private:

    static std::atomic<uint32_t> objectCounter;

    uint32_t id;

};

} // namespace core

#endif //CORE_OBJECTID_H

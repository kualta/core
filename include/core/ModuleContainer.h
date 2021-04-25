#ifndef CORE_MODULECONTAINER_H
#define CORE_MODULECONTAINER_H

#include "Essential.h"

namespace core {


class abstract_instance_container {
public:
    virtual ~abstract_instance_container() = default;

    // The type_map holding the instance container has the
    // type information, so we'll be able to safely convert
    // the pointer from void* back to its original type.
    void* get() { return raw_ptr_; }

    abstract_instance_container(abstract_instance_container &&other) {
        *this = std::move(other);
    }

    abstract_instance_container& operator=(abstract_instance_container &&other) {
        raw_ptr_ = other.raw_ptr_;
        other.raw_ptr_ = nullptr;
        return *this;
    }

protected:
    explicit abstract_instance_container(void *raw_ptr)
            : raw_ptr_(raw_ptr) {}

private:
    void *raw_ptr_;
};


template <class T, class Deleter>
class instance_container : public abstract_instance_container {
public:
    ~instance_container() override = default;

    explicit instance_container(std::unique_ptr<T, Deleter> &&p) :
            abstract_instance_container(p.get()),
            pointer_(std::move(p)) {}

    instance_container(instance_container &&other) {
        *this = std::move(other);
    }

    instance_container& operator=(instance_container &&other) {
        pointer_ = std::move(other);
        abstract_instance_container::operator=(std::move(other));
        return *this;
    }

private:
    std::unique_ptr<T, Deleter> pointer_;
};


}

#endif //CORE_MODULECONTAINER_H

#ifndef CORE_NODE_H
#define CORE_NODE_H

#include "Essential.h"

namespace core {

template <typename T> class Node {
public:
    Node() : parent(nullptr) {}
    Node(T* parent) : parent(parent) {}

    void SetParent(T* newParent);
    T* GetChild(int32_t index);

protected:
    uint32_t AddChild(T *c);
    void  DeleteChild(T *c);

private:
    T* parent { nullptr };
    std::vector<T*> children {  };
};

}

#include "Node.tpp"


#endif //CORE_NODE_H

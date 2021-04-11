/**
 * This is a stand-alone header file,
 * No Node.cpp is presented. Check Node.tpp for template implementations
 */
#ifndef CORE_NODE_H
#define CORE_NODE_H

#include "Essential.h"

namespace core {

template <typename T> class Node {
public:
    Node() { }

    /**
     *  @brief Get child by index
     *  @note Children indexes are not consistent
     */
    T* GetChild(int32_t i);

    virtual void SetParent(T* newParent) = 0;
    static void SetRoot(T* r);

protected:
    void AddChild(T* c);
    void DeleteChild(T* c);

    /**
     *  Pointer to root node.
     *  @warning Initialized in core::Root constructor, before that is nullptr.
     */
    static T* root;

    T* parent { nullptr };
    std::vector<T*> children {  };
};

}

#include "Node.tpp"


#endif //CORE_NODE_H

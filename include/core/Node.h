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
    Node(T* parent) {
        static_assert(std::is_base_of<Node<T>, T>::value, "Type T must inherit from Node<T>");
        SetParent(parent);
    }

    /**
     *  @brief Get child by index
     *  @note Children indexes are not consistent
     */
    T* GetChild(int32_t i);

    void SetParent(T* newParent);
    static void SetRoot(T* r);

protected:
    void AddChild(Node<T>* c);
    void DeleteChild(Node<T>* c);

    /**
     *  Pointer to root node.
     *  @warning Initialized in core::Root constructor, before that is nullptr.
     */
    static T* root;

    T* parent { nullptr };
    std::vector<Node<T>*> children {  };
};

} // namespace core

#include "Node.tpp"


#endif //CORE_NODE_H

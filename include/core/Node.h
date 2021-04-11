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
    Node() {
        SetParent(root);
    }
    Node(Node<T>* parent) {
        SetParent(parent);
    }

    /**
     *  @brief Get child by index
     *  @note Children indexes are not consistent
     */
    T* GetChild(int32_t i);

    void SetParent(Node<T>* newParent);
    static void SetRoot(Node<T> *r);

protected:
    void AddChild(Node<T>* c);
    void DeleteChild(Node<T>* c);

    /**
     *  Pointer to root node.
     *  @warning Initialized in core::Root constructor, before that is nullptr.
     */
    static Node<T>* root;

private:
    Node<T>* parent { nullptr };
    std::vector<Node<T>*> children {  };
};

}

#include "Node.tpp"


#endif //CORE_NODE_H

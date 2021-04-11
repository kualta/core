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
    Node() {}
    Node(T* parent) : parent(parent) {}

    void SetParent(T* newParent);

    /**
     *  @brief Get child by index
     *  @note Children indexes are not consistent
     */
    T* GetChild(int32_t i);
    static void SetRoot(Node<T> *r);

protected:
    T* AddChild(T* c);
    void  DeleteChild(T* c);

    static Node<T>* root;

private:
    Node<T>* parent { root };
    std::vector<T*> children {  };
};

}

#include "Node.tpp"


#endif //CORE_NODE_H

/**
 * No Node.cpp is presented. Check Node.tpp for template implementations
 */
#ifndef CORE_NODE_H
#define CORE_NODE_H

#include "Essential.h"

namespace core {

template <typename T> class Node {
public:
    explicit Node(T* parent) {
        // This assertion is necessary because of downcast in Node<T>::GetChild()
        static_assert(std::is_base_of<Node<T>, T>::value, "Type T must inherit from Node<T>");
        SetParent(parent);
    }

    /**
     *  Get child by index
     *  @note Children indexes are not consistent
     *  @return Pointer to child at index i
     */
    T* GetChild(int32_t i);

    /**
     * Get parent of this node
     * @return Pointer to parent
     */
    T* GetParent();

    /**
     * Change node's parent to newParent
     * @note Method is called at Node<T> constructor to init parent field
     * @param newParent - pointer to new parent object. Must inherit from Node<T>
     */
    void SetParent(T* newParent);

    /**
     * Change hierarchy's root to newRoot
     * @note For core::Entity hierarchy method is called at core::Root constructor
     */
    static void SetRoot(T* newRoot);

protected:

    /**
     * Adds child to Node's children.
     */
    void AddChild(Node<T>* c);

    /**
     * Removes child from Node's children.
     * @note Cmpares pointer c to all children pointers.
     */
    void DeleteChild(Node<T>* c);

    /**
     *  Pointer to root node.
     *  @warning Initialized in core::Root constructor, before that is nullptr.
     */
    static T* root;

    /**
     *  Pointer to parent node.
     *  @warning Initialized in core::Node constructor, before that is nullptr.
     */
    T* parent { nullptr };
    std::vector<Node<T>*> children {  };
};

} // namespace core

#include "Node.tpp"


#endif //CORE_NODE_H

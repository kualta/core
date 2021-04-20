/**
 * No Node.cpp is presented. Check Node.tpp for template definitions
 */
#ifndef CORE_NODE_H
#define CORE_NODE_H

#include "Essential.h"

namespace core {

// TODO: Make Node component
template <typename T>
class Node : public std::enable_shared_from_this<Node<T>> {
public:

    /**
     *  Get child by index
     *  @note Children indexes are not consistent
     *  @return Pointer to child at index i
     */
    std::shared_ptr<T> GetChild(uint32_t i);

    /**
     * Get parent of this node
     * @return Pointer to parent
     */
    std::weak_ptr<T> GetParent();

    /**
     * Change node's parent to newParent
     * @note Method is called at Node<T> constructor to init parent field
     * @param newParent - pointer to new parent object. Must inherit from Node<T>
     */
    void SetParent(std::weak_ptr<T> newParent);

    /**
     * Creates new root of the hierarchy
     * @return std::shared_ptr to new root object
     */
    static std::weak_ptr<T> CreateRoot();

    bool operator==(const Node &rhs) const;
    bool operator!=(const Node &rhs) const;

protected:

    explicit Node(std::weak_ptr<T> parent);

    /**
     * Adds child to Node's children.
     */
    void AddChild(std::shared_ptr<T>&& c);

    /**
     * Removes child from Node's children.
     * @note Cmpares pointer c to all children pointers.
     */
    void DeleteChild(std::shared_ptr<T> c);

    /**
     * Change hierarchy's root to newRoot
     * @note For core::Entity hierarchy method is called at core::Root constructor
     */
    static void SetRoot(std::weak_ptr<T> newRoot);

    /**
     *  Pointer to root node.
     *  @warning Initialized in core::Root constructor, before that is nullptr.
     */
    static std::weak_ptr<T> root;

    /**
     *  Pointer to parent node.
     *  @warning Initialized in core::Node constructor, before that is nullptr.
     */
    std::weak_ptr<T> parent;

    /**
     * Vector of children nodes
     */
    std::vector<std::shared_ptr<T>> children {  };
};

} // namespace core

#include "Node.tpp"


#endif //CORE_NODE_H

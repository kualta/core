/**
 *  core::Node template function implementations file
 */
#include <algorithm>
#include "Node.h"
#include "Logger.h"


namespace core {



template<typename T>
Node<T>::Node(T& parent) {
    // This assertion is necessary because of downcast in Node<T>::GetChild()
//    static_assert(std::is_base_of<Node<T>, T>::value, "Type T must inherit from Node<T>");
    SetParent(*parent);
}
template<typename T>
Node<T>::Node(T *parent) {
    assert((!root.expired(), "This constructor must only be used if root has not been set yet!"));
    // This constructor takes T* expecting nullptr on its place. Only used to create root node,
    // since it cannot have parent. After root has been set assert won't allow use of this.
}
template<typename T>
Node<T>::~Node() {
//    if ( parent ) parent->DeleteChild(*this);
//    for ( auto c: children ) { delete c; }
//    if ( !children.empty() ) children.erase(children.begin(), children.end());
}
template<typename T>
T& Node<T>::GetChild(int32_t index) {
    return *children[index];
}
template<typename T>
T& Node<T>::GetParent() {
    return *parent.lock();
}
template<typename T>
void Node<T>::SetParent(T& newParent) {
    if (*this == *root.lock()) {
        Logger::Log(ERR, INTERNAL) << "Cannot set parent for root node!";
        return;
    }
    // TODO: fix implementation \/
    if ( !parent.expired() ) parent->DeleteChild(*this);
    newParent.AddChild(std::make_shared<T>(*this));

    parent = &newParent;
}
template<typename T>
void Node<T>::AddChild(std::shared_ptr<T> c) {
    children.push_back(std::move(c));
}
template<typename T>
void Node<T>::DeleteChild(T& c) {
    auto child = std::find_if(children.begin(), children.end(), [&](std::shared_ptr<Node<T>> const& p) {
        return *p == c;
    });
    if ( child != children.end() ) {
        children.erase(child);
    }
}
template<typename T>
void Node<T>::SetRoot(std::weak_ptr<T> newRoot) {
    root = std::move(newRoot);
}
template<typename T>
std::shared_ptr<T> Node<T>::CreateRoot() {
    if ( !root.expired() ) {
        Logger::Log(ERR, INTERNAL) << "Root node already exists!";
    }
    std::shared_ptr<T> rootObj = std::make_shared<T>( nullptr );
    T::SetRoot(rootObj);

    return rootObj;
}
template<typename T>
bool Node<T>::operator==(const Node &rhs) const {
    return parent == rhs.parent &&
           children == rhs.children;
}
template<typename T>
bool Node<T>::operator!=(const Node &rhs) const {
    return !(rhs == *this);
}


} // namespace core
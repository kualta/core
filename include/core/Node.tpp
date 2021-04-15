/**
 *  core::Node template function implementations file
 */
#include <algorithm>
#include "Node.h"


namespace core {

template<typename T> T* Node<T>::root { nullptr };

template<typename T>
T Node<T>::GetChild(int32_t index) {
    return static_cast<T&>(*children[index]);
}
template<typename T>
void Node<T>::AddChild(Node<T>& c) {
    children.push_back(&c);
}
template<typename T>
void Node<T>::DeleteChild(Node<T>& c) {
    children.erase(std::find(children.begin(), children.end(), &c));
}
template<typename T>
void Node<T>::SetRoot(T& newRoot) {
    root = &newRoot;
}
template<typename T>
void Node<T>::SetParent(T& newParent) {
    if ( parent ) parent->DeleteChild(*this);
    newParent.AddChild(*this);

    parent = &newParent;
}
template<typename T>
T& Node<T>::GetParent() {
    return static_cast<T&>(*parent);
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
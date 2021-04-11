/**
 *  core::Node template function implementations file
 */
#include <algorithm>
#include "Node.h"


namespace core {

template<typename T> Node<T>* Node<T>::root { nullptr };

template<typename T>
void Node<T>::SetParent(Node<T>* newParent) {
    if ( parent ) parent->DeleteChild(this);
    if ( newParent ) newParent->AddChild(this);

    parent = newParent;
}
template<typename T>
T* Node<T>::GetChild(int32_t index) {
    return static_cast<T*>(children[index]);
}
template<typename T>
void Node<T>::AddChild(Node<T>* c) {
    children.push_back(c);
}
template<typename T>
void Node<T>::DeleteChild(Node<T>* c) {
    children.erase(std::find(children.begin(), children.end(), c));
}
template<typename T>
void Node<T>::SetRoot(Node<T> *r) {
    root = r;
}


} // namespace core
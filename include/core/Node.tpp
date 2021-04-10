/**
 *  core::Node template function implementations file
 */
#include <core/Node.h>
#include <algorithm>

namespace core {

template<typename T>
void Node<T>::SetParent(T *newParent) {
    if (parent) {
        parent->DeleteChild(this);
    }
    parent = newParent;
    newParent->AddChild(this);
}
template<typename T>
T *Node<T>::GetChild(int32_t index) {
    return children[index];
}
template<typename T>
uint32_t Node<T>::AddChild(T *c) {
    children.push_back(c);
    return children.size() - 1;
}
template<typename T>
void Node<T>::DeleteChild(T *c) {
    children.erase(std::find(children.begin(), children.end(), c));
}

} // namespace core
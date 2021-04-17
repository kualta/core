/**
 *  core::Node template function implementations file
 */
#include <algorithm>
#include "Node.h"
#include "Logger.h"


namespace core {

template<typename T>
std::weak_ptr<T> Node<T>::root {  };

template<typename T>
Node<T>::Node(T& parent) {
    static_assert(std::is_base_of<Node<T>, T>::value, "Type T must inherit from Node<T>");
    SetParent(parent);
}
template<typename T>
Node<T>::Node(T *parent) {
    assert((!root.expired(), "This constructor must only be used if root has not been set yet!"));
    // This constructor takes T* expecting nullptr on its place. Only used to create root node,
    // since it cannot have parent. After root has been set assert won't allow use of this.
}
template<typename T>
T& Node<T>::GetChild(int32_t index) {
    return *children[index];
}
template<typename T>
T Node<T>::GetParent() {
    if( !parent.expired() ) {
        return *parent.lock();
    } else {
        Logger::Log(ERR, INTERNAL) << "Parent has not been assigned or has been deleted!";
        return nullptr;
    }
}
template<typename T>
void Node<T>::SetParent(T& newParent) {
    if (*static_cast<T*>(this) == *root.lock()) {
        Logger::Log(ERR, INTERNAL) << "Cannot set parent for root node!";
        return;
    }
    if ( !parent.expired() ) parent.lock()->DeleteChild(static_cast<T*>(this));
    newParent.AddChild(*static_cast<T*>(this));

    parent = std::make_shared<T>(std::move(newParent));
}
template<typename T>
void Node<T>::AddChild(T& c) {
    children.push_back(std::make_shared<T>(std::move(c)));
}
template<typename T>
void Node<T>::DeleteChild(T* c) {
    auto child = std::find_if(children.begin(), children.end(), [&](std::shared_ptr<Node<T>> const& p) {
        return *p == *c;
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
    return *parent.lock() == *rhs.parent.lock() &&
           children == rhs.children;
}
template<typename T>
bool Node<T>::operator!=(const Node &rhs) const {
    return !(rhs == *this);
}


} // namespace core
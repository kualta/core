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
Node<T>::Node(std::weak_ptr<T> parent) {

}
template<typename T>
std::shared_ptr<T> Node<T>::GetChild(uint32_t index) {
    return children[index];
}
template<typename T>
std::weak_ptr<T> Node<T>::GetParent() {
    if( parent.expired() ) {
        Logger::Log(ERR, INTERNAL) << "Parent has not been assigned or has been deleted!";
    }
    return parent;
}
template<typename T>
void Node<T>::SetParent(std::weak_ptr<T> newParent) {
    if (*static_cast<T*>(this) == *root.lock()) {
        Logger::Log(ERR, INTERNAL) << "Cannot set parent for root node!";
        return;
    }
    if ( !parent.expired() ) parent.lock()->DeleteChild( this->shared_from_this() );
    newParent.AddChild( this->shared_from_this() );

    parent = std::move(newParent);
}
template<typename T>
void Node<T>::AddChild(std::shared_ptr<T>&& c) {
    children.push_back(std::move(c));
}
template<typename T>
void Node<T>::DeleteChild(std::shared_ptr<T> c) {
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
    std::shared_ptr<T> rootObj = std::make_shared<T>( );
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
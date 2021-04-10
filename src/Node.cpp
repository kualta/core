#include <core/Node.h>
#include <algorithm>

namespace core {

void Node::SetParent(Node *newParent) {
    if (parent) {
        parent->DeleteChild(this);
    }
    parent = newParent;
    newParent->AddChild(this);
}
uint32_t Node::AddChild(Node *c) {
    children.push_back(c);
    return children.size() - 1;
}
void Node::DeleteChild(Node *c) {
    children.erase(std::find(children.begin(), children.end(), c));
}
Node* Node::GetChild(int32_t i) {
    return children[i];
}

} // namespace core
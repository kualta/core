#ifndef CORE_NODE_H
#define CORE_NODE_H

#include "Essential.h"

namespace core {

class Node {
public:
    Node() : parent(nullptr) {}
    Node(Node* parent) : parent(parent) {}

    void SetParent(Node *newParent);
    Node* GetChild(int32_t index);

protected:
    uint32_t AddChild(Node *c);
    void  DeleteChild(Node *c);

private:
    Node *parent { nullptr };
    std::vector<Node *> children {  };
};



}

#endif //CORE_NODE_H

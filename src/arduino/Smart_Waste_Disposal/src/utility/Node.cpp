#include <stdlib.h>
#include "utility/Node.hpp"

Node::Node(void(*func)()) {
    this->next = nullptr;
    this->func = func;
}

Node::~Node() {
    free(this);
}

Node* Node::getNext() {
    return this->next;
}

void Node::setNext(Node* node) {
    this->next = node;
}
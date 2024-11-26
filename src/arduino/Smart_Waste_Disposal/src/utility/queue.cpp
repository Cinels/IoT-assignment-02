#include <stdlib.h>
#include "utility/Queue.hpp"
#include "utility/Node.hpp"

#define MAX_SIZE 10

Queue::Queue() {
  this->head = nullptr;
  this->tail = nullptr;
  this->size = 0;
}

void Queue::clear() {
  while(this->head != nullptr) {
    this->dequeue();
  }
}

int Queue::enqueue(void(*func)()) {
  if(this->size < MAX_SIZE) {
    Node *temp = new Node(func);
    if (this->head == nullptr) {
      this->head = temp;
    }
    if (this->tail != nullptr) {
      this->tail->setNext(temp);
    }
    this->size++;
    this->tail = temp;
    return 0;
  }
  return 1;
}

int Queue::dequeue() {
  Node* temp = this->head;
  if(temp != nullptr && this->size > 0) {
    if(this->head->getNext() == nullptr) {
      this->head = nullptr;
      this->tail = nullptr;
    } else {
      this->head = this->head->getNext();
    }
    this->size--;
    temp->~Node();
    return 0;
  }
  return 1;
}

Node* Queue::getNext() {
  return this->head;
}
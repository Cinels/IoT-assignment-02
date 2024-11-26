#ifndef __QUEUE__
#define __QUEUE__

#include "Node.hpp"

class Queue {
private:
  Node* head;
  Node* tail;
  short size;
public:
  Queue();
  void clear();
  int enqueue(void (*func)());
  int dequeue();
  Node* getNext();
};

#endif
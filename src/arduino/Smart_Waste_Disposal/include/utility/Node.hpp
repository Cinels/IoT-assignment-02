#ifndef __NODE__
#define __NODE__

class Node {
private:
  Node* next;
  void (*func)();
public:
  Node(void(*func)());
  ~Node();
  Node* getNext();
  void setNext(Node* node);
};

#endif
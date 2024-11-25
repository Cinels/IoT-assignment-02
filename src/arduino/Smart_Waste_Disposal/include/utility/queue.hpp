#ifndef __QUEUE__
#define __QUEUE__

typedef struct Node{
  struct Node *next;
  void (*func)();
} Node;

typedef struct Queue{
  Node *head;
  Node *tail;
  short size;
} Queue;

Queue* initialize();

void clear(Queue* Q);

void enqueue(Queue* Q, void(*func)());

void dequeue(Queue* Q);

Node* getNext(Queue* Q);

#endif
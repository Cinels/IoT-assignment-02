#include <stdlib.h>
#include "utility/queue.hpp"

#define MAX_SIZE 10

Queue* initialize() {
  Queue* Q = (Queue*)malloc(sizeof(Queue));
  Q->head = NULL;
  Q->tail = NULL;
  Q->size = 0;
  return Q;
}

void clear(Queue* Q) {
  while(Q->head != NULL) {
    dequeue(Q);
  }
}

void enqueue(Queue* Q, void(*func)()) {
  if(Q->size < MAX_SIZE) {
    Node *temp = (Node*)malloc(sizeof(Node));
    temp->next = NULL;
    temp->func = func;
    if (Q->head == NULL) {
      Q->head = temp;
    }
    if (Q->tail != NULL) {
      Q->tail->next = temp;
    }
    Q->size++;
    Q->tail = temp;
  }
}

void dequeue(Queue* Q) {
  Node* temp = Q->head;
  if(temp != NULL && Q->size > 0) {
    if(Q->head->next == NULL) {
      Q->head = NULL;
      Q->tail = NULL;
    }
    else Q->head = Q->head->next;
    Q->size--;
    free(temp);
  }
}

Node* getNext(Queue* Q) {
  return Q->head;
}
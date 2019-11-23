#ifndef QUEUE_H
#define QUEUE_H

#include "bst.h"

typedef struct node_q{
    struct node_q* next;
    NodePtr value;
}Node_q;

typedef Node_q* NodePtr_q;

typedef struct{
    NodePtr_q head;
    NodePtr_q tail;
}Queue;

void makequeue(Queue* q);
NodePtr_q makenode_q(NodePtr node);
void enqueue(Queue* q, NodePtr node);
NodePtr dequeue(Queue* q);

#endif
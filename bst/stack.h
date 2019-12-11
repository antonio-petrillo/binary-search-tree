#ifndef STACK__H
#define STACK_H

#include "bst.h"

typedef struct node_s{
    struct node_s* next;
    NodePtr value;
}Node_s;

typedef Node_s* NodePtr_s;

typedef struct{
    NodePtr_s head;
}Stack;

void makestack(Stack* s);
NodePtr_s makenode_s(NodePtr node);
void push(Stack* s, NodePtr node);
void pop(Stack* s);
NodePtr top(Stack s);
int is_empty(Stack s);

#endif
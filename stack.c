#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void makestack(Stack* s){
    s->head = NULL;
}

NodePtr_s makenode_s(NodePtr node){
    NodePtr_s newnode = (NodePtr_s) malloc(sizeof(Node_s));
    if(!newnode) error("impossibile allocare il nodo per lo stack");
    newnode->value = node;
    newnode->next = NULL;
    return newnode;
}

void push(Stack* s, NodePtr node){
    NodePtr_s newnode = makenode_s(node);
    newnode->next = s->head;
    s->head = newnode;
}

void pop(Stack* s){
    if(s->head){
        NodePtr_s tmp = s->head;
        s->head = s->head->next;
        free(tmp);
    }
    return;
}

NodePtr top(Stack s){
    NodePtr tmp = NULL;
    if(s.head) tmp = s.head->value;
    return tmp;
}

int is_empty(Stack s){
    if(s.head) return 1;
    else return 0;
}
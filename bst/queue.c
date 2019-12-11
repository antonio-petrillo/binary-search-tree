#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void makequeue(Queue* q){
    q->head = NULL;
    q->tail = NULL;
}

NodePtr_q makenode_q(NodePtr node){
    NodePtr_q newnode = (NodePtr_q) malloc(sizeof(Node_q));
    if(!newnode)error("errore nella creazione del nodo della coda");
    newnode->value = node;
    newnode->next = NULL;
    return newnode;
}

void enqueue(Queue* q, NodePtr node){
    if(node){
        if(!(q->head || q->tail)) q->head = q->tail = makenode_q(node);
        else{
            NodePtr_q newnode = makenode_q(node);
            q->tail->next = newnode;
            q->tail = newnode;
        }
    }
}

NodePtr dequeue(Queue* q){
    NodePtr ret;
    if(!(q->head || q->tail)) ret =  NULL;
    else{
        ret = q->head->value;
        if(q->head == q->tail) q->head = q->tail = NULL;
        else q->head = q->head->next;
    }
    return ret;
}
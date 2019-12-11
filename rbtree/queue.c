#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "rbtree.h"

void makequeue(Queue* q){
    q->head = q->tail = NULL;
    return;
}

NodeQPtr makenode_queue(NodePtr RB_node){
    NodeQPtr newnode = (NodeQPtr) malloc(sizeof(NodeQ));
    if(!newnode){printf("error in allocating node for th queue\n"); exit(0);}
    newnode->next = NULL;
    newnode->RB_node = RB_node;
    return newnode;
}

void enqueue(Queue* q, NodePtr RB_node){
    if(RB_node){
        if(!(q->head || q->tail))//empty queue
            q->head = q->tail = makenode_queue(RB_node);
        else{
            NodeQPtr newnode = makenode_queue(RB_node);
            q->tail->next = newnode;
            q->tail = newnode;
        }
    }
}

NodePtr dequeue(Queue* q){
    NodePtr ret;
    if(!(q->head || q->tail)) ret =  NULL;
    else{
        NodeQPtr tmp;
        ret = q->head->RB_node;
        tmp = q->head;
        if(q->head == q->tail) q->head = q->tail = NULL;
        else q->head = q->head->next;
        free(tmp);
    }
    return ret;

}
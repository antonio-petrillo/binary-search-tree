#ifndef QUEUE_H
#define QUEUE_H

    #include "rbtree.h"

    typedef struct node_queue{
        struct node_queue* next;
        NodePtr RB_node;
    }NodeQ;

    typedef NodeQ* NodeQPtr;

    typedef struct{
        NodeQPtr head;
        NodeQPtr tail;
    }Queue;

    void makequeue(Queue* q);
    NodeQPtr makenode_queue(NodePtr RB_node);
    void enqueue(Queue* q, NodePtr RB_node);
    NodePtr dequeue(Queue* q);

#endif
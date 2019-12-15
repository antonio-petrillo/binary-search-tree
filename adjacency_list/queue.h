#ifndef QUEUE_H 
#define QUEUE_H 1

    typedef struct queue_node{
        struct queue_node* next;
        int value;
    }queue_node;

    typedef struct{
        queue_node* head;
        queue_node* tail;
    }Queue;

    Queue make_queue(Queue q);
    queue_node* make_queue_node(int value);
    void enqueue(Queue* q, int value);
    int dequeue(Queue* q);
    //void status(Queue q);

#endif
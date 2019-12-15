#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "queue.h"

Queue make_queue(Queue q){
    q.head = q.tail = NULL;
    return q;
}

queue_node* make_queue_node(int value){
    queue_node* newnode = (queue_node*) malloc(sizeof(int));
    if(!newnode){
      printf("error in function: queue_node* make_queue_node(int value) of queue.c\n");
      exit(EXIT_FAILURE);    
    }
    newnode->next = NULL;
    newnode->value = value;
    return newnode;
}

void enqueue(Queue* q, int value){
    if(q->head == q->tail && q->head == NULL) q->head = q->tail = make_queue_node(value);
    else{
        queue_node* newnode = make_queue_node(value);
        q->tail->next = newnode;
        q->tail = newnode;
        return;
    }
}

int dequeue(Queue* q){
    int ret;
    queue_node* tmp = NULL;
    if(q->head == q->tail && q->head == NULL) return INT_MAX;
    else{
        ret = q->head->value;
        tmp = q->head;
        if(q->head == q->tail){
            q->head = q->tail = NULL;
        }else{
            q->head = tmp->next;
        }
        free(tmp);
    }
    return ret;
}

// void status(Queue q){
//     queue_node* iter = q.head;
//     while(iter){
//         printf("vertex:%4d", iter->value);
//         iter = iter->next;
//     }
//     puts("");
//     return;
// }
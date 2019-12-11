#ifndef QUEUE_H
#define QUEUE_H

#include "list_sl.h"

typedef struct Queue{
    Nodo* head;
    Nodo* tail;
}Queue;

void creaqueue(Queue* Q);
void enqueue(Queue* Q, int elem);
void dequeue(Queue* Q, int* elem);
int CodaVuota(Queue *Q);
void LeggiQueue (Queue *Q, int *elem);
void StampaCoda(Queue* Q);
void LiberaCoda(Queue *Q);

#endif
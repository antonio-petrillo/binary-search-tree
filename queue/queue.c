#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void creaqueue(Queue* Q){
    if(Q){
        Q->head = NULL;
        Q->tail = NULL;
    }
}
void enqueue(Queue* Q, int elem){
    Nodo* tmp;
    if(Q == NULL) return;
    else if(CodaVuota(Q)){
        tmp = creanodo(elem);
        if(tmp){
            Q->head = tmp;
            Q->tail = Q->head;
        }    
        return;
    }
    else{
        tmp = creanodo(elem);
        if(tmp){
            Q->tail->nextptr = tmp;
            Q->tail = Q->tail->nextptr;
        }
        return;
    }
}
void dequeue(Queue* Q, int* elem){
    if(CodaVuota(Q) || elem == NULL){//se la coda è vuota
        printf("la coda è vuota \n");
        return;
    }
    else if(Q->head == Q->tail){// se la coda ha un solo nodo
        *elem = Q->head->value;
        free(Q->head);
        Q->head = Q->tail = NULL;
    }
    else{//se la coda non è vuota ED ha più di un elemento
        Nodo* tmp;
        tmp = Q->head;
        Q->head = Q->head->nextptr;
        *elem = tmp->value;
        free(tmp);
    }
}
int CodaVuota(Queue *Q){
    return (Q->head == NULL);
}
void LeggiQueue (Queue *Q, int *elem){//legge il primo elemento nella queue
    if(CodaVuota(Q) || elem){
        printf("se arrivo qua c'è un problema\n");
        return;
    }
    else{
        *elem = Q->head->value;
        return;
    }
}
void StampaCoda(Queue* Q){
    Nodo* tmp;
    if(CodaVuota(Q)){
        printf("la coda è vuota\n");
        return;
    }
    else{
        tmp = Q->head;
        printf("H--] ");
        while(tmp->nextptr != NULL){
            printf("% d ", tmp->value);
            tmp = tmp->nextptr;
        }
        printf(" %d [--T\n", tmp->value);
        return;
    }
}
void LiberaCoda(Queue *Q){
    Nodo *tmp;
    if(Q != NULL ) {
        while(Q->head != NULL ) {
            tmp = Q->head;
            Q->head = Q->head->nextptr;
            free(tmp);
        }
        Q->head = Q->tail = NULL ;
    }
}
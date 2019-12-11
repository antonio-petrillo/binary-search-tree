#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main(int argc, char const *argv[])
{
    int dato;
    Queue Coda;
    creaqueue(&Coda);
    for(int i=1; i<argc; i++){
        enqueue(&Coda, atoi(argv[i]));
    }
    StampaCoda(&Coda);
    dequeue(&Coda, &dato);
    printf("elemento estratto %d\n", dato);
    StampaCoda(&Coda);
    dequeue(&Coda, &dato);
    printf("elemento estratto %d\n", dato);
    StampaCoda(&Coda);
    LiberaCoda(&Coda);
    return 0;
}

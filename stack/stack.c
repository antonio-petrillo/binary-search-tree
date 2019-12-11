#include "stack.h"
#include <stdio.h>

void creastack(Stack* S){
  S->nextptr = NULL;
  return;
}
void push(Stack* S, int value){
  inserimento_in_testa(S,value);
  return;
}
int pop(Stack* S){
  int elem;
  estrai_in_testa(S, &elem);
  return elem;
}
void LiberaStack(Stack* S){
  deletelist(S);
}
int StackVuoto(Stack* S){
  if(S->nextptr == NULL){
    printf("lo stack è vuoto\n");
    return 1;
  }
  else{
    printf("lo stack non è vuoto\n");
    return 0;
  }
}
void stampastack(Stack *S){
  if(S->nextptr == NULL){
    printf("lo stack è vuoto\n");
    return;
  }
  else{
    Nodo* tmp = S->nextptr;
    printf("[Stack] ->");
    while(tmp->nextptr != NULL){
      printf("%d ->", tmp->value);
      tmp = tmp->nextptr;
    }
    printf("%d --|\n", tmp->value);
    return;
  }
}

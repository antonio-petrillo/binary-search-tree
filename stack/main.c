#include <stdio.h>
#include "stack.h"

int main(int argc, char const *argv[]) {
  int elem;
  Stack S;
  creastack(&S);
  for(int i=0; i<10; i++){
    printf("inserisci un valore: ");
    scanf("%d", &elem);
    push(&S, elem);
  }
  stampastack(&S);
  for(int i=0; i<10; i++){
    printf("prelievo dallo stack: %d\n", pop(&S));
  }
  StackVuoto(&S);
  for(int i=0; i<10; i++){
    printf("inserisci un valore: ");
    scanf("%d", &elem);
    push(&S, elem);
  }
  stampastack(&S);
  for(int i=0; i<5; i++){
    printf("prelievo dallo stack: %d\n", pop(&S));
  }
  StackVuoto(&S);
  LiberaStack(&S);
  return 0;
}

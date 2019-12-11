#include <stdio.h>
#include "list_sl.h"

int main(int argc, char const *argv[]) {
  Lista_SL lista;
  crealista(&lista);
  int elem, key;
  int *elemptr = &elem;
  for(int i=0; i<10; i++){
    printf("inserisci un valore: ");
    scanf("%d", &elem);
    inserimento_in_testa(&lista, elem);
  }
  stampalista(&lista);
  for(int i=0; i<5; i++){
    printf("inserisci un valore da eliminare: ");
    scanf("%d", &key);
    if(estrai_elemento(&lista, elemptr, key))
      printf("elemento estratto %d \n", elem);
  }
  stampalista(&lista);
  deletelist(&lista);
  return 0;
}

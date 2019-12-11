#include <stdio.h>
#include <stdlib.h>
#include "liste_dl.h"

int main(int argc, char const *argv[]){
    Lista_DL lista;
    int dato;
    int key, elem;
    makelist(&lista);
    for(int i=1; i<argc; i++)
    inserimento_ordinato(&lista, atoi(argv[i]));
    stampalista(&lista);
    printf("inserire un valore da inserire nella lista: ");
    scanf("%d", &elem);
    printf("dopo quale valore lo vuoi inserire: ");
    scanf("%d", &key);
    inserisci_dopo_elemento(&lista, key, elem);
    stampalista(&lista);
    svuotalista(&lista);
    stampalista(&lista);
    return 0;
}

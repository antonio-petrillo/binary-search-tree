#include <stdio.h>
#include <stdlib.h>
#include "circular_double_linked.h"

int main(int argc, char const *argv[]){
    Lista_DCL lista;
    int dato, key, elem;
    makelist(&lista);
    for(int i=1; i<argc; i++){
        inserimento_ordinato(&lista, atoi(argv[i]));
    }
    stampalista_molteplice(&lista, 1);
    printf("quale elemento vuoi inserire?\n?:");
    scanf("%d", &elem);
    printf("dopo quale elemento lo vuoi inserire?\n?:");
    scanf("%d", &key);
    inserisci_dopo_elem(&lista, elem, key);
    stampalista(&lista);
    freelist(&lista);
    stampalista(&lista);
    return 0;
}

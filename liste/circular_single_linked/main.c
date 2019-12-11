#include <stdio.h>
#include <stdlib.h>
#include "circular_singular_list.h"

int main(int argc, char const *argv[])
{
    int dato;
    int key, elem;
    Lista_SCL lista;
    makelist(&lista);
    for(int i=1; i<argc; i++){
        inserimento_ordinato(&lista, atoi(argv[i]));
    }
    stampalista_molteplice(&lista, 1);
    printf("inserire elemento: ");
    scanf("%d", &elem);
    printf("dopo quale valore?\n?: ");
    scanf("%d", &key);
    inserisci_dopo_elem(&lista, elem, key);
    stampalista(&lista);
    freelist(&lista);
    stampalista(&lista);
    return 0;
}

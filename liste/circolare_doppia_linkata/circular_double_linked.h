#ifndef CIRCULAR_DOUBLE_LINKED_H
#define CIRCULAR_DOUBLE_LINKED_H

struct nodo{
    struct nodo* next;
    struct nodo* prev;
    int value;
    int start_of_the_list;
};

typedef struct nodo Nodo_DCL;

typedef struct{
    Nodo_DCL* next;
}Lista_DCL;

void makelist(Lista_DCL* Head);
Nodo_DCL* makenode(int elem);
void inserisci_in_testa(Lista_DCL* Head, int elem);
void inserisci_in_coda_deprecated(Lista_DCL* Head, int elem);
void inserisci_in_coda(Lista_DCL* Head, int elem);
void inserimento_ordinato(Lista_DCL* Head, int elem);
void stampalista(Lista_DCL* Head);
void stampalista_molteplice(Lista_DCL* Head, int num_stampe);
void freelist(Lista_DCL* Head);
void preleva_in_testa(Lista_DCL* Head, int* dato);
void preleva_in_coda(Lista_DCL* Head, int* dato);
void preleva_elem_desiderato(Lista_DCL* Head, int* dato, int key);
Nodo_DCL* search_node(Lista_DCL* Head, int key);
void inserisci_dopo_elem(Lista_DCL* Head, int elem, int key);

#endif
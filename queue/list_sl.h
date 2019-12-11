#ifndef LIST_SL_H
#define LIST_SL_H

struct nodo{
    int value;
    struct nodo* nextptr;
};
typedef struct {
    struct nodo* nextptr;
}Lista_SL;

typedef struct nodo Nodo;

void crealista(Lista_SL* Head);
void inserimento_in_testa(Lista_SL* Head, int elem);
void inserimento_in_coda(Lista_SL* Head, int elem);
void inserimento_ordinato(Lista_SL* Head, int elem);
Nodo* creanodo(int elem);
int estrai_in_testa (Lista_SL* Head, int* elem);
int  estrai_in_coda (Lista_SL* Head, int* elem);
int estrai_elemento (Lista_SL* Head, int* elem, int key);
void stampalista(Lista_SL* Head);
void delete_node(Lista_SL* Head, int key);
void deletelist(Lista_SL* Head);

#endif

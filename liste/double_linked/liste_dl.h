#ifndef LIST_DL_H
#define LIST_DL_H

    typedef struct Nodo_DL {
        int value;
        struct Nodo_DL* next;
        struct Nodo_DL* prev;
    } Nodo_DL;

    typedef struct{
        Nodo_DL * next;
    } Lista_DL;

    void makelist(Lista_DL* Head);
    Nodo_DL* makenode(int elem);
    void inserisci_in_testa(Lista_DL* Head, int elem);
    void inserisci_in_coda(Lista_DL* Head, int elem);
    void inserimento_ordinato(Lista_DL* Head, int elem);
    void stampalista(Lista_DL* Head);
    void svuotalista(Lista_DL* Head);
    void elimina_nodo_in_testa(Lista_DL* Head, int* dato);
    void elimina_nodo_in_coda(Lista_DL* Head, int* dato);
    void elimina_nodo_desiderato(Lista_DL* Head, int* dato, int key);
    Nodo_DL* cercaelemento(Lista_DL* Head, int key);
    void inserisci_dopo_elemento(Lista_DL* Head, int key, int elem);
#endif
#ifndef CIRCULAR_SINGLE_LIST_H
#define CIRCULAR_SINGLE_LIST_H

    struct nodo{
        int start_of_the_list;
        int value;
        struct nodo* next;
    };

    typedef struct nodo Nodo_SCL;

    typedef struct{
        Nodo_SCL* next;
    }Lista_SCL;

    void makelist(Lista_SCL* Head); 
    Nodo_SCL* makenode(int elem);
    void inserisci_in_testa(Lista_SCL* Head, int elem);
    void inserisci_in_coda(Lista_SCL* Head, int elem);
    void inserimento_ordinato(Lista_SCL* Head, int elem);
    void stampalista(Lista_SCL* Head);
    void stampalista_molteplice(Lista_SCL* Head, int num_stampe);
    void freelist(Lista_SCL* Head);
    void preleva_in_testa(Lista_SCL* Head, int* dato);
    void preleva_in_coda(Lista_SCL* Head, int* dato);
    void preleva_elem_desiderato(Lista_SCL* Head, int* dato, int key);
    Nodo_SCL* search_node(Lista_SCL* Head, int key);
    void inserisci_dopo_elem(Lista_SCL* Head, int elem, int key);
#endif

#ifndef LIST_SL_H
#define LIST_SL_H
#include <stdlib.h>

  struct node{
      char value;
      struct node* nextptr;
  };

  typedef struct node Node;
  typedef Node* Lista;

  Lista crealista();
  Lista inserisci_nodo_in_testa (Lista head, char elem);
  Lista inserisci_nodo_in_coda (Lista head, char elem);
  Lista inserisci_nodo_ordinato (Lista head, char elem);
  Node* crea_nodo(char elem);
  void print_list(Lista head);
  void delete_node(Lista* head, char key);
  void delete_list(Lista* head);
#endif

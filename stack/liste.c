#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list_sl.h"

void crealista(Lista_SL* Head){
    Head->nextptr = NULL;
    return;
}
void inserimento_in_testa(Lista_SL* Head, int elem){
    Nodo* tmp;
    if(!Head->nextptr){//se la lista è vuota
        tmp = creanodo(elem);
        if(tmp){
            Head->nextptr = tmp;
            return;
        }
    }
    else{
        tmp = creanodo(elem);
        if(tmp){
            tmp->nextptr = Head->nextptr;
            Head->nextptr = tmp;
            return;
        }
    }
}
void inserimento_in_coda(Lista_SL* Head, int elem){
    Nodo* tmp;
     if(!Head->nextptr){
      tmp = creanodo(elem);
      if(tmp){
            Head->nextptr = tmp;
            return;
        }
    }
    else{
        tmp = creanodo(elem);
        if(tmp){
            Nodo* iter = Head->nextptr;
            while(iter->nextptr != NULL){
                iter = iter->nextptr;
            }
            iter->nextptr = tmp;
        }
    }
}
void inserimento_ordinato(Lista_SL* Head, int elem){
    Nodo* tmp, *prev, *curr;
    prev = NULL;
    curr = Head->nextptr;
    while(curr != NULL && elem > curr->value){
        prev = curr;
        curr = curr->nextptr;
    }
    if(!prev){
        tmp = creanodo(elem);
        if(tmp){
            tmp->nextptr = Head->nextptr;
            Head->nextptr = tmp;;
            return;
        }
    }
    else{
        tmp = creanodo(elem);
        if(tmp){
            prev->nextptr = tmp;
            tmp->nextptr = curr;
            return;
        }
    }
}
Nodo* creanodo(int elem){
    Nodo* newnode;
    newnode = (Nodo*) malloc(sizeof(Nodo));
    if(!newnode){
        printf("impossibile allocare nodo memoria insufficiente\n");
        return NULL;
    }
    else{
        newnode->nextptr = NULL;
        newnode->value = elem;
        return newnode;
    }
}
void stampalista(Lista_SL* Head){
    if(!Head->nextptr){
        printf("la lista è vuota \n");
        return;
    }
    else{
        Nodo* tmp;
        tmp = Head->nextptr;
        printf("[lista] ->");
        while(tmp && tmp->nextptr){
            printf("%d -> ", tmp->value);
            tmp = tmp->nextptr;
        }
        if(tmp) printf("%d--|\n", tmp->value);
        return;
    }
}
void deletelist(Lista_SL* Head){
    Nodo* tmp;
    if(!Head->nextptr){
        printf("la lista è già vuota\n");
        return;
    }
    else{
        tmp = Head->nextptr;
        while(tmp != NULL){
            Head->nextptr = tmp->nextptr;
            free(tmp);
            tmp = Head->nextptr;
        }
        Head->nextptr = NULL;
    }
}
void delete_node(Lista_SL* Head, int key){
  Nodo* prev, *curr, *tmp;
  prev = NULL;
  curr = Head->nextptr;
  if(curr == NULL){
    printf("la lista è vuota\n");
    return;
  }
  else{
    while(curr != NULL && curr->value != key){
        prev = curr;
        curr = curr->nextptr;
    }
    if(curr == NULL){
      printf("l'elemento non è presente nella lista\n");
      return;
    }
    else if(prev == NULL){
      tmp = curr;
      Head->nextptr = curr->nextptr;
      free(tmp);
      return;
    }
    else{
      tmp = curr;
      prev->nextptr = curr->nextptr;
      free (tmp);
      return;
    }
  }
}
int estrai_in_testa (Lista_SL* Head, int* elem){
  Nodo* tmp;
  if(Head->nextptr==NULL){
    printf("la lista è vuota, impossibile estrare elemento\n");
    return 0;
  }
  else{
    tmp = Head->nextptr;
    Head->nextptr = tmp->nextptr;
    *elem = tmp->value;
    printf("elemento estratto %d\n", *elem);
    free(tmp);
    return 1;
  }
}
int estrai_in_coda (Lista_SL* Head, int* elem){
  Nodo *prev, *curr;
  prev = Head->nextptr;
  curr = Head->nextptr;
  while(curr != NULL && curr->nextptr!=NULL){
    prev = curr;
    curr = curr->nextptr;
  }
  if(prev == NULL){
    printf("la lista è vuota, impossibile estrare elemento\n");
    return 0;
  }
  else{
    *elem = curr->value;
    free(curr);
    prev->nextptr = NULL;
    printf("elemento estratto: %d\n", *elem);
    return 1;
  }
}
int estrai_elemento (Lista_SL* Head, int* elem, int key){
  Nodo* prev, *curr, *tmp;
  prev = NULL;
  curr = Head->nextptr;
  if(curr == NULL){
    printf("la lista è vuota\n");
    return 0;
  }
  else{
    while(curr != NULL && curr->value != key){
        prev = curr;
        curr = curr->nextptr;
    }
    if(curr == NULL){
      printf("l'elemento non è presente nella lista\n");
      return 0;
    }
    else if(prev == NULL){
      tmp = curr;
      *elem = tmp->value;
      Head->nextptr = curr->nextptr;
      free(tmp);
      return 1;
    }
    else{
      tmp = curr;
      *elem = curr->value;
      prev->nextptr = curr->nextptr;
      free (tmp);
      return 1;
    }
  }
}

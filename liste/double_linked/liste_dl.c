#include <stdio.h>
#include <stdlib.h>
#include "liste_dl.h"

void makelist(Lista_DL* Head){
    Head->next = NULL;
    return;
}
Nodo_DL* makenode(int elem){
    Nodo_DL* newnode = (Nodo_DL*)malloc(sizeof(Nodo_DL));
    if(newnode==NULL){
        printf("impossinbile allocare nodo, memoria insufficiente\n");
        return NULL;
    }
    else{
        newnode->value = elem;
        newnode->next = NULL;
        newnode->prev = NULL;
        return newnode;
    }
}
void inserisci_in_testa(Lista_DL* Head, int elem){
    Nodo_DL* tmp;
    if(Head->next == NULL){
        tmp = makenode(elem);
        if(tmp){
            Head->next = tmp;
            return;
        }
    }
    else{
        tmp = makenode(elem);
        if(tmp){
            tmp->next = Head->next;
            Head->next->prev = tmp;
            Head->next = tmp;
        }
    }
}
void inserisci_in_coda(Lista_DL* Head, int elem){
    Nodo_DL* iter, *tmp;
    if(Head->next == NULL){
        tmp = makenode(elem);
        if(tmp){
            Head->next = tmp;
            return;
        }
    }
    else{
        iter = Head->next;
        while(iter->next != NULL){
            iter = iter->next;
        }
        tmp = makenode(elem);
        if(tmp){
            iter->next = tmp;
            tmp->prev = iter;
        }
        return;
    }
}
void inserimento_ordinato(Lista_DL* Head, int elem){ //ordine crescente 
/*per inserire in ordine decrescente devo cambiare i > con < e viceversa*/ 
    Nodo_DL *tmp, *iter;
    if(!Head->next){
        //la lista non ha nodi, quindi il primo va aggiunto alla testa
        tmp = makenode(elem);
        if(tmp){
            Head->next = tmp;
        }
        return;
    }
    else{
        //la lista contiene almeno un nodo, quindi devo scorrere la lista per capire 
        //dove inserire il nuovo nodo
        iter = Head->next;
        while(iter->next && elem > iter->value)
            iter = iter->next;
        if(!iter->prev && elem < iter->value){/*se il puntatore al nodo precedente è NULL e
         se l'elemento è minore
         dell' elemento dell'iteratore : 
           -devo effettuare un inserimento in testa*/
            inserisci_in_testa(Head, elem);
            return;
        }
        else if(!iter->prev && elem >= iter->value){
            /*se il puntatore al nodo precedente è NULL, ma il valore da inserire
             è >= del valore nel nodo devo inserire il nuovo nodo in seconda posizione,
             ora devo distinguere dal caso in cui la lista ha un solo elemento-> 
             (in questo caso effettuo un inserimento in coda)
             o quando la lista ha 2 o più elementi*/
            if(!iter->next){//se il ptr al nodo successivo è NULL (la lista ha un solo nodo)
                tmp = makenode(elem);
                if(tmp){
                    tmp->prev = iter;
                    iter->next = tmp;
                }
                return;
            }
            else{// se il ptr al nodo successivo è != NULL il nuovo nodo va in seconda posizione
                tmp = makenode(elem);
                if(tmp){
                    tmp->next = iter->next;
                    tmp->prev = iter;
                    iter->next->prev = tmp;
                    iter->next = tmp; 
                }
                 return;
            }
        }/*se il ptr al nodo successivo è NULL ed l'elemento da inserire è maggiore 
          del valore nell'ultimo nodo devo effettuare un inserimento in coda [caso (1)]
          
          se il ptr al nodo successivo è NULL ed l'elemento da inserire è minore 
          del valore nell'ultimo nodo devo inserire il nuovo nodo in penultima posizione [caso (2)]*/

        else if(!iter->next && elem > iter->value){ //caso (1)
            inserisci_in_coda(Head, elem);
            return;
        }
        else if(!iter->next && elem <= iter->value){//caso (2)
            tmp = makenode(elem);
            if(tmp){
                tmp->next = iter;
                tmp->prev = iter->prev;
                iter->prev->next = tmp;
                iter->prev = tmp;
            }
            return;
        }
        else{// se il nodo da inserire va in posizione centrale nella lista
            tmp = makenode(elem);
            if(tmp){
                tmp->next = iter;
                tmp->prev = iter->prev;
                iter->prev->next = tmp;
                iter->prev = tmp;
            }
            return;
        }
    }
    
}
void stampalista(Lista_DL* Head){
    if(Head->next == NULL){
        printf("la lista è vuota\n");
        return;
    }
    else{
        Nodo_DL* tmp;
        tmp = Head->next;
        printf("[Lista_DL]: ");
        while(tmp != NULL && tmp->next != NULL){
            printf("%d <-> ", tmp->value);
            tmp = tmp->next;
        }
        printf("%d -|\n", tmp->value);
        return;
    }
}
void svuotalista(Lista_DL* Head){
    Nodo_DL* tmp;
    if(Head->next == NULL){
        printf("la lista è già vuota impossibile deallocarla\n");
        return;
    }
    else{
        while(Head->next != NULL){
            tmp = Head->next;
            Head->next = Head->next->next;
            printf("elimino: %d\n", tmp->value);
            free(tmp);
        }
        return;
    }
}
void elimina_nodo_in_testa(Lista_DL* Head, int* dato){
    Nodo_DL* tmp;
    if(!Head->next){
        printf("la lista è vuota impossibile estrarre nodo\n");
        return;
    }
    else{
        if(!Head->next->next){//se la lista ha un solo nodo
            *dato = Head->next->value;
            tmp = Head->next;
            free(tmp);
            printf("elemento estratto in testa %d\n", *dato);
            Head->next = NULL;
        }
        else{
            tmp = Head->next;
            Head->next = Head->next->next;
            Head->next->prev = NULL;
            *dato = tmp->value;
            free(tmp);
            printf("elemento estratto in testa %d\n", *dato);
        }
        return;
    }
}
void elimina_nodo_in_coda(Lista_DL* Head, int* dato){
    Nodo_DL *tmp, *iter; 
    if(!Head->next){ //se Head->next == NULL ovvero se la lista è vuota
        printf("la lista è vuota, impossibile estrarre elemento\n");
        return;
    }
    else{
        iter = Head->next;
        while(iter->next)
            iter = iter->next;
        if(!iter->prev){//se la lista ha un solo nodo
            *dato = iter->value;
            free(iter);
            printf("elemento estratto in coda %d\n", *dato);
            Head->next = NULL;
            return;
        }
        else{
            tmp = iter->prev;
            tmp->next = NULL;
            *dato = iter->value;
            free(iter);
            printf("elemento estratto in coda %d\n", *dato);
            return;
        }
    }
}
void elimina_nodo_desiderato(Lista_DL* Head, int* dato, int key){
    Nodo_DL *tmp, *iter;
    if(!Head->next){
        printf("lista vuota impossibile estrarre elemento\n");
        return;
    }
    else{
        iter = Head->next;
        while(iter->next && iter->value!=key)
            iter = iter->next;
        if(iter->value!=key){
            printf("l'elemento non è presente nella lista\n");
            return;
        }
        else{
            /*
            *caso 1) estrazione del primo elemento [estrazione in testa]
            *caso 2) estrazione dell' ultimo elemento [estrazione in coda]
            *caso 3) estrazione di un elemento in posizione centrale [estrazione elem "casuale"]
            */
            if(Head->next->value == key){//caso (1)
                elimina_nodo_in_testa(Head,dato);
                return;
            }
            else if(!iter->next){//caso (2)
                elimina_nodo_in_coda(Head,dato);
                return;
            }
            else{//caso (3)
                tmp = iter;
                iter->prev->next = tmp->next;
                iter->next->prev = tmp->prev;
                *dato = tmp->value;
                free(tmp);
                printf("elemento trovato ed estratto (%d)\n", *dato);
                return;
            }
        }
    }
}
Nodo_DL* cercaelemento(Lista_DL* Head, int key){
    Nodo_DL* iter;
    if(!Head->next){
        printf("la lista è vuota, impossibile cercare un nodo\n");
        return NULL;
    }
    else{
        iter = Head->next;
        while(iter->next && iter->value!=key)
            iter = iter->next;
        if(iter->value == key)
            return iter;
        else{
            return NULL;
        }
    }
}
void inserisci_dopo_elemento(Lista_DL* Head, int key, int elem){
    Nodo_DL* iter, *tmp;
    iter = cercaelemento(Head, key);
    if(!iter){
        printf("elemento non presente nela lista impossibile inserire il nodo\n");
        return;
    }
    else{
        if(!iter->next){//se il nodo successivo è NULL effetuo un inserimento in coda
            inserisci_in_coda(Head, elem);
            return;
        }
        else{//se il nodo successivo è !NULL lo inserisco dopo il nodo
            tmp = makenode(elem);
            if(tmp){
                tmp->next = iter->next;
                tmp->prev = iter;
                iter->next->prev = tmp;
                iter->next = tmp;
                return;
            }
        }
    }
}

        
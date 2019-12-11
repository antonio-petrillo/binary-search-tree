#include <stdio.h>
#include <stdlib.h>
#include "circular_double_linked.h"

void makelist(Lista_DCL* Head){
    Head->next = NULL;
    return;
}
Nodo_DCL* makenode(int elem){
    Nodo_DCL* tmp;
    tmp = (Nodo_DCL*) malloc(sizeof(Nodo_DCL));
    if(tmp){
        tmp->next = tmp->prev = NULL;
        tmp->start_of_the_list = 0;
        tmp->value = elem;
        return tmp;
    }
    else{
        printf("impossibile allocare nodo, memoria insufficiente\n");
        return NULL;
    }
}
void inserisci_in_testa(Lista_DCL* Head, int elem){
    Nodo_DCL* iter, *tmp;
    if(!Head->next){//se la lista è vuota
        tmp = makenode(elem);
        if(tmp){
            Head->next = tmp;
            tmp->next = tmp;
            tmp->prev = tmp;
            tmp->start_of_the_list = 1;
        }
        return; 
    }
    else{
        tmp = makenode(elem);
        if(tmp){
            Head->next->start_of_the_list = 0;
            tmp->start_of_the_list = 1;
            tmp->next = Head->next;
            tmp->prev = Head->next->prev;
            Head->next->prev->next = tmp;
            Head->next->prev = tmp;
            Head->next = tmp;
        }
        return;
    }
}
void inserisci_in_coda(Lista_DCL* Head, int elem){
    Nodo_DCL* newnode = makenode(elem);
    if(!newnode){printf("problema nell'allocazione del nodo!\n"); return;}
    newnode->next = Head->next;
    newnode->prev = Head->next->prev;
    Head->next->prev->next = newnode;
    Head->next->prev = newnode;
    return;

}
void inserisci_in_coda_deprecated(Lista_DCL* Head, int elem){
    Nodo_DCL* tmp, *iter;
    if(!Head->next){//se la lista è vuota devo inserire il primo elemento
        tmp = makenode(elem);
        if(tmp){
            Head->next = tmp;
            tmp->next = tmp;
            tmp->prev = tmp;
            tmp->start_of_the_list = 1;
        }
        return;
    }
    else{//mi sposto in ultima posizione con il ptr prev della testa della lista
        iter = Head->next; // meglio non usare il ptr Head per aggiustare i collegamenti si rischia di perderla
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
void inserimento_ordinato(Lista_DCL* Head, int elem){//ordine crescente (per l'ordine decrescente basta cambiare > & >= con < & <=)
    Nodo_DCL* tmp, *iter;
    if(!Head->next){
        tmp = makenode(elem);
        if(tmp){
            Head->next = tmp;
            tmp->start_of_the_list = 1;
            tmp->prev = tmp;
            tmp->next = tmp;
        }
        return;
    }
    else{
        iter = Head->next;
        while(iter->next != Head->next && elem > iter->value)
            iter = iter->next;
        if(iter->next != Head->next && elem <= iter->value){
            if(iter == Head->next){
                inserisci_in_testa(Head, elem);
                return;
            }
            else{
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
        else if(iter->next ==  Head->next && iter->prev == Head->next){
            if(elem >= iter->value){
                inserisci_in_coda(Head, elem);
                return;
            }
            else{
                inserisci_in_testa(Head, elem);
                return;
            }
        }
        else if(iter->next == Head->next && elem > iter->value){
            inserisci_in_coda(Head, elem);
            return;
        }
        else{
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
void stampalista(Lista_DCL* Head){
    Nodo_DCL* iter;
    if(!Head->next){
        printf("la lista è vuota\n");
        return;
    }
    else{
        iter = Head->next;
        printf("[Lista circolare <-> Head]: %d <->", iter->value);
        iter  = iter->next;
        while(iter->start_of_the_list != 1){
            printf(" %d <->", iter->value);
            iter = iter->next;
        }
        printf(" [%d]-|\n", iter->value);
        return;
    }
}
void stampalista_molteplice(Lista_DCL* Head, int num_stampe){
    Nodo_DCL* iter;
    int counter = 0;
    if(!Head->next){
        printf("la lista è vuota\n");
        return;
    }
    else{
        printf("stampa multipla di una lista doppiamente linkata (%d)\n", num_stampe);
        
        printf("[Lista circolare <-> Head]: ");
        while(counter < num_stampe){
            iter = Head->next;
            printf("%d <->", iter->value);
            iter = iter->next;
            while(iter->start_of_the_list != 1){
                printf(" %d <->", iter->value);
                iter = iter->next;
            }
            counter++;
        }
        
        printf(" [%d]-|\n", Head->next->value);
        return;
    }
}
void freelist(Lista_DCL* Head){
    Nodo_DCL* tmp, *iter;
    if(!Head->next){
        printf("la lista è vuota impossibile deallocarla\n");
        return;
    }
    else{
        iter = Head->next->prev;
        while(iter->start_of_the_list != 1){
            tmp = iter;
            iter = iter->prev;
            printf("elimino: %d\n", tmp->value);
            free(tmp);
        }
        printf("elimino: %d\n", iter->value);
        free(iter);
        Head->next = NULL;
        return;
    }
}
void preleva_in_testa(Lista_DCL* Head, int* dato){
    Nodo_DCL* tmp, *iter;
    if(!Head->next){
        printf("lista vuota, impossibile prelevare elemento\n");
        return;
    }
    else if(Head->next == Head->next->prev){//se la lista ha un solo elemento
        Nodo_DCL* tmp;
        tmp = Head->next;
        *dato = tmp->value;
        printf("elemento estratto: %d\n", *dato);
        free(tmp);
        Head->next = NULL;
    }
    else{
        tmp = Head->next;
        iter = Head->next;
        iter->next->start_of_the_list = 1; 
        iter->next->prev = tmp->prev;
        iter->prev->next = tmp->next;
        *dato = tmp->value;
        printf("elemento estratto: %d\n", *dato);
        Head->next = iter->next;
        free(tmp);
        return; 
    }
}
void preleva_in_coda(Lista_DCL* Head, int* dato){
    Nodo_DCL* tmp, *iter;
    if(!Head->next){
        printf("la lista è vuota, impossibile strarre elemento\n");
        return;
    }
    else if(Head->next == Head->next->prev){//se la lista ha un solo elemento
        Nodo_DCL* tmp;
        tmp = Head->next;
        *dato = tmp->value;
        printf("elemento estratto: %d\n", *dato);
        free(tmp);
        Head->next = NULL;
    }
    else{
        tmp = Head->next->prev;
        iter = Head->next;
        iter->prev = tmp->prev;
        tmp->prev->next = iter;
        *dato = tmp->value;
        printf("elemento estratto: %d\n", *dato);
        free(tmp);
        return;
    }
}
void preleva_elem_desiderato(Lista_DCL* Head, int* dato, int key){
    Nodo_DCL* tmp, *iter;
    if(!Head->next){
        printf("La lista è vuota impossibile estrarre elemento\n ");
        return;
    }
    else if(Head->next == Head->next->prev){
        if(Head->next->value != key){
            printf("elemento non presente in lista, impossibile estrarlo\n");
            return;
        }
        else{
            tmp = Head->next;
            *dato = Head->next->value;
            printf("elemento estratto: %d\n", *dato);
            free(Head->next);
            Head->next = NULL;
            return;
        }
    }
    else{
        tmp = NULL;
        iter = Head->next;
        while(iter->next != Head->next && iter->value != key)
            iter = iter->next;
        if(iter->value != key){
            printf("elemento non presente in lista, impossibile estrarlo\n");
            return;
        }
        else{
            if(iter == Head->next){
                preleva_in_testa(Head, dato); 
                return;
            }
            else{
                tmp = iter;
                tmp->prev->next = iter->next;
                iter->next->prev = tmp->prev;
                *dato = tmp->value;
                printf("elemento estratto: %d\n", *dato);
                free(tmp);
                return;
            }
        }
    }
}
Nodo_DCL* search_node(Lista_DCL* Head, int key){
    Nodo_DCL* tmp, *iter;
    if(!Head->next){
        printf("lista vuota impossibile cercare nodo\n");
        return NULL;
    }  
    else if(Head->next == Head->next->prev){
        if(Head->next->value == key){
            printf("elemento trovato!\n");
            return Head->next;
        }
        else{
            printf("elemento non presnte in lista\n");
            return NULL;
        }
    }
    else{
        iter = Head->next;
        while(iter->next != Head->next && iter->value != key)
            iter = iter->next;
        if(iter->next == Head->next){
            if(iter->value == key){
                printf("elemento trovato\n");
                return iter;
            }
            else{
                printf("elemento non presente in lista\n");
                return NULL;
            }
        }
        else{
            if(iter->value == key){
                printf("elemento trovato\n");
                return iter;
            }
            else{
                printf("elemento non presente in lista\n");
                return NULL;
            }
        }
    }
}
void inserisci_dopo_elem(Lista_DCL* Head, int elem, int key){
    Nodo_DCL* tmp, *iter;
    if(!Head->next){
        printf("lista vuota impossibile allocare dopo l'elemento desiderato\n");
        return;
    }
    else{
        iter = search_node(Head, key);
        if(!iter){
            printf("l'elemento %d non è presente nella lista impossibile allocare nodo\n", key);
            return;
        }
        else{
            if(iter->next == Head->next && iter->prev == Head->next){//se la lista ha solo il nodo cercato
                inserisci_in_coda(Head, elem);
                return;
            }
            else if(iter->next == Head->next && iter->prev != Head->next){// se l'elemento "precedente" è in ultima posizione
                inserisci_in_coda(Head, elem);
            }
            else{
                tmp = makenode(elem);
                if(tmp){
                    tmp->prev = iter;
                    tmp->next = iter->next;
                    iter->next->prev = iter;
                    iter->next = tmp;
                }
                return;
            }
        }
    }
}
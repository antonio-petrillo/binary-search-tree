#include "circular_singular_list.h"
#include <stdio.h>
#include <stdlib.h>

void makelist(Lista_SCL* Head){
    Head->next = NULL;
    return;
}
Nodo_SCL* makenode(int elem){
    Nodo_SCL* newnode = (Nodo_SCL*) malloc (sizeof(Nodo_SCL));
    if(newnode){
        newnode->next = NULL;
        newnode->value = elem;
        newnode->start_of_the_list = 0;
    }
    else{
        printf("impossibile allocare nodo, memoria insufficiente\n");
        return NULL;
    }
}
// 1==> testa della lista  
// 0==> non è la testa della lista;
void inserisci_in_testa(Lista_SCL* Head, int elem){
    Nodo_SCL* tmp, *iter;
    if(!Head->next){//se la lista è vuota il nodo va in prima posizione ed il ptr al nextnode punterà a se stesso
        tmp = makenode(elem);
        if(tmp){//in questo caso il ptr next è ancora NULL occorre cambiarlo manualmente
            Head->next = tmp;
            tmp->next = Head->next;
            tmp->start_of_the_list = 1;
        }
        return;
    }
    else{//il problema è aggiornare l'ultimo nodo, il quale punta sempre a se stesso
        tmp = makenode(elem);
        if(tmp){
            tmp->next = Head->next;
            tmp->start_of_the_list = 1;
            Head->next->start_of_the_list = 0;
            iter = Head->next;
            while(iter->next != Head->next)
                iter = iter->next;
            iter->next = tmp;
            Head->next = tmp;
        }
        return;
    }
}
void inserisci_in_coda(Lista_SCL* Head, int elem){
    Nodo_SCL* tmp, *iter;
    if(!Head->next){//lista vuota
        tmp = makenode(elem);
        if(tmp){
            Head->next = tmp;
            tmp->next = tmp;
            tmp->start_of_the_list = 1; 
        }
        return;
    }
    else{
        tmp = makenode(elem);
        if(tmp){
            iter = Head->next;
            while(iter->next != Head->next)
                iter = iter->next;
            iter->next = tmp;
            tmp->next = Head->next;
        }
        return;
    }
}
void inserimento_ordinato(Lista_SCL* Head, int elem){
    Nodo_SCL *tmp, *prev, *curr;
    if(!Head->next){//se la lista è vuota
        tmp = makenode(elem);
        if(tmp){
            Head->next = tmp;
            tmp->next = Head->next;
            tmp->start_of_the_list = 1;
        }
    }
    else{//se la lista non è vuota
        prev = NULL;
        curr = Head->next;
        while(curr->next != Head->next && elem > curr->value){
            prev = curr;
            curr = curr->next;
        }
        if(!prev && elem <= curr->value){//se il ptr al nodo precedente è null ed il
        // valore da inserire è più piccolo della lista effettuo un inserimento in testa
            inserisci_in_testa(Head, elem);
            return;
        }
        else if(curr->next == Head->next && elem > curr->value){
            inserisci_in_coda(Head, elem);
            return;
        }
        else{
            tmp = makenode(elem);
            if(tmp){
                tmp->next = curr;
                prev->next = tmp;
            }
            return;
        }
    }
}
void stampalista(Lista_SCL* Head){
    if(!Head->next){
        printf("la lista è vuota\n");
        return;
    }
    else{
        Nodo_SCL* iter;
        iter = Head->next;
        printf("[Lista Circolare: Head] %d -> ", iter->value);
        iter = iter->next;
        while(iter->start_of_the_list != 1){
            printf("%d -> ", iter->value);
            iter = iter->next;
        }
        printf(" [%d]-|\n", Head->next->value);
        return;
    }
}
void stampalista_molteplice(Lista_SCL* Head, int num_stampe){
    int counter = 0;
    if(!Head->next){
        printf("la lista è vuota\n");
        return;
    }
    else{
        printf("stampa molteplice (%d) di una lista circolare  \n", num_stampe);  
        printf("[Lista Circolare: Head]:");
        while(counter < num_stampe){
            Nodo_SCL* iter;
            iter = Head->next;
            printf(" %d -> ", iter->value);
            iter = iter->next;
            while(iter->start_of_the_list != 1){
                printf("%d -> ", iter->value);
                iter = iter->next;
            }
            counter++;
        }
        printf(" [%d]-|\n", Head->next->value);
            return;
    }
}
void freelist(Lista_SCL* Head){
    Nodo_SCL* tmp, *iter;
    if(!Head->next){
        printf("la lista è già vuota, imposibile deallocarla\n");
        return;
    }
    else{
        printf("eliminazione della lista circolare...\n");
        iter = Head->next->next;//inizio a cancellare dal secondo elemento fino a ritrovarmi di nuovo sulla testa
        while(iter->start_of_the_list != 1/*Head->next->start_of_the_list*/){
            tmp = iter;
            iter = iter->next;
            printf("elimino: %d\n", tmp->value);
            free(tmp);
        }//l'ultimo elemento da deallocare è la testa
        printf("elimino: %d\n", iter->value);
        free(iter);
        Head->next = NULL;
        return;
    }
}
void preleva_in_testa(Lista_SCL* Head, int* dato){
    Nodo_SCL* tmp, *iter;
    if(!Head->next){
        printf("lista vuota impossibile estrarre elemento \n");
        return;
    }
    else{
        tmp = Head->next;
        if(tmp == tmp->next){
            *dato = tmp->value;
            printf("elemento estratto: %d\n", *dato);
            free (tmp);
            Head->next = NULL;
            return;
        }
        else{
            iter = tmp->next;
            while(iter->next != Head->next)
                iter = iter->next;
            iter->next = tmp->next;
            *dato = tmp->value;
            Head->next = tmp->next;
            Head->next->start_of_the_list = 1;
            printf("elemento estratto: %d\n", *dato);
            free(tmp);
            return;
        }
    }
}
void preleva_in_coda(Lista_SCL* Head, int* dato){
    Nodo_SCL *tmp, *iter;
    if(!Head->next){
        printf("lista vuota impossibile estrarre elemento \n");
        return;
    }
    else{
        tmp = Head->next;
        if(tmp->next == tmp){
            *dato = tmp->value;
            printf("elemento estratto: %d\n", *dato);
            free(tmp);
            Head->next = NULL;
            return;
        }
        else{
            iter = tmp;
            while(iter->next->next != Head->next)
                iter = iter->next;
            tmp = iter->next;
            *dato = tmp->value;
            printf("elemento estratto: %d\n", *dato);
            iter->next = Head->next;
            free(tmp);
            return;
        }
    }
}
void preleva_elem_desiderato(Lista_SCL* Head, int* dato, int key){
    Nodo_SCL* tmp, *iter, *prev;
    if(!Head->next){
        printf("la lista è vuota impossibile cercare elemento\n");
        return;
    }
    else{//non posso usare la funzione searchnode perché mi serve il nodo precedente a quello da eliminare
        iter = Head->next;
        prev = NULL;
        if(iter->value == key){//se l'elem cercato è in testa
            preleva_in_testa(Head, dato);
            return;
        }
        else{
            while(iter->next != Head->next && iter->value != key){
                prev = iter;
                iter = iter->next;
            }
            if(iter->next == Head->next && iter->value == key){//se l'elem cercato è in coda
                preleva_in_coda(Head, dato);
                return;
            }
            else if(iter->next == Head->next && iter->value != key){
                printf("elemento non presente in lista, impossibile estrarlo\n");
                return;
            }
            else{//elemento da estrarre in posizione centrale della lista   NB:--> iter->value == key
                tmp = iter;
                prev->next = iter->next;
                *dato = tmp->value;
                printf("elemento estratto: %d\n", *dato);
                free(tmp);
                return;
            }
        }
    }
}
Nodo_SCL* search_node(Lista_SCL* Head, int key){
    Nodo_SCL* tmp;
    if(!Head->next){
        printf("lista vuota impossibile cercare nodo\n");
        return NULL;
    }
    else{
        tmp = Head->next;
        while(tmp->next != Head->next && tmp->value != key)
            tmp = tmp->next;
        if(tmp->next == Head->next && tmp->value != key){
            printf("elemento non presente in lista\n");
            return NULL;
        }
        else
            return tmp;
    }
}
void inserisci_dopo_elem(Lista_SCL* Head, int elem, int key){
    Nodo_SCL* tmp, *iter;
    iter = search_node(Head, key);
    if(iter){
        if(iter->next == Head->next){
            inserisci_in_coda(Head, elem);
            return;
        }
          else{
            tmp = makenode(elem);
            if(tmp){
                tmp->next = iter->next;
                iter->next = tmp;
            }
            return;
        }
    }
    else{
        printf("impossibile posizionare il nodo e quindi vaffanculo\n");
        return;
    }
    
}
/**
* Piccolo appunto sulle liste circolari:
*   -Non si ha bisogno di 2 "iteratori" per cercare la posizione in una lista circolare, 
*    basta scorrere la lista fino a quando il nodo successivo all'iteratore non sia uguale
*    al nodo cercato 
*    ESEMPIO:
*        -while(iter->next != <indirizzo del valore che cerco>)
*           iter = iter->next;
*   -Si può utilizzare questo metodo proprio per la natura circolare di questo tipo di lista
*    infatti dato che "l'ultimo" nodo punta al primo posso scorrere la lista quante volte
*    serve fino a trovare il nodo precedente al nodo cercato
*   -IPP (In Poche Parole):
*    dovrei riscrivere la funzione per l'inserimento ordinato e forse un'altra,
*    ma non ho un cazzo voglia di farlo...
*/
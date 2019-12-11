#include <stdio.h>
#include "list_sl.h"

int main(int argc, char const *argv[])
{
    Lista lista;
    char c;
    lista = crealista();
    printf("inserimento in testa\n\n");
    //printf("inserisci un carattere\n");
    printf("inserisci una stringa\n");
    scanf("%c", &c);
    //getchar();
    while(c != '0'){
        lista = inserisci_nodo_in_testa(lista, c);
        scanf("%c", &c);
        //getchar();
    }
    printf("stampa lista\n\n");
    print_list(lista);
    delete_list(&lista);
    printf("stampa dopo delete_list\n\n");
    print_list(lista);
    c = getchar();
    printf("inserimento in coda\n\n"); //inserimento in coda
    //printf("inserisci un carattere\n");
    printf("inserisci una stringa\n");
    scanf("%c", &c);
    //getchar();
    while(c != '0'){
        lista = inserisci_nodo_in_coda(lista, c);
        scanf("%c", &c);
        //getchar();
    }
    printf("stampa lista\n\n");
    print_list(lista);
    delete_list(&lista);
    printf("stampa dopo delete_list\n\n");
    print_list(lista);
    printf("inserimento in ordinato\n\n"); //inserimento in ordinato
    //printf("inserisci un carattere\n");
    printf("inserisci una stringa\n");
    scanf("%c", &c);
    //getchar();
    while(c != '0'){
        lista = inserisci_nodo_ordinato(lista, c);
        scanf("%c", &c);
        //getchar();
    }
    printf("stampa lista\n\n");
    print_list(lista);
    delete_list(&lista);
    printf("stampa dopo delete_list\n\n");
    print_list(lista);
    free (lista);
    return 0;
}

Lista crealista(){
    return NULL;
}
Lista inserisci_nodo_in_testa (Lista head, char elem){
    Node* newnode = crea_nodo(elem);
    if(!newnode){
        printf("impossibile allocare nodo\n");
        return NULL;
    }
    else{
        if(!head){
            head = newnode;
            return head;
        }
        else{
            newnode->nextptr = head;
            return newnode;
        }
    }

}
Node* crea_nodo(char elem){
    Node* newnode = (Node*) malloc (sizeof(Node));
    if(!newnode) return NULL;
    else{
        newnode->value = elem;
        newnode->nextptr = NULL;
        return newnode;
    }
}
void print_list(Lista head){
    Lista p = head;
    if(p == NULL) printf("la lista è vuota\n");
    while(p != NULL){
        //printf("valore del nodo: %c\n", p->value);
        printf("%c", p->value);
        p = p->nextptr;
    }
    puts("");
}
void delete_list(Lista* head){
    Lista curr = *head;
    Lista next;
    while(curr != NULL){
        next = curr->nextptr;
        free(curr);
        curr = next;
    }
    *head = NULL;
}
Lista inserisci_nodo_in_coda (Lista head, char elem){
    Node* newnode = crea_nodo(elem);
    Node* curr;
    if(!newnode){
        printf("impossibile allocare nodo\n");
        return NULL;
    }
    else{
        if(!head){
            head = newnode;
            return head;
        }
        else{
            curr = head;
            while(curr->nextptr != NULL){
                curr = curr->nextptr;
            }
            curr->nextptr = newnode;
            return head;
        }
    }
}
Lista inserisci_nodo_ordinato (Lista head, char elem){
    Node* newnode = crea_nodo(elem);
    Node* curr, *prev;
    if(!newnode){
        printf("impossibile allocare nodo\n");
        return NULL;
    }
    else{
        if(!head){
            head = newnode;
            return head;
        }
        else{
            curr = head;
            while(curr != NULL && elem > curr->value){
                prev = curr;
                curr = curr->nextptr;
            }
            prev->nextptr = newnode;
            newnode->nextptr = curr;
            return head;
        }
    }
}
void delete_node(Lista* head, char key){
    if(!(*head)){
        printf("la lista è vuota, impossibile trovare l'elemento");
        return;
    }
    else{
        if((*head)->value == key){
            printf("elemento trovato\n");
            free (*head);
        }
        else{
            Lista* prev, *curr;
            prev = head;
            curr = (*head) -> nextptr;
            while(curr != NULL && (*curr)->value != key){
                prev = curr;
                curr = (*curr)->nextptr;
            } 
            if(curr != NULL){
                printf("elemento trovato");
                Lista* tmp = curr;
                (*prev)->nextptr = (*curr)->nextptr;
                free(tmp);
                return;
            }
        }
        
    }
}
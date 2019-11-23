#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "queue.h"
#include "stack.h"

// funzioni per la gestione delle strutture dati
// la maggior parte delle funzioni sotto elencate servono da supporto per le funzioni ricorsive

void error(char* message){
    printf("%s\n", message);
    exit(0);
}

void maketree(BST* tree){
    tree->root = NULL;
}

NodePtr makenode(int key){
    NodePtr newnode = (NodePtr) malloc(sizeof(Node));
    if(!newnode) error("impossibile allocare il nodo");
    newnode->value = key;
    newnode->right = newnode->left = NULL;
    return newnode;
}

BST insert(BST tree, int key){
    if(tree.root) insert_rc(tree.root, key, NULL);
    else tree.root = makenode(key);
    return tree;
}

NodePtr search(BST tree, int key){
    NodePtr tmp = NULL;
    if(tree.root){
        if(tree.root->value == key) return tree.root;
        else if(tree.root->value > key) search_support(tree.root->left, key, &tmp);
        else search_support(tree.root->right, key, &tmp);
    }
    return tmp;
}

BST delete_node(BST tree, int key){
    if(tree.root){
        if(tree.root->value == key){
            tree.root = delete_root(tree.root);
        }else{
            if(tree.root->value > key)
                delete_node_rc(tree.root->left, key, tree.root);
            else
                delete_node_rc(tree.root->right, key, tree.root);
        }
    }
    return tree;
}

NodePtr delete_root(NodePtr T){
    if(T){
        NodePtr tmp;
        if(!(T->left) || !(T->right)){
            tmp = T;
            if(T->left) T=T->left;
            else T=T->right;
            free(tmp);
        }else{
            tmp = minimum_disconnection(T->right, T);
            T->value = tmp->value;
            free(tmp);
        }
    }
    return T;
}

NodePtr find_minimum_from_tree(BST tree){
    if(tree.root){
        if(tree.root->left) return find_minimum(tree.root->left);
        else return tree.root;
    }else 
        return NULL;
}

NodePtr find_maximum_from_tree(BST tree){
    if(tree.root){
        if(tree.root->right) return find_maximum(tree.root->right);
        else return tree.root;
    }else 
        return NULL;
}

NodePtr successor(BST tree, int key){
    NodePtr tmp = NULL;
    if(tree.root){
        if(tree.root->value == key) return find_minimum(tree.root->right);
        else if(tree.root->value > key) successor_support(tree.root->left, key, &tmp);
        else successor_support(tree.root->right, key, &tmp);
    }
    return tmp;
}

BST delete_tree(BST tree){
    if(tree.root) tree.root = delete_all_node(tree.root);
    return tree;
}

int is_BST(BST tree, int inf, int sup){//controlla anche che tutti i nodi rientrino nell'intervallo [a,b]
    if(tree.root){
        if(tree.root->value < inf || tree.root->value > sup) return 0;
        else 
            return check_is_BST(tree.root->left, inf, tree.root->value) * check_is_BST(tree.root->right, tree.root->value, sup); 
    }
    else return 1;
}

void visit(BST tree, void (*visit_mode)(NodePtr node)){
    if(visit_mode == visit_in_order){
        //printf("visita in modalita' in-order");
        visit_mode(tree.root);
    }else if(visit_mode == visit_pre_order){
        //printf("visita in modalita' pre-order");
        visit_mode(tree.root);
    }else if(visit_mode == visit_post_order){
        //printf("visita in modalita' post-order");
        visit_mode(tree.root);
    }
    puts("");
}

void iterative_visit(BST tree, void (*visit_mode)(BST tree)){
    if(visit_mode == iterative_visit_in_order){
        //printf("visita in modalita' in-order iterativo");
        visit_mode(tree);
    }else if(visit_mode == iterative_visit_pre_order){
        //printf("visita in modalita' pre-order iterativo");
        visit_mode(tree);
    }else if(visit_mode == iterative_visit_post_order){
        //printf("visita in modalita' post-order iterativo");
        visit_mode(tree);
    }else if(visit_mode == visit_in_amplitude){
        //printf("visita in modalita' in-amplitude");
        visit_mode(tree);
    }
    puts("");
}

int count(BST tree){
    if(!tree.root) return 0;
    else return 1 + count_nodes(tree.root->left) + count_nodes(tree.root->right);
}

//funzioni ricorsive

void insert_rc(NodePtr T, int key, NodePtr P){
    if(T){
        if(T->value > key && T->value != key) insert_rc(T->left, key, T);
        else if(T->value < key && T->value != key) insert_rc(T->right, key, T);
    }
    else{
        if(P){
            NodePtr newnode = makenode(key);
            if(P->value > key) P->left = newnode;
            else P->right = newnode;
        }
    }
}

void search_support(NodePtr node, int key, NodePtr* ret){
    if(node){
        if(node->value > key) search_support(node->left, key, ret);
        else if(node->value < key) search_support(node->right, key, ret);
        else *ret = node;
    }
    return;
}

void delete_node_rc(NodePtr T, int key, NodePtr P){
    if(T){
        if(T->value > key)
            delete_node_rc(T->left, key, T);
        else if(T->value < key)
            delete_node_rc(T->right, key, T);
        else{
            if(P->left == T) P->left = delete_root(T);
            else P->right = delete_root(T);
        }
    }
    return;
}

NodePtr minimum_disconnection(NodePtr T, NodePtr P){
    if(T){
        if(T->left) return minimum_disconnection(T->left, T);
        else
            if(P->left == T) P->left = T->right;
            else P->right = T->right;
    }
    return T;
}

NodePtr find_minimum(NodePtr node){
    if(node){
        if(node->left) return find_minimum(node->left);
        else return node;
    }
    return NULL;
}

NodePtr find_maximum(NodePtr node){
    if(node){
        if(node->right) return find_maximum(node->right);
        else return node;
    }
    return NULL;
}

void successor_support(NodePtr T, int key, NodePtr* P){
    if(T){
        if(T->value == key) *P = find_minimum(T->right);
        else {
            if (T->value < key) successor_support(T->right, key, P);
            else successor_support(T->left, key, P);
        }
    }
    return;
}

NodePtr delete_all_node(NodePtr node){
    if(node){
        node->left = delete_all_node(node->left);
        node->right = delete_all_node(node->right);
        free(node);
    }
    return NULL;
}

int check_is_BST(NodePtr node, int inf, int sup){
    if(node){
        if(node->value < inf || node->value > sup) return 0;
        else 
            return check_is_BST(node->left, inf, node->value) * check_is_BST(node->right, node->value, sup);
    }
    else return 1;
}

void visit_in_order(NodePtr node){
    if(!node) return;
    visit_in_order(node->left);
    printf("%4d", node->value);
    visit_in_order(node->right);
}

void visit_post_order(NodePtr node){
    if(node){
        visit_post_order(node->left);
        visit_post_order(node->right);
        printf("%4d", node->value);
    }
}

void visit_pre_order(NodePtr node){
    if(node){
        printf("%4d", node->value);        
        visit_pre_order(node->left);
        visit_pre_order(node->right);
    }
}

int count_nodes(NodePtr node){
    if(node) return 1 + count_nodes(node->left) + count_nodes(node->right);
    return 0;
}

//funzioni iterative

void visit_in_amplitude(BST tree){
    Queue q;
    makequeue(&q);
    NodePtr tmp;
    enqueue(&q, tree.root);
    while(q.head){
        tmp = dequeue(&q);
        printf("%4d", tmp->value);
        if(tmp->left) enqueue(&q, tmp->left);
        if(tmp->right) enqueue(&q, tmp->right);
    }
}

BST iterative_insertion(BST tree, int key){
    NodePtr iter = tree.root;
    NodePtr prev = NULL;
    while(iter){
        prev = iter;
        if(iter->value > key) iter = iter->left;
        else if(iter->value < key) iter = iter->right;
        else break;
    }
    if(!prev) tree.root = makenode(key);
    else{
        NodePtr tmp = makenode(key);
        if(prev->value > key) prev->left = tmp;
        else if(prev->value < key) prev->right = tmp;
        //altrimenti non fai nulla dato che il valore e' gia' presente nell'albero 
    }
    return tree;
}

BST iterative_delete_node(BST tree, int key){
    NodePtr iter = tree.root;
    NodePtr prev = NULL;
    while(iter && iter->value != key){
        prev = iter;
        if(iter->value > key) iter = iter->left;
        else if(iter->value < key) iter = iter->right;
        else break;
    }
    if(prev){
        if(iter){
            if(prev->left == iter) prev->left = delete_root(iter);
            else prev->right = delete_root(iter);
        }
    }else{
        if(iter) iter = delete_root(iter);
    }
    return tree;
}

void iterative_visit_pre_order(BST tree){
    NodePtr iter = tree.root;
    NodePtr prev = NULL;
    Stack s;
    makestack(&s);
    while(iter || is_empty(s)){
        if(iter){
            printf("%4d", iter->value);
            push(&s, iter);
            iter = iter->left;
        }else{
            iter = top(s);
            if(prev != iter->right && iter->right) iter = iter->right;
            else{
                prev = iter;
                pop(&s);
                iter = NULL;
            }
        }
    }
}

void iterative_visit_in_order(BST tree){
    NodePtr iter = tree.root;
    NodePtr prev = NULL;
    Stack s;
    makestack(&s);
    while(iter || is_empty(s)){
        if(iter){
            push(&s, iter);
            iter = iter->left;
        }else{
            iter = top(s);
            if(prev != iter->right && iter->right){ 
                printf("%4d", iter->value);
                iter = iter->right;
            }
            else{
                if(!(iter->right)) printf("%4d", iter->value);   
                prev = iter;
                pop(&s);
                iter = NULL;
            }
        }
    }
}

void iterative_visit_post_order(BST tree){
    NodePtr iter = tree.root;
    NodePtr prev = NULL;
    Stack s;
    makestack(&s);
    while(iter || is_empty(s)){
        if(iter){
            push(&s, iter);
            iter = iter->left;
        }else{
            iter = top(s);
            if(prev != iter->right && iter->right) iter = iter->right;
            else{
                printf("%4d", iter->value);
                prev = iter;
                pop(&s);
                iter = NULL;
            }
        }
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "bst.h"

int main(int argc, char** argv){
    BST tree;
    maketree(&tree);

    //inserimento ricorsivo

    /*tree = insert(tree, 5);
    tree = insert(tree, 3);
    tree = insert(tree, 9);
    tree = insert(tree, 6);
    tree = insert(tree, 10);
    tree = insert(tree, 4);
    tree = insert(tree, 2);
    tree = insert(tree, 5);*/
    
    //inserimento iterativo

    tree = iterative_insertion(tree, 5);
    tree = iterative_insertion(tree, 3);
    tree = iterative_insertion(tree, 9);
    tree = iterative_insertion(tree, 6);
    tree = iterative_insertion(tree, 10);
    tree = iterative_insertion(tree, 4);
    tree = iterative_insertion(tree, 2);
    tree = iterative_insertion(tree, 5);

    //visit_in_order(tree.root);
    //puts("");
    
    visit(tree, visit_in_order);

    //cancellazione di un nodo ricorsivamente
    
    /*tree = delete_node(tree, 10);
    tree = delete_node(tree, 2);
    tree = delete_node(tree, 3);
    tree = delete_node(tree, 9);
    tree = delete_node(tree, 5);
    tree = delete_node(tree, 4);
    tree = delete_node(tree, 6);*/

    //cancellazione di un nodo in modo ricorsivo

    /*tree = iterative_delete_node(tree, 5);
    tree = iterative_delete_node(tree, 5);
    tree = iterative_delete_node(tree, 4);
    tree = iterative_delete_node(tree, 6);
    tree = iterative_delete_node(tree, 10);
    
    visit(tree, visit_in_order);*/

    NodePtr max = find_maximum_from_tree(tree);
    NodePtr min = find_minimum_from_tree(tree);
    NodePtr succ = successor(tree, 5);
    NodePtr valore = search(tree, 6);
    if(min) printf("il minimo e': %d\n", min->value);
    else printf("la funzione ha ritornato NULL\n");
    if(max) printf("il massimo e': %d\n", max->value);
    else printf("la funzione ha ritornato NULL\n");
    if(succ) printf("il successore e': %d\n", succ->value);
    else printf("la funzione ha ritornato NULL\n");
    if(valore) printf("il valore cercato e': %d\n", valore->value);
    else printf("la funzione ha ritornato NULL\n");
    visit(tree, visit_in_order);
    visit(tree, visit_post_order);
    visit(tree, visit_pre_order);
//    tree = delete_tree(tree);
//    visit(tree, visit_in_order);
    iterative_visit(tree, visit_in_amplitude);

    //tree.root->left->left->left = makenode(100); forzo l'abr a perdere le sue proprieta' per vedere se funziona is_BST
    printf("l'albero su cui lavoriamo e' un ABR?\n?: %d\n", is_BST(tree, -1, 10));
    
    printf("l'albero ha %d nodi\n", count(tree));
    iterative_visit(tree, iterative_visit_pre_order);
    iterative_visit(tree, iterative_visit_post_order);
    iterative_visit(tree, iterative_visit_in_order);
    iterative_visit(tree, visit_in_amplitude);

    return 0;
}
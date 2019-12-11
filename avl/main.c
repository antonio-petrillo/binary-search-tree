#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "avl.h"

#define randomize srand(time(NULL))
#define random(x) rand()%x

int main(int argc, char** argv){
    AVL tree;
    makeAVL(&tree);
    randomize;
    //for(int i=0; i<15; i++) tree = insert_in_AVL(tree, random(40));
    tree = insert_in_AVL(tree, 10);
    tree = insert_in_AVL(tree, 1);
    tree = insert_in_AVL(tree, 2);
    tree = insert_in_AVL(tree, 9);
    tree = insert_in_AVL(tree, 7);
    tree = insert_in_AVL(tree, 5);
    tree = insert_in_AVL(tree, 13);
    tree = insert_in_AVL(tree, 4);
    tree = insert_in_AVL(tree, 17);
    tree = insert_in_AVL(tree, 19);
    tree = insert_in_AVL(tree, 42);
    in_order(tree.root);
    puts("");

    tree = delete_node_in_AVL(tree, 10);
    in_order(tree.root);
    puts("");

    tree = delete_node_in_AVL(tree, 9);
    in_order(tree.root);
    puts("");

    tree = delete_node_in_AVL(tree, 19);
    in_order(tree.root);
    puts("");

    tree = delete_node_in_AVL(tree, 42);
    in_order(tree.root);
    puts("");

    tree = delete_node_in_AVL(tree, 5);
    in_order(tree.root);
    puts("");

    tree = delete_node_in_AVL(tree, 100);
    in_order(tree.root);
    puts("");
    return 0;
}
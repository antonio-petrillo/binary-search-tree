#include <stdio.h>
#include <stdlib.h>
#include "rbtree.h"

int main(int argc, char** argv){
    RB_tree tree;
    maketree(&tree);
    tree = insert_in_tree(tree, 10);
    tree = insert_in_tree(tree, 19);
    tree = insert_in_tree(tree, 82);
    tree = insert_in_tree(tree, 7);
    tree = insert_in_tree(tree, 6);
    tree = insert_in_tree(tree, 5);
    tree = insert_in_tree(tree, 9);
    tree = insert_in_tree(tree, 13);
    tree = insert_in_tree(tree, 20);
    tree = insert_in_tree(tree, 8);
    breadth_visit(tree);    
    tree = delete_node_from_tree(tree, 8);
    tree = delete_node_from_tree(tree, 10);
    tree = delete_node_from_tree(tree, 19);
    tree = delete_node_from_tree(tree, 7);
    tree = delete_node_from_tree(tree, 20);
    tree = delete_node_from_tree(tree, 42);
    breadth_visit(tree);
    drop_tree(tree); 
    return 0;
}
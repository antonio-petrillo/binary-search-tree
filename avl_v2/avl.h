#ifndef AVL_H
#define AVL_H

#include <stdlib.h>

typedef struct avl_node{
    int key;
    size_t height;
    struct avl_node* left;
    struct avl_node* right;
}* avl_node;

typedef struct avl_tree{
    avl_node root;
}* avl_tree;

avl_tree make_avl();
void insert_avl(avl_tree* tree, int key);
void delete_avl(avl_tree* tree, int key);
void drop_avl(avl_tree* tree);
void print_avl(avl_tree tree);


#endif

#include <stdio.h>
#include <stdlib.h>
#include "avl.h"


avl_tree make_avl(){
    avl_tree tree = (avl_tree) malloc(sizeof(struct avl_tree));
    if(!tree){
        printf("error in make_avl, abort.");
        exit(EXIT_FAILURE);
    }
    tree->root = NULL;
    return tree;
}

static avl_node make_node(int key){
    avl_node node = (avl_node) malloc(sizeof(struct avl_node));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

static size_t height(avl_node node){
    int height = 0;
    if(node){
        height = node->height;
    }
    return height;
}

static size_t max_height(avl_node left, avl_node right){
   size_t h_left = height(left);
   size_t h_right = height(right);
   return h_left > h_right ? h_left : h_right;
}

static avl_node single_left_rotate(avl_node node){
    avl_node pivot = node->right;
    node->right = pivot->left;
    pivot->left = node;
    node->height = max_height(node->left, node->right) + 1;
    pivot->height = max_height(pivot->left, pivot->right);
    return pivot;
}

static avl_node single_right_rotate(avl_node node){
    avl_node pivot = node->left;
    node->left = pivot->right;
    pivot->right = node;
    node->height = max_height(node->left, node->right) + 1;
    pivot->height = max_height(pivot->left, pivot->right);
    return pivot;
}

static avl_node double_left_rotate(avl_node node){
    node->right = single_right_rotate(node->right);
    node = single_left_rotate(node);
    return node;
}

static avl_node double_right_rotate(avl_node node){
    node->left = single_left_rotate(node->left);
    node = single_right_rotate(node);
    return node;
}

static int is_single_left(avl_node node){
    return height(node->left) > height(node->right) ? 1 : 0;
}

static avl_node balance_left(avl_node node){
    size_t bigger,smaller;
    if(height(node->right) > height(node->left)){
        bigger = height(node->right);
        smaller = height(node->left);
    }else{
        bigger = height(node->left);
        smaller = height(node->right);

    }
    if(bigger - smaller > 1){
        if(is_single_left(node->left)){
            node = single_right_rotate(node);
        } else{
            node = double_right_rotate(node);
        }
    }else{
        printf("no violation\n");
    }
    return node;
}

static int is_single_right(avl_node node){
    return height(node->right) > height(node->left) ? 1 : 0;
}

static avl_node balance_right(avl_node node){
    size_t bigger,smaller;
    if(height(node->right) > height(node->left)){
        bigger = height(node->right);
        smaller = height(node->left);
    }else{
        bigger = height(node->left);
        smaller = height(node->right);

    }
    if(bigger - smaller > 1){
        if(is_single_right(node->right)){
            node = single_left_rotate(node);
        }else{
            node = double_left_rotate(node);
        }
    }else{
        printf("no violation\n");
    }
    return node;
}

static avl_node insert_helper(avl_node node, int key){
    if(node){
        if(node->key > key){
           node->left = insert_helper(node->left, key);
           node = balance_left(node);
        }else if(node->key < key){
           node->right = insert_helper(node->right, key);
           node = balance_right(node);
        }else{
            // ignore operation
            printf("key already present into the avl, abort insertion");
        }
        node->height = max_height(node->left, node->right) + 1;
    }else{
        node = make_node(key);
    }
    return node;
}

void insert_avl(avl_tree* tree, int key){
    (*tree)->root = insert_helper((*tree)->root, key);
    return;
}

avl_node minimum_deconnection(avl_node child, avl_node parent){
    avl_node tmp = NULL;
    if(child->left != NULL){
       tmp = minimum_deconnection(child->left, child);
       child->height = max_height(child->left, child->right) + 1;
       child = balance_right(child);
    }else{
        tmp = child;
        if(child == parent->left){
            parent->left = child->right;
        } else{
            parent->right = child->right;
        }
    }
    return tmp;
}

avl_node delete_root(avl_node node){
    avl_node tmp = NULL;
    if(!(node->left && node->right)){
        tmp = node;
        if(!node->left){
            node = node->right;
        }else{
            node = node->left;
        }
    }else{
        tmp = minimum_deconnection(node->right, node);
        node->height = max_height(node->left, node->right) + 1;
        node->key = tmp->key;
        node = balance_left(node);
    }
    free(tmp);
    return node;
}

avl_node delete_helper(avl_node node, int key){
    if(node){
        if(node->key > key){
            node->left = delete_helper(node->left, key);
            node = balance_right(node);
            node->height = max_height(node->left, node->right) + 1;
        }else if(node->key < key){
            node->right = delete_helper(node->right, key);
            node = balance_left(node);
            node->height = max_height(node->left, node->right) + 1;
        }else{
            node = delete_root(node);
        }
    }
    return node;
}

void delete_avl(avl_tree* tree, int key){
    (*tree)->root = delete_helper((*tree)->root, key);
    return;
}

avl_node drop_helper(avl_node node){
    if(node){
        node->left = drop_helper(node->left);
        node->right = drop_helper(node->right);
        free(node);
    }
    return NULL;
}

void drop_avl(avl_tree* tree){
    if(*tree){
        (*tree)->root = drop_helper((*tree)->root);
        free(*tree);
    }
    return;
}

void print_helper(avl_node node){
    if(node){
        printf("<key := %3d> | <height := %3lu>", node->key, node->height);
        if(node->left){
            printf(" | <left child := %3d>", node->left->key);
        }
        if(node->right){
            printf(" | <right child := %3d>", node->right->key);
        }
        puts("");
        print_helper(node->left);
        print_helper(node->right);
    }
}

void print_avl(avl_tree tree){
   print_helper(tree->root);
}

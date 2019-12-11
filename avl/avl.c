#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

void error(char* message){
    printf("%s\n", message);
    exit(0);
}

void makeAVL(AVL* tree){
    tree->root = NULL;
    return;
}

unsigned int max(unsigned int a,unsigned int b){
    return (a > b) ? a : b;
}

unsigned int height(AVLnode node){
    if(!node) return -1;
    else return node->height;
}

AVLnode makenode_AVL(int value){
    AVLnode newnode = (AVLnode) malloc(sizeof(Node));
    if(!newnode) error("impossibile alocare il nodo");
    newnode->height = 0;
    newnode->left = newnode->right = NULL;
    newnode->value = value;
    return newnode;
}

AVLnode SL_rotation(AVLnode pivot){
    if(pivot){
        AVLnode newroot = pivot->left;
        if(newroot){
            pivot->left = newroot->right;
            newroot->right = pivot;
            pivot->height = 1 + max(height(pivot->left), height(pivot->right));
            newroot->height = 1 + max(height(newroot->left), height(newroot->right));
            return newroot;
        }
    }
    return pivot;
}

AVLnode SR_rotation(AVLnode pivot){
    if(pivot){
        AVLnode newroot = pivot->right;
        if(newroot){
            pivot->right = newroot->left;
            newroot->left = pivot;
            pivot->height = 1 + max(height(pivot->left), height(pivot->right));
            newroot->height = 1 + max(height(newroot->left), height(newroot->right));
            return newroot;
        }
    }
    return pivot;
}

AVLnode DL_rotation(AVLnode pivot){
    pivot->left = SR_rotation(pivot->left);
    return SL_rotation(pivot);
}

AVLnode DR_rotation(AVLnode pivot){
    pivot->right = SL_rotation(pivot->right);
    return SR_rotation(pivot);
}

int is_SL(AVLnode pivot){
    return height(pivot->left) > height(pivot->right);
}

int is_SR(AVLnode pivot){
    return height(pivot->left) > height(pivot->right);
}

AVLnode left_balance(AVLnode node){
    if(node){
        if(height(node->left) - height(node->right) == 2){
            if(is_SL) node = SL_rotation(node);
            else node = DL_rotation(node);
        }
        else node->height = 1 + max(height(node->left), height(node->right)); 
    }
    return node;
}

AVLnode right_balance(AVLnode node){
    if(node){
        if(height(node->right) - height(node->left) == 2){
            if(is_SR) node = SR_rotation(node);
            else node = DR_rotation(node);
        }
        else node->height = 1 + max(height(node->left), height(node->right));
    }
    return node;
}

AVL insert_in_AVL(AVL tree, int value){
    tree.root = insert_node(tree.root, value);
    return tree;
}

AVLnode insert_node(AVLnode node, int value){
    if(!node) node = makenode_AVL(value);
    else{
        if(node->value > value){
            node->left = insert_node(node->left, value);
            node = left_balance(node);
        }
        else if(node->value < value){
            node->right = insert_node(node->right, value);
            node = right_balance(node);
        }
    }
    return node;
}

AVLnode delete_root(AVLnode node){
    if(node){
        AVLnode tmp;
        if(!(node->left) || !(node->right)){
            tmp = node;
            if(node->left) node = node->left;
            else node=node->right;
            free(tmp);
        }else{
            tmp = minimum_disconnection_AVL(node->right, node);
            node->value = tmp->value;
            free(tmp);
        }
    }
    return node;
}

AVLnode minimum_disconnection_AVL(AVLnode node, AVLnode prev){
    AVLnode ret = NULL, newroot;
    if(node){
        if(node->left){
            ret = minimum_disconnection_AVL(node->left, node); 
            newroot = right_balance(node);
        }else{
            ret = node;
            newroot = node->right;
        }    
        if(node == prev->left) prev->left = newroot;
        else prev->right = newroot;
    }
    return ret;
}

AVL delete_node_in_AVL(AVL tree, int key){
    if(tree.root) tree.root = delete_node(tree.root, key);
    return tree;
}

AVLnode delete_node(AVLnode node, int key){
    if(node){
        if(node->value > key){
            node->left = delete_node(node->left, key);
            node = right_balance(node);
        }
        else if(node->value < key){
            node->right = delete_node(node->right, key);
            node= left_balance(node);
        }else if(!(node->left) || !(node->right))
            node = delete_root(node);
        else{
            AVLnode tmp = minimum_disconnection_AVL(node->right, node);
            node->value = tmp->value;
            node = left_balance(node);
            free(tmp);
        }
    }
    return node;
}

void pre_order(AVLnode node){
    if(!node) return;
    printf("%4d", node->value);
    pre_order(node->left);
    pre_order(node->right);
}

void  in_order(AVLnode node){
    if(!node) return;
    in_order(node->left);
    printf("%4d", node->value);
    in_order(node->right);
}

AVL delete_all(AVL tree){
    if(tree.root)
        tree.root = delete_all_node (tree.root);
    return tree;
}

AVLnode delete_all_node(AVLnode node){
    if(node){
        node->left = delete_all_node(node->left);
        node->right = delete_all_node(node->right);
        free(node);
    }
    return NULL;
}
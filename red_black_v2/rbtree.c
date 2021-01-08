#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

int is_black(rbnode_t node){
    return node->color == BLACK;
}

int is_double_black(rbnode_t node){
    return node->color == DOUBLE_BLACK;
}

rbtree_t make_tree(){
    rbtree_t new_t = (rbtree_t) malloc(sizeof(struct rbtree));
    if(!new_t){
        printf("make_tree error\n");
        exit(EXIT_FAILURE);
    }
    new_t->NIL = (rbnode_t) malloc(sizeof(struct rbnode));
    if(!new_t->NIL){
        printf("make_tree (NIL) error\n");
        exit(EXIT_FAILURE);
    }
    new_t->NIL->left = new_t->NIL->right = new_t->NIL;
    new_t->NIL->color = BLACK;
    new_t->root = new_t->NIL;
    new_t->root->color = BLACK;
    return new_t;
}

rbnode_t make_node(int key, rbnode_t NIL){
    rbnode_t new_n = (rbnode_t) malloc(sizeof(struct rbnode));
    if(!new_n){
        printf("make_node error\n");
        exit(EXIT_FAILURE);
    }
    new_n->color = RED;
    new_n->left = new_n->right = NIL;
    new_n->key = key;
    return new_n;
}

rbnode_t left_rotate(rbnode_t node){
    rbnode_t pivot = node->right;
    node->right = pivot->left;
    pivot->left = node;
    return pivot;
}

rbnode_t right_rotate(rbnode_t node){
    rbnode_t pivot = node->left;
    node->left = pivot->right;
    pivot->right = node;
    return pivot;
}

static int detect_insert_violation_left(rbnode_t node){
    int type_insert_violation = 0;
    if(!is_black(node->right)){
        if(!is_black(node->left)){
            if(!is_black(node->left->left) || !is_black(node->left->right)){
                    type_insert_violation = 1;
                }
        }
    }else{//right child is black
        if(!is_black(node->left)){
            if(!is_black(node->left->right)){
                type_insert_violation = 2;
            }else if(!is_black(node->left->left)){
                type_insert_violation = 3;
            }
        }
    }
    return type_insert_violation;
}

static int detect_insert_violation_right(rbnode_t node){
    int type_insert_violation = 0;
    if(!is_black(node->left)){
        if(!is_black(node->right)){
            if(!is_black(node->right->left) || !is_black(node->right->right)){
                    type_insert_violation = 1;
                }
        }
    }else{//left child is black
        if(!is_black(node->right)){
            if(!is_black(node->right->left)){
                type_insert_violation = 2;
            }else if(!is_black(node->right->right)){
                type_insert_violation = 3;
            }
        }
    }
    return type_insert_violation;
}

static rbnode_t insert_fixup_left(rbnode_t node){
    switch(detect_insert_violation_left(node)){
        case 1:
            node->left->color = node->right->color = BLACK;
            node->color = RED;
            break;
        case 2:
            node->left = left_rotate(node->left);
        case 3:
            node = right_rotate(node);
            node->right->color = RED;
            node->color = BLACK;
            break;
    }
    return node;
}

static rbnode_t insert_fixup_right(rbnode_t node){
    switch(detect_insert_violation_right(node)){
        case 1:
            node->left->color = node->right->color = BLACK;
            node->color = RED;
            break;
        case 2:
            node->right = right_rotate(node->right);
        case 3:
            node = left_rotate(node);
            node->left->color = RED;
            node->color = BLACK;
            break;
    }
    return node;
}

static rbnode_t insert_helper(rbnode_t node, rbnode_t NIL, int key){
    if(node != NIL){
        if(node->key > key){
            node->left = insert_helper(node->left, NIL, key);
            node = insert_fixup_left(node);
        }else if(node->key < key){
            node->right = insert_helper(node->right, NIL, key);
            node = insert_fixup_right(node);
        }
        else{
            // update o ignora operazione
            // -- per semplicita' ignoro l'operazione
            printf("key already present, abort operation\n");
        }
    }else{
        node = make_node(key, NIL);
    }
    return node;
}

void insert(rbtree_t* t, int key){
   (*t)->root = insert_helper((*t)->root, (*t)->NIL, key);
   (*t)->root->color = BLACK;
}

static rbnode_t propagate_black(rbnode_t node){
    node->color = is_black(node) ? (node->color = DOUBLE_BLACK) : (node->color = BLACK);
   return node;
}

static int detect_delete_violation_left(rbnode_t node, rbnode_t NIL){
    int type_violation = 0;
    if(is_double_black(node->left)){
        printf("doppio nero  a sx\n");
        if(!is_black(node->right)){ // se il fratello del doppio nero e' rosso
           type_violation = 1;
        }else{
            if((node->right->left == NIL || is_black(node->right->left)) && (node->right->right == NIL || is_black(node->right->right))){
                type_violation = 2;
            }
            if(node->right->left != NIL && !is_black(node->right->left)){
                type_violation = 3;
            }
            if(node->right->right != NIL && !is_black(node->right->right)){
                type_violation = 4;
            }
        }
    }
    printf("detected %d (left)\n", type_violation);
    return type_violation;
}

static int detect_delete_violation_right(rbnode_t node, rbnode_t NIL){
    int type_violation = 0;
    if(is_double_black(node->right)){
        printf("doppio nero  a dx\n");
        if(!is_black(node->left)){
            type_violation = 1;
        }else{
            if((node->left->left == NIL || is_black(node->left->left)) && (node->left->right == NIL || is_black(node->left->right))){
                type_violation = 2;
            }
            if(node->left->right != NIL && !is_black(node->left->right)){
                type_violation = 3;
            }
            if(node->left->left != NIL && !is_black(node->left->left)){
                type_violation = 4;
            }
        }
    }
    printf("detected %d (right)\n", type_violation);
    return type_violation;
}

static rbnode_t delete_fixup_left(rbnode_t node, rbnode_t NIL){
    switch(detect_delete_violation_left(node, NIL)){
        case 1:
            printf("<fixup 1 left>\n");
            node = left_rotate(node);
            node->color = BLACK;
            node->left->color = RED;
            node->left = delete_fixup_left(node->left, NIL);
            break;
        case 2:
            printf("<fixup 2 left>\n");
            node->left->color = BLACK;
            node->right->color = RED;
            node = propagate_black(node);
            break;
        case 3:
            printf("<fixup 1 left>\n");
            node->right = right_rotate(node->right);
            node->right->color = BLACK;
            node->right->right->color = RED;
        case 4:
            printf("<fixup 4 left>\n");
            node = left_rotate(node);
            node->right->color = BLACK;
            node->color = node->left->color;
            node->left->color = BLACK;
            node->left->left->color= BLACK;
            break;
    }
    return node;
}

static rbnode_t delete_fixup_right(rbnode_t node, rbnode_t NIL){
    switch(detect_delete_violation_right(node, NIL)){
        case 1:
            printf("<fixup 1 right>\n");
            node = right_rotate(node);
            node->right->color = RED;
            node->color = BLACK;
            node->right = delete_fixup_right(node->right, NIL);
            break;
        case 2:
            printf("<fixup 2 right>\n");
            node->right->color = BLACK;
            node->left->color = RED;
            node = propagate_black(node);
            break;
        case 3:
            printf("<fixup 3 right>\n");
            node->left = left_rotate(node->left);
            node->left->color = BLACK;
            node->left->left->color = RED;
        case 4:
            printf("<fixup 4 right>\n");
            node = right_rotate(node);
            node->left->color = BLACK;
            node->color = node->right->color;
            node->right->color = BLACK;
            node->right->right->color = BLACK;
            break;
    }
    return node;
}

static rbnode_t minimum_deconnection(rbnode_t child, rbnode_t parent, rbnode_t NIL){
    rbnode_t tmp;
    if(child->left != NIL){
        tmp = minimum_deconnection(child->left, child, NIL);
        if(child == parent->right){
            parent->right = delete_fixup_right(child, NIL);
        }else{
            parent->left = delete_fixup_left(child, NIL);
        }

    }else{
        tmp = child;
        if(child == parent->right){
            parent->right = child->right;
        }else{
            parent->left = child->right;
        }
        if(is_black(tmp)){
            child->right = propagate_black(child->right);
        }
    }
    return tmp;
}

static rbnode_t delete_root(rbnode_t node, rbnode_t NIL){
    rbnode_t tmp;
    if(node->left == NIL || node->right == NIL){
        tmp = node;
        if(node->left != NIL){
            node = node->left;
        }else{
            node = node->right;
        }
        if(is_black(tmp)){
            node = propagate_black(node);
        }
    }else{
        tmp = minimum_deconnection(node, node->right, NIL);
        node->key = tmp->key;
        node = delete_fixup_right(node, NIL);
    }
    free(tmp);
    return node;
}

static rbnode_t delete_helper(rbnode_t node, rbnode_t NIL, int key){
    if(node != NIL){
        if(node->key > key){
            node->left = delete_helper(node->left, NIL, key);
            node = delete_fixup_left(node, NIL);
        }else if(node->key < key){
            node->right = delete_helper(node->right, NIL, key);
            node = delete_fixup_right(node, NIL);
        }else{
            node = delete_root(node, NIL);
        }
    }
    return node;
}

void delete(rbtree_t* t, int key){
    (*t)->root = delete_helper((*t)->root, (*t)->NIL, key);
    (*t)->root->color = BLACK;
    (*t)->NIL->color = BLACK;
}

static void print_helper(rbnode_t t, rbnode_t NIL){
    if(t != NIL){
        print_helper(t->left, NIL);
        printf("key := %d\n", t->key);
        print_helper(t->right, NIL);
    }
}

void print(rbtree_t t){
    print_helper(t->root, t->NIL);
}

static rbnode_t drop_helper(rbnode_t node, rbnode_t NIL){
    if(node != NIL){
        node->left = drop_helper(node->left, NIL);
        node->right = drop_helper(node->right, NIL);
        free(node);
    }
    return NIL;
}

void drop(rbtree_t* t){
    (*t)->root = drop_helper((*t)->root, (*t)->NIL);
    free((*t)->NIL);
    free((*t));
    *t = NULL;
    return;
}

static void print_with_color_helper(rbnode_t node, rbnode_t NIL){
    if(node != NIL){
        printf("<key := %d, color := %s> ", node->key, ((node->color == BLACK) ? "BLACK" : ((node->color == RED) ? "RED" : "DOUBLE_BLACK")));
        if(node->left != NIL){
            printf(" || left child := %d ", node->left->key);
        }
        if(node->right != NIL){
            printf(" || right child := %d ", node->right->key);
        }
        puts("");
        print_with_color_helper(node->left, NIL);
        print_with_color_helper(node->right, NIL);
    }
}

void print_with_color(rbtree_t t){
    print_with_color_helper(t->root, t->NIL);
}

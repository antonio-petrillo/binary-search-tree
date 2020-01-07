#include <stdio.h>
#include <stdlib.h>
#include "rbtree.h"
#include "queue.h"

void maketree(RB_tree* tree){
    tree->root = NULL;
}

NodePtr makenode(int value){
    NodePtr newnode = (NodePtr) malloc(sizeof(Node));
    if(!newnode){printf("error in allocting node for th rb tree\n"); exit(0);}
    newnode->left = newnode->right = NULL;
    newnode->value = value;
    newnode->color = RED;
    return newnode;
}

NodePtr left_rotate(NodePtr root){
    NodePtr newroot = root;
    if(root->left){
        newroot = root->left;
        root->left = newroot->right;
        newroot->right = root;
    }
    return newroot;
}

NodePtr right_rotate(NodePtr root){
    NodePtr newroot = root;
    if(root->right){
        newroot = root->right;
        root->right = newroot->left;
        newroot->left = root;
    }
    return newroot;
}

RB_tree insert_in_tree(RB_tree tree, int value){
    tree.root = insert(tree.root, value);
    tree.root->color = BLACK;
    return tree;
}

NodePtr insert(NodePtr root, int value){
    if(!root) root = makenode(value);
    else{
        if(root->value > value){
            root->left = insert(root->left, value);
            root = left_insertion_balance(root);
        }else if(root->value < value){
            root->right = insert(root->right, value);
            root = right_insertion_balance(root);
        }
    }
    return root;
}

int type_of_violation_on_insert_left(NodePtr root){
    int violation = 0;
    if(root->right && root->right->color == RED)
        if(root->left && root->left->color == RED)
            if(root->left->left && root->left->left->color == RED) 
                violation = 1;
            else if(root->left->right && root->left->right->color == RED) 
                violation = 1;
    else{
        if(root->left && root->left->color == RED){
            if(root->left->right && root->left->right->color == RED) violation = 2;
            else if(root->left->left && root->left->left->color == RED) violation = 3;    
        }
    }
    return violation;
}

int type_of_violation_on_insert_right(NodePtr root){
    int violation = 0;
    if(root->left && root->left->color == RED)
        if(root->right && root->right->color == RED)
            if(root->right->right && root->right->right->color == RED)
                violation = 1;
            else if(root->right->left && root->right->left->color == RED)
                violation = 1;
    else{
        if(root->right && root->right->color == RED){
            if(root->right->left && root->right->left->color == RED) violation = 2;
            else if(root->right->right && root->right->right->color) violation = 3;
        }
    }
    return violation;
}

NodePtr insert_balance_left_1(NodePtr root){
    root->left->color = root->right->color = BLACK;
    root->color = RED;
    return root;
}

NodePtr insert_balance_left_2(NodePtr root){
    root->left = right_rotate(root->left);
    return root;
}

NodePtr insert_balance_left_3(NodePtr root){
    root = left_rotate(root);
    root->color = BLACK;
    root->right = RED;
    return root;
}

NodePtr insert_balance_right_1(NodePtr root){
    root->color = RED;
    root->left->color = root->right->color = BLACK;
    return root;
}

NodePtr insert_balance_right_2(NodePtr root){
    root->right = left_rotate(root->left);
    return root;
}

NodePtr insert_balance_right_3(NodePtr root){
    root = right_rotate(root);
    root->left->color = RED;
    root->color = BLACK;
    return root;
}

NodePtr left_insertion_balance(NodePtr root){
    int v = type_of_violation_on_insert_left(root);
    switch (v){
    case 1:
        root = insert_balance_left_1(root);
        break;
    case 2:
        root = insert_balance_left_2(root);
        root = insert_balance_left_3(root);
        break;
    case 3:
        root = insert_balance_left_3(root);
        break;
    case 0:
        break;
    }
    return root;
}

NodePtr right_insertion_balance(NodePtr root){
    int v = type_of_violation_on_insert_right(root);
    switch (v){
    case 1:
        root = insert_balance_right_1(root);
        break;
    case 2:
        root = insert_balance_right_2(root);
        root = insert_balance_right_3(root);
        break;
    case 3: 
        root = insert_balance_right_3(root);
        break;
    case 0:
        break;
    }
    return root;
}

/* ########################## DEBUG FUNCTION ################################
void breadth_visit(RB_tree tree){
    if(tree.root){
        Queue q;
        NodePtr iter;
        makequeue(&q);
        enqueue(&q, tree.root);
        while(q.head){
            iter = dequeue(&q);
            if(iter->left) {
                printf("padre: %d, color: %s ==> figlio: %d, color: %s  \n", iter->value, (iter->color > 0) ? "BLACK" : "RED",iter->left->value, (iter->left->color > 0) ? "BLACK" : "RED"); 
                enqueue(&q, iter->left);
            }
            else printf("foglia\n");
            if(iter->right){
                printf("padre: %d, color: %s ==> figlio: %d, color: %s  \n", iter->value, (iter->color > 0) ? "BLACK" : "RED", iter->right->value, (iter->right->color > 0) ? "BLACK" : "RED");
                enqueue(&q, iter->right);
            }
            else printf("foglia\n");
            //printf("value:%4d, ", iter->value);
            //if(iter->color == RED) printf("color: RED\n");
            //else printf("color: BLACK\n");
        }
    }
    //puts("");
    return;
}
*///################### THERE WERE NO PROBLEMS IN REALITY P.D. ##############

void breadth_visit(RB_tree tree){
    if(tree.root){
        Queue q;
        NodePtr iter;
        makequeue(&q);
        enqueue(&q, tree.root);
        while(q.head){
            iter = dequeue(&q);
            if(iter->left) enqueue(&q, iter->left);
            if(iter->right) enqueue(&q, iter->right);
            printf("value:%4d, ", iter->value);
            if(iter->color == RED) printf("color: RED\n");
            else printf("color: BLACK\n");
        }
    }
    puts("");
    return;
}

void visit(NodePtr root){
    if(root){
        visit(root->left);
        printf("value:%4d, color:%2d ", root->value, root->color);
        visit(root->right);
    }
}

RB_tree drop_tree(RB_tree tree){
    tree.root = drop(tree.root);
    return tree ;
}

NodePtr drop(NodePtr root){
    if(root){
        root->left = drop(root->left);
        root->right = drop(root->right);
        free(root);
        return NULL;
    }
}

RB_tree delete_node_from_tree(RB_tree tree, int key){
    tree.root = delete_node(tree.root, key);
    tree.root->color = BLACK;
    return tree;
}

NodePtr delete_node(NodePtr root, int key){
    NodePtr tmp;
    if(root){   
        if(root->value > key){
            root->left = delete_node(root->left, key);
            root = left_delete_balance(root);
        }else if(root->value < key){
            root->right = delete_node(root->right, key);
            root = right_delete_balance(root);
        }else{//value found
            if(!root->left){//there are no node on the left
                tmp = root;
                root = root->right;
                if(tmp->color == BLACK) root = propagate_black(root);
                free(tmp);
            }else if(!root->right){//there are no node on the right
                tmp = root;
                root = root->left;
                if(tmp->color == BLACK) root = propagate_black(root);
                free(tmp);
            }else{//there are two subtree, (so' cazzi)
                tmp = minimum_disconnection(root->right, root);
                root->value = tmp->value;
                root = right_delete_balance(root);
            }
        }
    }
    return root;
}

NodePtr left_delete_balance(NodePtr root){
    if(root->left || root->right){
        int v = type_of_violation_on_delete_left(root);
        switch (v){
        case 1:
            root = delete_balance_left_1(root);
            root->left = left_delete_balance(root->left);
            break;
        case 2:
            root = delete_balance_left_2(root);
            break;
        case 3:
            root = delete_balance_left_3(root);
            root = delete_balance_left_4(root);
            break;
        case 4:
            root = delete_balance_left_4(root);
            break;
        case 0:
            break;
        }
    }
    return root;
}

NodePtr right_delete_balance(NodePtr root){
    if(root->left || root->right){
        int v = type_of_violation_on_delete_right(root);
        switch (v){
        case 1:
            root = delete_balance_right_1(root);
            root->right = right_delete_balance(root->right);
            break;
        case 2:
            root = delete_balance_right_2(root);
            break;
        case 3:
            root = delete_balance_right_3(root);
            root = delete_balance_right_4(root);
            break;
        case 4:
            root = delete_balance_right_4(root);
            break;
        case 0:
            break;
        }
    }
    return root;
}

NodePtr minimum_disconnection(NodePtr curr, NodePtr prev){
    NodePtr ret = NULL;
    if(curr){
        if(curr->left){
            ret = minimum_disconnection(curr->left, curr);
            if(curr == prev->left) prev->left = left_delete_balance(curr);
            else prev->right = right_delete_balance(curr);
        }else{
            if(curr == prev->left) prev->left = curr->right;
            else prev->right = curr->right;
            if(curr->color == BLACK) curr->right = propagate_black(curr->right);
            ret = curr;
        }
    }
    return ret;
}

int type_of_violation_on_delete_left(NodePtr root){
    int violation = 0;
    if(root->left && root->right){
        if(root->left->color == DOUBLE_BLACK && root->right->color == RED) violation = 1;
        else if(root->left->color == DOUBLE_BLACK){
            violation = 2;
            if(root->right->right && root->right->right->color == RED) violation = 4;
            else if(root->right->left && root->right->left->color == RED) violation = 3;
        }
    }
    return violation;
}

int type_of_violation_on_delete_right(NodePtr root){
    int violation = 0;
    if(root->left && root->right){
        if(root->right->color == DOUBLE_BLACK &&  root->left->color == RED) violation = 1;
        else if(root->right->color == DOUBLE_BLACK){
            violation = 2;
            if(root->left->left && root->left->left->color == RED) violation = 4;
            else if(root->left->right && root->left->right->color == RED) violation = 3;
        }
    }
    return violation;
}

NodePtr propagate_black(NodePtr root){
    if(root->color == RED) root->color == BLACK;
    else root->color == DOUBLE_BLACK;
    return root;
}

NodePtr delete_balance_left_1(NodePtr root){
    root = right_rotate(root);
    root->color = BLACK;
    root->left->color = RED;
    return root;
}

NodePtr delete_balance_left_2(NodePtr root){
    root->left->color = BLACK;
    root = propagate_black(root);
    root->right->color = RED;
    return root;
}

NodePtr delete_balance_left_3(NodePtr root){
    root->right = left_rotate(root->right);
    root->right->right->color = RED;
    root->right->color = BLACK;
    return root;
}

NodePtr delete_balance_left_4(NodePtr root){
    root = right_rotate(root);
    root->right->color = BLACK;
    root->color = root->left->color;
    root->left->color = BLACK;
    root->left->left->color = BLACK;
    return root;
}

NodePtr delete_balance_right_1(NodePtr root){
    root = left_rotate(root);
    root->color = BLACK;
    root->right->color = RED;
    return root;
}

NodePtr delete_balance_right_2(NodePtr root){
    root->right->color = BLACK;
    root = propagate_black(root);
    root->left->color = RED;
    return root;
}

NodePtr delete_balance_right_3(NodePtr root){
    root->left = right_rotate(root->left);
    root->left->left->color = RED;
    root->left->color = BLACK;
    return root;
}

NodePtr delete_balance_right_4(NodePtr root){
    root = left_rotate(root);
    root->left->color = BLACK;
    root->color = root->right->color;
    root->right->color = BLACK;
    root->right->right->color = BLACK;
    return root;
}



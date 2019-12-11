#ifndef AVL_H
#define AVL_H

typedef struct node_avl{
    struct node_avl* left;
    struct node_avl* right;
    unsigned int height;
    int value;
}Node;

typedef Node* AVLnode;

typedef struct{
    AVLnode root;
}AVL;

void error(char* message);
unsigned int max(unsigned int a,unsigned int b);
unsigned int height(AVLnode node);
void makeAVL(AVL* tree);
AVLnode makenode_AVL(int value);
AVLnode SL_rotation(AVLnode pivot);
AVLnode SR_rotation(AVLnode pivot);
AVLnode DL_rotation(AVLnode pivot);
AVLnode DR_rotation(AVLnode pivot);
int is_SL(AVLnode pivot);
int is_SR(AVLnode pivot);
AVLnode left_balance(AVLnode node);
AVLnode right_balance(AVLnode node);
AVL insert_in_AVL(AVL tree, int value);
AVLnode insert_node(AVLnode node, int value);
AVLnode delete_root(AVLnode node);
AVLnode minimum_disconnection_AVL(AVLnode node, AVLnode prev);
AVL delete_node_in_AVL(AVL tree, int key);
AVLnode delete_node(AVLnode node, int key);
void pre_order(AVLnode node);
void  in_order(AVLnode node);
AVL delete_all(AVL tree);
AVLnode delete_all_node(AVLnode node);

#endif
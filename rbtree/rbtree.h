#ifndef RB_TREE_H
#define RB_TREE_H

    #define RED 0
    #define BLACK 1
    #define DOUBLE_BLACK 2
    #define LEAF 3

    typedef struct node{
        struct node* left;
        struct node* right;
        int value;
        int color :4;
    }Node;

    typedef Node* NodePtr;

    typedef struct{
        NodePtr root;
    }RB_tree;

    void maketree(RB_tree* tree);
    NodePtr makenode(int value);
    NodePtr left_rotate(NodePtr root);
    NodePtr right_rotate(NodePtr root);
    RB_tree insert_in_tree(RB_tree tree, int value);
    NodePtr insert(NodePtr root, int value);
    int type_of_violation_on_insert_left(NodePtr root);
    int type_of_violation_on_insert_right(NodePtr root);
    NodePtr insert_balance_left_1(NodePtr root);
    NodePtr insert_balance_left_2(NodePtr root);
    NodePtr insert_balance_left_3(NodePtr root);
    NodePtr insert_balance_right_1(NodePtr root);
    NodePtr insert_balance_right_2(NodePtr root);
    NodePtr insert_balance_right_3(NodePtr root);
    NodePtr left_insertion_balance(NodePtr root);
    NodePtr right_insertion_balance(NodePtr root);
    void breadth_visit(RB_tree tree);
    void visit(NodePtr root);
    RB_tree drop_tree(RB_tree tree);
    NodePtr drop(NodePtr root);
    RB_tree delete_node_from_tree(RB_tree tree, int key);
    NodePtr delete_node(NodePtr root, int key);
    NodePtr left_delete_balance(NodePtr root);
    NodePtr right_delete_balance(NodePtr root);
    NodePtr minimum_disconnection(NodePtr curr, NodePtr prev);
    int type_of_violation_on_delete_left(NodePtr root);
    int type_of_violation_on_delete_right(NodePtr root);
    NodePtr propagate_black(NodePtr root);
    NodePtr delete_balance_left_1(NodePtr root);
    NodePtr delete_balance_left_2(NodePtr root);
    NodePtr delete_balance_left_3(NodePtr root);
    NodePtr delete_balance_left_4(NodePtr root);
    NodePtr delete_balance_right_1(NodePtr root);
    NodePtr delete_balance_right_2(NodePtr root);
    NodePtr delete_balance_right_3(NodePtr root);
    NodePtr delete_balance_right_4(NodePtr root);

#endif
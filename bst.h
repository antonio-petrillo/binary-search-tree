#ifndef BST_H 
#define BST_H

    typedef struct node{
        int value;
        struct node* left;
        struct node* right;
    }Node;

    typedef Node* NodePtr;

    typedef struct{
        NodePtr root;
    }BST;

    void error(char* message);
    void maketree(BST* tree);
    NodePtr makenode(int key);
    
    //funzioni di appoggio
    BST insert(BST tree, int key);
    NodePtr search(BST tree, int key);
    BST delete_node(BST tree, int key);
    NodePtr delete_root(NodePtr T);
    NodePtr find_minimum_from_tree(BST tree);
    NodePtr find_maximum_from_tree(BST tree);
    NodePtr successor(BST tree, int key);
    BST delete_tree(BST tree);
    int is_BST(BST tree, int inf, int sup);
    void iterative_visit(BST tree, void (*visit_mode)(BST tree));

    //funzioni ricorsive
    void insert_rc(NodePtr T, int key, NodePtr P);
    void search_support(NodePtr node, int key, NodePtr* ret);
    void delete_node_rc(NodePtr T, int key, NodePtr P);
    NodePtr minimum_disconnection(NodePtr T, NodePtr P);
    NodePtr find_minimum(NodePtr node);
    NodePtr find_maximum(NodePtr node);
    void successor_support(NodePtr T, int key, NodePtr* P);
    NodePtr delete_all_node(NodePtr node);
    int check_is_BST(NodePtr node, int inf, int sup);
    void visit(BST tree, void (*visit_mode)(NodePtr node));
    void visit_in_order(NodePtr node);
    void visit_post_order(NodePtr node);
    void visit_pre_order(NodePtr node);
    int count(BST tree);
    int count_nodes(NodePtr node);

    //funzioni iterative
    void visit_in_amplitude(BST tree);
    BST iterative_insertion(BST tree, int key);
    BST iterative_delete_node(BST tree, int key);
    void iterative_visit_in_order(BST tree);
    void iterative_visit_pre_order(BST tree);
    void iterative_visit_post_order(BST tree);

#endif
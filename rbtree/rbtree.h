 
#ifndef RBTREE_H
#define RBTREE_H

typedef enum{RED, BLACK} color_t;

#define color_to_string(node) (node == NULL)? "BLACK" : ((node->color == BLACK) ? "BLACK" : "RED")

typedef struct rb_node_t{
    struct rb_node_t* left;
    struct rb_node_t* right;
    struct rb_node_t* parent;
    color_t color;
    int value;
} *rb_node;

typedef struct rbtree_t{
    rb_node root;
}* rbtree;

rb_node grandparent(rb_node node); // parent parent
rb_node sibling(rb_node node);     // other parent's child
rb_node uncle(rb_node node);       // sibling of its parent
color_t node_color(rb_node node);
int is_black(rb_node node);
int is_red(rb_node node);
int num_child(rb_node node);
rbtree make_rbtree();
rbtree drop_rbtree(rbtree tree);
rb_node drop_rbtree_helper(rb_node node);
rb_node make_rbnode(int value, color_t color, rb_node left, rb_node right);
rb_node search_rb_node(rbtree tree, int value);
rb_node search_rb_node_from_node(rb_node node, int value);

void in_order_rbvisit(rbtree tree);
void in_order_rbvisit_helper(rb_node node);
void post_order_rbvisit(rbtree tree);
void post_order_rbvisit_helper(rb_node node);
void pre_order_rbvisit(rbtree tree);
void pre_order_rbvisit_helper(rb_node node);

void rotate_left_rb(rbtree tree, rb_node node);
void rotate_right_rb(rbtree tree, rb_node node);
void replace_rb_node(rbtree tree, rb_node old_node, rb_node node);

void rbtree_insert(rbtree tree, int value);
void rb_insert_fixup(rbtree tree, rb_node node);

rb_node min_rb(rbtree tree);
rb_node max_rb(rbtree tree);
rb_node min_rb_from_node(rb_node node);
rb_node max_rb_from_node(rb_node node);


void rbtree_remove(rbtree tree, int key);
void rbtree_remove_with_addr(rbtree tree, rb_node key);
void delete_case1(rbtree tree, rb_node node);
void delete_case2(rbtree tree, rb_node node);
void delete_case3(rbtree tree, rb_node node);
void delete_case4(rbtree tree, rb_node node);
void delete_case5(rbtree tree, rb_node node);
void delete_case6(rbtree tree, rb_node node);

int count_rb_node(rbtree tree);
int count_rb_node_helper(rb_node node);
int is_empty_rb(rbtree tree);
rbtree union_rbtree(rbtree tree1, rbtree tree2);
void union_rbtree_helper(rb_node tree1, rb_node tree2, rbtree tree3);
rbtree intersect_rbtree(rbtree tree1, rbtree tree2);
void intersect_rbtree_helper(rb_node tree1, rb_node tree2, rbtree tree3);
rbtree difference_rbtree(rbtree tree1, rbtree tree2);
void difference_rbtree_helper(rb_node tree2, rbtree tree3);
rbtree copy_rbtree(rbtree src);
void copy_rbtree_helper(rbtree dest, rb_node node);
void remove_rb_duplicates(rbtree tree);
void remove_rb_duplicates_helper(rbtree tree, rb_node node);
rb_node rb_successor(rbtree tree, int key);
void rb_successor_helper(rb_node node, int key, rb_node* candidate);
rb_node rb_predecessor(rbtree tree, int key);
void rb_predecessor_helper(rb_node node, int key, rb_node* candidate);

#endif
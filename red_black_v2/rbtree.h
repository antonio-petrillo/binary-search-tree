#ifndef RB_H
#define RB_H

typedef enum{RED, BLACK, DOUBLE_BLACK} color_t;

typedef struct rbnode{
    struct rbnode* left;
    struct rbnode* right;
    color_t color;
    int key;
}* rbnode_t;

typedef struct rbtree{
    rbnode_t root;
    rbnode_t NIL;
}* rbtree_t;

int is_black(rbnode_t node);
int is_double_black(rbnode_t node);

rbtree_t make_tree();
rbnode_t make_node(int key, rbnode_t NIL);
rbnode_t left_rotate(rbnode_t node);
rbnode_t right_rotate(rbnode_t node);
void insert(rbtree_t* t, int key);
void delete(rbtree_t* t, int key);
void print(rbtree_t t);
void drop(rbtree_t* t);

void print_with_color(rbtree_t t);

#endif

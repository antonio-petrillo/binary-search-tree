#include <stdio.h>
#include <stdlib.h>
#include "rbtree.h"

int main(int argc, char** argv){
    rbtree tree = make_rbtree();
    for(int i=atoi(argv[1]); i>=0; i--) rbtree_insert(tree, i);
    in_order_rbvisit(tree);
    printf("delete test\n");
    for(int i=atoi(argv[1]); i>=0; i--) {
        printf("rimuovo %d\n\n", i);
        rbtree_remove(tree, i);
        //in_order_rbvisit(tree);
        puts("");
    }
    in_order_rbvisit(tree);
    tree = drop_rbtree(tree);
    return 0;
}

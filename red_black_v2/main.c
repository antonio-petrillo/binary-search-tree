#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
    rbtree_t t = make_tree();
    for(int i=0; i<20; i++){
        insert(&t, i);
    }
    print_with_color(t);
    delete(&t, 10);
    puts("");
    print_with_color(t);
    drop(&t);
    return 0;
}

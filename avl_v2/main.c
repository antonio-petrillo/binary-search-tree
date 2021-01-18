#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
    avl_tree t = make_avl();
    for(int i=0; i<20; i++){
        insert_avl(&t, i);
    }
    print_avl(t);
    puts("\n");
    delete_avl(&t, 10);
    print_avl(t);
    drop_avl(&t);
    return 0;
}

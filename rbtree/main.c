#include <stdio.h>
#include <stdlib.h>
#include "rbtree.h"

int main(int argc, char** argv){
    rbTree tree = makeRbTree();
    //for(int i=0; i<=atoi(argv[1]); i++) tree = insertRb(tree, i);
    for(int i=atoi(argv[1]); i>=0; i--) tree = insertRb(tree, i);
    //inOrderRbVisit(tree);
    //
    breadthRbVisit(tree);
    for(int i=atoi(argv[1]); i>=0; i--){
        printf("\nrimuovo %d\n", i);
        tree = deleteRbNode(tree, i);
        breadthRbVisit(tree);
        //inOrderRbVisit(tree);
        puts("\n");
    } 
    printf("\nstampa finale\n\n");
    inOrderRbVisit(tree);

    tree = dropRbTree(tree);
    return 0;
}
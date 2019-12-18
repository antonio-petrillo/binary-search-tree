#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

int main(int argc, char** argv){
    //Edge edge_vector[] = {{1, 3}, {3, 1}, {1, 0}, {2, 3}, {3, 4}, {2, 4}, {4, 1}};
    //int num_vertex = 5;
    //int num_edge = 7;
    //Graph g = makegraph(g, num_vertex, num_edge, edge_vector);
    char buffer[256];
    if(argc == 2){
        strcpy(buffer, argv[1]);
    }else{
        printf("inserisci il nome del file da cui comporre il grafo(con annessa estensione): ");
        scanf("%s", buffer);
    }
    Graph g = makegraph_from_file(buffer);
    print_Graph(g);
    int src, dest;
    printf("insert source: ");
    scanf("%d", &src);
    printf("insert destination: ");
    scanf("%d", &dest);
    print_min_path(g, src, dest);
    dfs(g);
    printf("search of the ot:\n");
    topologic_ordering(g);
    g = drop(g);
    return 0;
}
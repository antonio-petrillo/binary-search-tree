#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define randomize srand(time(NULL))
#define random(x) rand()%x

void print_graph(FILE* stream, int num_vertex, int num_edge);

int main(int argc, char** argv){
    randomize;
    if(argc == 4){
        FILE* fp = fopen(argv[1], "w");
        int num_vertex = atoi(argv[2]);
        fprintf(fp, "%d\n", num_vertex);
        print_graph(fp, num_vertex, atoi(argv[3]));
        fclose(fp);
    }else{
        printf("syntax error!\ncorrect use: ./graph_generator filename_output number_of_vertex, number_of_edges/n");
    }
    return 0;
}

void print_graph(FILE* stream, int num_vertex, int num_edge){
    for(int i=0; i < num_edge; i++)
        fprintf(stream, "%d %d\n", random(num_vertex), random(num_vertex));
    return;
}












#ifndef GRAPH_H 
#define GRAPH_H 1

    #define WHITE 0
    #define BLACK 1
    #define GREY  2

    typedef struct adj_node{
        struct adj_node* next;
        int value;
    }AdjNode;

    typedef struct{
        AdjNode* head;
    }AdjList;

    typedef struct{
        int src;
        int dest;
    }Edge;

    typedef struct{
        AdjList* entries;
        int num_vertex;
        int num_edge;
    }Graph;

    typedef struct{
        int* forward_edge;
        int* backward_edge;
        int* transition_edge;
    }edge_info;

    void error(char* message);
    AdjNode* make_list_node(int adj);
    AdjList insert(AdjList list, int adj);
    Graph makegraph(Graph g, int num_vertex, int num_egde, Edge edge_to_add[]);
    void print_Graph(Graph g);
    void print_list(AdjList l);
    AdjList droplist(AdjList list);
    Graph drop(Graph g);
    int* bfs(Graph g, int starting_point);//breadth first visit
    void print_min_path(Graph g, int src, int dest);
    void genpath(int src, int dest, int* prev);
    Graph makegraph_from_file(char* filename);
    void dfs_visit(Graph g, int starting_point, int* color, int* prev, int* t_discover, int* t_end_visit, int* time, edge_info* info);
    void dfs(Graph g);
    void initialize_edge_info(Graph g,edge_info* info);

#endif
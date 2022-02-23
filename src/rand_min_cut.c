#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "utils.h"
#include "graph_utils.h"

graph_t * init_graph_from_file(const char * filepath)
{
    size_t V = 0, E = 0;

    FILE *fp;
    char *line = NULL;
    size_t len = 0;

    if ((fp = fopen(filepath, "r")) == NULL)
        exit(EXIT_FAILURE);
    
    while (getline(&line, &len, fp) != EOF)
    {
        char *next = strtok(line, "\t");

        while ((next = strtok(NULL, "\t")) != NULL)
        {
            if(next[0] == '\n' || next[0] == '\r')
                break;
            E++;
        }
        V++;
    }
    fclose(fp);
    if (line)
        free(line);

    return init_graph(V, E);
}

void assign_edges_from_file(graph_t *g, const char * filepath)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;

    if ((fp = fopen(filepath, "r")) == NULL)
        exit(EXIT_FAILURE);

    size_t e = 0;
    while (getline(&line, &len, fp) != EOF)
    {
        size_t value;
        char *next = strtok(line, "\t");
        sscanf(next, "%zu", &value);

        size_t src = value - 1; 

        while ((next = strtok(NULL, "\t")) != NULL)
        {
            if(next[0] == '\n' || next[0] == '\r')
                break;
            sscanf(next, "%zu", &value);

            g->edge[e++] = (edge_t) {src, value};
        }
    }
    fclose(fp);
    if (line)
        free(line);
}

int main(int argc, const char *argv[])
{
    srand(time(NULL));

    graph_t *g = init_graph_from_file("../data/kargerMinCut.txt");
    assign_edges_from_file(g, "../data/kargerMinCut.txt");
    
    printf("V, E: %zu, %zu\n", g->V, g->E);
    printf("edge example 4000: %zu -- %zu\n", g->edge[3999].src, g->edge[3999].dest);

    exit(EXIT_SUCCESS);
}
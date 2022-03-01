#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#include "utils.h"
#include "graph_utils.h"

graph_t *init_graph_from_file(const char *filepath)
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
            if (next[0] == '\n' || next[0] == '\r')
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

void assign_edges_from_file(graph_t *g, const char *filepath)
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
            if (next[0] == '\n' || next[0] == '\r')
                break;
            sscanf(next, "%zu", &value);

            size_t dest = value - 1;
            g->edge[e++] = (edge_t){src, dest};
        }
    }
    fclose(fp);
    if (line)
        free(line);
}

size_t karger_min_cut(graph_t *graph)
{
    size_t V = graph->V;
    size_t E = graph->E;
    edge_t *edge = graph->edge;

    subset_t *subsets;
    if ((subsets = (subset_t *)malloc(V * sizeof(subset_t))) == NULL)
        error("failed to alloc subset_t pointer at karger_min_cut");

    for (size_t v = 0; v < V; v++)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // contract edges, i.e. group into subsets
    size_t v = V;
    while (v > 2)
    {
        size_t i = rand() % E;
        size_t root1 = subsets_find(subsets, edge[i].src);
        size_t root2 = subsets_find(subsets, edge[i].dest);

        if (root1 == root2)
            continue;
        else
        {
            v--;
            subsets_union(subsets, root1, root2);
        }
    }

    // count edges
    size_t cutedEdges = 0;
    for (size_t i = 0; i < E; i++)
    {
        size_t root1 = subsets_find(subsets, edge[i].src);
        size_t root2 = subsets_find(subsets, edge[i].dest);

        if (root2 != root1)
            cutedEdges++;
    }

    return cutedEdges;
}

int main(int argc, const char *argv[])
{
    srand(time(NULL));

    printf("%zu\n", 16 % 32 == 0);

    const char *filepath = abs_path("../data/kargerMinCut.txt");
    graph_t *g = init_graph_from_file(filepath);
    assign_edges_from_file(g, filepath);

    size_t tries = 500;
    size_t minCutedEdges = 10 * (g->E);

    printf("CUTS: ");
    for (size_t i = 0; i < tries; i++)
    {
        size_t res = karger_min_cut(g) / 2;
        printf("%zu ", res);
        minCutedEdges = MIN(res, minCutedEdges);
    }

    printf("\nMIN CUT: %zu\n", minCutedEdges);

    printf("Num edges: %zu\n", g->E / 2);

    exit(EXIT_SUCCESS);
}

#ifndef GRAPH_UTILS_H_
#define GRAPH_UTILS_H_

#include <stdlib.h>

typedef struct Edge
{
    size_t src;
    size_t dest;
} edge_t;

typedef struct Graph
{
    size_t V;
    size_t E;
    edge_t *edge;
} graph_t;

typedef struct Subset
{
    size_t parent;
    size_t rank;
} subset_t;

size_t subsets_find(subset_t *const, const size_t);
void subsets_union(subset_t *const, const size_t, const size_t);
graph_t *init_graph(size_t, size_t);

#endif
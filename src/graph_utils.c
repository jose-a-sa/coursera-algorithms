
#include "graph_utils.h"
#include "utils.h"

size_t subsets_find(subset_t *subsets, const size_t n, const size_t i)
{
    if (i >= n)
        error("subsets_find index i out of range");

    if (subsets[i].parent != i)
        subsets[i].parent = subsets_find(subsets, n, subsets[i].parent);

    return subsets[i].parent;
}

void subsets_union(subset_t *const subsets, const size_t n, const size_t x, const size_t y)
{
    if (x >= n)
        error("subsets_union index x out of range");
    if (y >= n)
        error("subsets_union index y out of range");

    size_t xr = subsets_find(subsets, n, x);
    size_t yr = subsets_find(subsets, n, y);

    if (subsets[xr].rank < subsets[yr].rank)
        subsets[xr].parent = yr;
    else if (subsets[xr].rank > subsets[yr].rank)
        subsets[yr].parent = xr;
    else
    {
        subsets[yr].parent = xr;
        subsets[xr].rank++;
    }
}

graph_t *init_graph(size_t V, size_t E)
{
    graph_t *g;
    if ((g = (graph_t *)malloc(sizeof(graph_t))) == NULL)
        error("failed to malloc graph_t pointer in init_graph");

    edge_t * edge;
    if ((edge = (edge_t *)malloc(E*sizeof(edge_t))) == NULL)
        error("failed to malloc edge_t pointer in init_graph");

    g->V = V;
    g->E = E;
    g->edge = edge;

    return g;
}

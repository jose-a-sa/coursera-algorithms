
#include "graph_utils.h"
#include "utils.h"

size_t subsets_find(subset_t *subsets, const size_t i)
{
    if (subsets[i].parent != i)
        subsets[i].parent = subsets_find(subsets, subsets[i].parent);

    return subsets[i].parent;
}

void subsets_union(subset_t *const subsets, const size_t x, const size_t y)
{
    size_t xr = subsets_find(subsets, x);
    size_t yr = subsets_find(subsets, y);

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

graph_t *graph_init(size_t V, size_t E)
{
    graph_t *g;
    if ((g = (graph_t *)malloc(sizeof(graph_t))) == NULL)
        error("failed to malloc graph_t pointer in graph_init");

    edge_t *edge;
    if ((edge = (edge_t *)malloc(E * sizeof(edge_t))) == NULL)
        error("failed to malloc edge_t pointer in graph_init");

    g->V = V;
    g->E = E;
    g->edge = edge;

    return g;
}

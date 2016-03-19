#include <cstdio>
#include "Graph.h"
#include "Algo.h"

int main(int argc, char *argv[])
{
    char *topo_file =  "test-case/case1/topo.csv";
    char *demand_file = "test-case/case1/demand.csv";
    Graph G(topo_file, demand_file);

    Route route;
    if(DFS(G, G._src, G._dst, route))
        route.print(G);

    return 0;

}

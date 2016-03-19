#include <cstdio>
#include "Graph.h"
#include "Algo.h"

int main(int argc, char *argv[])
{
    char *topo_file =  "test-case/case1/topo.csv";
    char *demand_file = "test-case/case1/demand.csv";
    Graph G(topo_file, demand_file);


    return 0;

}

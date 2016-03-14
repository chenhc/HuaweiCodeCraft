#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "DataStructure.h"
#include "route.h"

Link Edge[lMAX];
int first[nMAX],next[nMAX], visit[lMAX], must[nMAX];
int Src, Dst, node_num, edge_num, must_num;

int main(int argc, char *argv[])
{
    char *topo_file = "test-case/case1/topo.csv";
    char *demand_file = "test-case/case1/demand.csv";
    init(topo_file, demand_file);
    search_route();
    return 0;
}







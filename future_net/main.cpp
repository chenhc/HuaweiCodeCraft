#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "io.h"
#include "DataStructure.h"
#include "route.h"

Link Edge[lMAX];
int first[nMAX], next[lMAX], visit[nMAX], must[nMAX], pre_first[nMAX], pre_next[lMAX], unblock[nMAX];
int Src, Dst, node_num, edge_num, must_num;

int main(int argc, char *argv[])
{
    char *topo_file = "more-test-case/test-case/case2/topo.csv"; //more-test-case
    char *demand_file = "more-test-case/test-case/case2/demand.csv";
    init(topo_file, demand_file);
    //search_route();
    int route[200];
    memset(visit, 0, sizeof(visit));
    memset(route, 0, sizeof(route));
    memset(unblock, 0, sizeof(unblock));

    if( DFS(Src, Dst, route, 0) == 1 )
    {
        int i = 0;
        printf("%d->", Src);
        while(route[i] != Dst)
            printf("%d->", route[i++]);
        printf("%d", Dst);
    }

    else
        printf("NA\n");
    return 0;
}







#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "io.h"
#include "DataStructure.h"
#include "route.h"
#include <set>
using namespace std;

Link Edge[lMAX];
int first[nMAX], next[lMAX], visit[nMAX], must[nMAX], pre_first[nMAX], pre_next[lMAX];
int Src, Dst, node_num, edge_num, must_num;
int Dist[nMAX][nMAX];
set<int> Subject;

int main(int argc, char *argv[])
{
    char *topo_file =  "more-test-case/test-case/case40-15/case3/topo.csv"; //"test-case/case2/topo.csv";
    char *demand_file = "more-test-case/test-case/case40-15/case3/demand.csv"; //"test-case/case2/demand.csv";
    init(topo_file, demand_file);

    set<int>::iterator it;
    printf("Ô¼Êøµã\n");
    for(it = Subject.begin(); it != Subject.end(); it++)
    {
        printf("%d ", *it);
    }
    printf("\n");

    int route[600];
    memset(visit, 0, sizeof(visit));
    memset(route, 0, sizeof(route));
    visit[Src] = 1;
    printf("dfs:\n");
    if( DFS(Src, Dst, route, 0))
    {
        int i = 0;
        int sum = 0;
        printf("%d->", Src);
        while(route[i] != Dst)
        {
            printf("%d->", route[i++]);
        }
        printf("%d", Dst);
    }
    else
        printf("NA\n");
    printf("\n");

    memset(route, 0, sizeof(route));



    /*printf("heuristic_dfs:\n");
    if( heuristic_search(Src, Dst, route))
    {
        int i = 0;
        printf("%d->", Src);
        while(route[i] != Dst)
            printf("%d->", route[i++]);
        printf("%d", Dst);

    }
    else
        printf("NA\n");*/
    return 0;
}







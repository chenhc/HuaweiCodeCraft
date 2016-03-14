#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "DataStructure.h"
#include <queue>
#include <vector>
#include <utility>

extern Link Edge[lMAX];
extern int first[nMAX], next[nMAX], visit[nMAX], must[nMAX];
extern int Src, Dst, edge_num, must_num;

int done[nMAX] = {0};
typedef  pair<int, int> pair_i_i;

int search_route()
{

    return 0;
};

int Dijkstra(int src, int dst)
{
    struct cmp
    priority_queue<pair_i_i, vector<pair_i_i>, >
}

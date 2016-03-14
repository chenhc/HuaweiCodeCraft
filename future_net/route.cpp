#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <malloc.h>
#include <queue>
#include <vector>
#include <utility>
#include <stack>
#include "io.h"
#include "DataStructure.h"
#include "route.h"


typedef  std::pair<int, int> pair_i_i;

extern Link Edge[lMAX];
extern int first[nMAX], next[lMAX], visit[nMAX], must[nMAX];
extern int Src, Dst, node_num, edge_num, must_num;

/* 20个点*/
int route[1<<20][20];
int dp[1<<20][20];

int search_route()
{
    /*节点数较少时，动态压缩dp求解*/
    memset(dp, -1, sizeof(dp));
    /*必经点集压缩*/
    int demand = 0;
    for(int i=0; i<must_num; i++)
    {
        demand = demand | (1<<must[i]);
    }
    demand = demand | (1<<Dst);

    int result = recursion(1<<Src, Src, demand);

    /*输出 route*/
    if(result < INF)
    {
        printf("all the cost = %d\n", result);
        int u = Src, S = 1<<Src, e = -1;
        while(u != Dst)
        {
            e = route[S][u];
            u = Edge[e].dst;
            S = S | (1<<u);
            printf("%d ", Edge[e].linkID);
        }
    }
    else
        printf("NA\n");

    return 0;
};

int Dijkstra(int src, int dst)
{
    /*标号数组*/
    int D[nMAX];
    int path[nMAX]; /*保存路径,path[nodeID] = edgeID*/
    for(int i=0; i<node_num; i++)
        D[i] = (i==0? 0: INF);

    /*优先队列*/
    std::priority_queue<pair_i_i, std::vector<pair_i_i>, std::greater<pair_i_i> > Q;

    /*起点进入优先队列*/
    Q.push(std::make_pair(D[src], src));
    while(!Q.empty())
    {
        /*队列中具有最小标号的*/
        pair_i_i x = Q.top();
        Q.pop();
        int u = x.second;
        if( u == dst) /*到达终点*/
            break;

        /*更新节点u出发的所有边 */
        for(int e = first[src]; e != -1; e = next[e])
        {
            int v = Edge[e].dst;
            if(D[u]+Edge[e].cost < D[v])
            {
                D[v] = D[u]+Edge[e].cost;
                Q.push(std::make_pair(D[v], v)); /*标号更新成功，加入优先队列*/
                path[v] = e; /*更新路径*/
            }
        }

    }
    return 0;
}

/*
 S已遍历点
 v当前点
*/
int recursion(int S, int v, const int demand)
{
    /*记忆化搜索*/
    if(dp[S][v] >= 0)
        return dp[S][v];
    if((S & demand) == demand && v == Dst)
        return dp[S][v] = 0;

    int res = INF;
    for(int e = first[v]; e != -1; e = next[e])
    {
        int u = Edge[e].dst;
        if(!(S>>u & 1))
        {
            int temp = Edge[e].cost + recursion(S|1<<u, u, demand);
            if(temp < res )
            {
                res = temp;
                route[S][v] = e;
            }
        }
    }

    return dp[S][v] = res;
}

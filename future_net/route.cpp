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

using namespace std;
typedef pair<int, int> pair_i_i;

extern Link Edge[lMAX];
extern int first[nMAX], next[lMAX], visit[nMAX], must[nMAX];
extern int Src, Dst, node_num, edge_num, must_num;

/* 20个点以内使用dp求解 */
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
        printf("\n");
    }
    else
        printf("NA\n");

    return 0;
}

int Dijkstra(int src, int dst)
{
    /* 最小值优先的优先队列 */

    /*标号数组*/
    int D[nMAX];
    int path[nMAX]; /*保存路径,path[nodeID] = edgeID*/
    for(int i=0; i<node_num; i++)
        D[i] = (i==src ? 0: INF);

    /*优先队列*/
    priority_queue<pair_i_i, vector<pair_i_i>, greater<pair_i_i> > Q;

    /*起点进入优先队列*/
    Q.push(make_pair(D[src], src));
    while(!Q.empty())
    {
        /*队列中具有最小标号的*/
        pair_i_i x = Q.top();
        Q.pop();
        int u = x.second;
        /* 避免节点的重复处理 */
        if(x.first != D[u]) continue;
        if( u == dst) /*到达终点*/
            break;

        /*更新节点u出发的所有边 */
        for(int e = first[u]; e != -1; e = next[e])
        {
            int v = Edge[e].dst;
            if(D[u]+Edge[e].cost < D[v])
            {
                D[v] = D[u]+Edge[e].cost;
                Q.push(make_pair(D[v], v)); /*标号更新成功，加入优先队列*/
                path[v] = e; /*更新反向路径*/
            }
        }

    }

    /*路径回溯*/
    if( D[dst] < INF)
    {
        printf("the shortest path %d->%d costs %d\n", src, dst, D[dst]);
        stack<int> trace;
        int cur = dst, e = -1;
        while(cur != src)
        {
            e = path[cur];
            trace.push(e);
            cur = Edge[e].src;
        }
        while(!trace.empty())
        {
            printf("%d ", trace.top());
            trace.pop();
        }
        printf("\n");
    }
    else
        printf("no path for %d->%d\n", src, dst);

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


/* route 记录经过的点。steps为当前路径累计节点数 */
int DFS(int cur, const int dst, int *route, int steps)
{
    if(cur == dst)
    {
        int ok = 1;
        int i = 0;
        while(i < must_num && visit[must[i]])  i++;
        if(i < must_num) ok = 0;
        return ok;
    }

    /* 当前节点cur 相邻所有节点，DFS */
    for(int e= first[cur]; e != -1; e = next[e])
    {
        cur = Edge[e].dst;
        if(!visit[cur])
        {
            visit[cur] = 1;
            route[steps] = cur;
            if(DFS(cur, dst, route, steps+1))
                return true;
            visit[cur] = 0;
        }
    }
    return false;
}

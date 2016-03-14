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

int route[2<<20][20];
int dp[2<<20][20];

int search_route()
{

    /*�ڵ�������ʱ����̬ѹ��dp���*/
    /* ����dp����*/
    /*int **dp = (int **)malloc((2<<node_num) * sizeof(int));
    for(int i=0; i < (2<<node_num); i++)
    {
        dp[i] = (int *)malloc(node_num * sizeof(int));
        memset(dp[i], -1, node_num);
    }

    /*����route���飬·���滮*/
    /*int **route = (int **)malloc((2<<node_num) * sizeof(int));
    for(int j=0; j< (2<<node_num) * sizeof(int); j++)
    {
        route[j] = (int *)malloc(node_num * sizeof(int));
    }
    */
    for(int i=0; i < (2<<node_num); i++)
    {
        memset(dp[i], -1, node_num);
    }
    /*�ؾ��㼯ѹ��*/
    int demand = 0;
    for(int i=0; i<must_num; i++)
    {
        demand = demand | (1<<must[i]);
    }
    demand = demand | (1<<Dst);

    int result = recursion(1<<Src, Src, dp, route, demand);
    printf("%d\n", result);
    /*��� route*/
    return 0;
};

int Dijkstra(int src, int dst)
{
    /*�������*/
    int D[nMAX];
    int path[nMAX]; /*����·��,path[nodeID] = edgeID*/
    for(int i=0; i<node_num; i++)
        D[i] = (i==0? 0: INF);

    /*���ȶ���*/
    std::priority_queue<pair_i_i, std::vector<pair_i_i>, std::greater<pair_i_i> > Q;

    /*���������ȶ���*/
    Q.push(std::make_pair(D[src], src));
    while(!Q.empty())
    {
        /*�����о�����С��ŵ�*/
        pair_i_i x = Q.top();
        Q.pop();
        int u = x.second;
        if( u == dst) /*�����յ�*/
            break;

        /*���½ڵ�u���������б� */
        for(int e = first[src]; e != -1; e = next[e])
        {
            int v = Edge[e].dst;
            if(D[u]+Edge[e].cost < D[v])
            {
                D[v] = D[u]+Edge[e].cost;
                Q.push(std::make_pair(D[v], v)); /*��Ÿ��³ɹ����������ȶ���*/
                path[v] = e; /*����·��*/
            }
        }


    }

    return 0;
}

/*
 S�ѱ�����
 v��ǰ��
*/
int recursion(int S, int v, int dp[][20], int route[][20], const int demand)
{
    /*���仯����*/
    if(dp[S][v] >= 0)
        return dp[S][v];
    if((S & demand) == demand && v == Dst)
        return dp[S][v] = 0;

    int res = INF;
    for(int e = first[v]; e != -1; e = next[e])
    {
        int u = Edge[v].dst;
        if(!(S>>u & 1))
        {
            int temp = Edge[e].cost + recursion(S|1<<u, u, dp, route, demand);
            if(temp < res )
            {
                res = temp;
                route[S][v] = e;
            }
        }
    }

    return dp[S][v] = res;
}

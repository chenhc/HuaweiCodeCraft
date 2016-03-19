#include <cstdio>
#include <cstdlib>
#include <queue>
#include <vector>
#include <utility>
#include <stack>
#include "Graph.h"

using namespace std;

int Floyd(const Graph &G, DistMatrix dist)
{
    /*初始化距离矩阵*/
    int node_num = G._nNum;
    for(int i = 0; i < node_num; i++)
        for(int j = 0; j < node_num; j++)
        {
            if(i == j)
                dist[i][j] = 0;
            else
                dist[i][j] = INF;
        }

    /* 边权赋值 */
    vector<Link>::const_iterator it = G._Edge.begin();
    for( ; it != G._Edge.end(); it ++)
        dist[(*it)._src][(*it)._dst] = (*it)._cost;

    /* floyd */
    for(int k = 0; k < node_num; k++)
        for(int i = 0; i < node_num; i++)
            for(int j = 0; j < node_num; j++)
            {
                int temp = dist[i][k] + dist[k][j];
                if(temp < dist[i][j])
                    dist[i][j] = temp;
            }

    return 0;
}



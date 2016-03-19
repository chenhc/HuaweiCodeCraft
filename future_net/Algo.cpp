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
    /*initialize distence matrix*/
    int node_num = G._nNum;
    for(int i = 0; i < node_num; i++)
        for(int j = 0; j < node_num; j++)
        {
            if(i == j)
                dist[i][j] = 0;
            else
                dist[i][j] = INF;
        }

    /* weight of each edge counts */
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

int DFS(const Graph &G, int cur, int dst, Route &path)
{
    if(cur == dst)
    {
        return path._already.size() == G.specified_num;
    }

    for(int e = G._first[cur]; e != -1; e = G._next[e])
    {
        cur = G._Edge.at(e)._dst;

        if(!path._visit[cur])
        {
            path.add(G, e);

            if(DFS(G, cur, dst, path))
                return true;

            path.rm(G, e);
        }
    }

    return false;
}

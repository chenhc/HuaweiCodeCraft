#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <vector>

#define nMAX 600
#define lMAX 5000
#define INF 999999

using namespace std;

typedef int DistMatrix[nMAX][nMAX];

class Link
{
public:
    int _linkID;
    int _src;
    int _dst;
    int _cost;

    Link(): _linkID(-1), _src(-1), _dst(-1), _cost(INF) {}

    Link(int linkid, int src, int dst, int cost)
    : _linkID(linkid), _src(src), _dst(dst), _cost(cost) {}

    bool operator < (const Link &e) const
    {
        return _cost < e._cost;
    }
};

class Graph
{
public:
    int _src;
    int _dst;
    int _lNum;
    int _nNum;
    int specified_num;
    vector<Link> _Edge;
    int _Specified[60];

    int _first[nMAX];
    int _next[lMAX];
    int _pre_first[nMAX];
    int _pre_next[lMAX];

    Graph(const char *topo_file, const char *demand_file);
};

#endif // GRAPH_H_INCLUDED

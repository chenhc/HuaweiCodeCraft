#ifndef ROUTE_H_INCLUDED
#define ROUTE_H_INCLUDED

int search_route();

int Dijkstra(int src, int dst);

int recursion(int S, int v, const int demand);

int DFS(int cur, const int dst, int *route, int steps);

int heuristic_dfs(int cur, const int dst, int *route, int steps, Link *_edge);

int heuristic_search(int src, int dst, int *route);
int floyd();

#endif // ROUTE_H_INCLUDED

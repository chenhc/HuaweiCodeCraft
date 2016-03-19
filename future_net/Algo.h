#ifndef ALGO_H_INCLUDED
#define ALGO_H_INCLUDED

int Dijkstra(const Graph &G, int src, int dst);

int Floyd(const Graph &G, DistMatrix dist);

int DFS(const Graph &G, int cur, int dst, Route &path);

#endif // ALGO_H_INCLUDED

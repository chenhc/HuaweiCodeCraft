#ifndef ROUTE_H_INCLUDED
#define ROUTE_H_INCLUDED

int search_route();

int Dijkstra(int src, int dst);

int recursion(int S, int v, int dp[][20], int route[][20], const int demand);

#endif // ROUTE_H_INCLUDED

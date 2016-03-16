#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED

#define nMAX 600+50
#define lMAX 5000
#define INF 99999

int init(const char * topo_file, const char * demand_file);

int strtoi(const char * str, int len);

#endif // IO_H_INCLUDED

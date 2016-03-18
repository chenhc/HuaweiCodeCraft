#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "io.h"
#include "DataStructure.h"
#include <set>

using namespace std;
extern Link Edge[lMAX];
extern int first[nMAX], next[lMAX], visit[nMAX], must[nMAX], pre_first[nMAX], pre_next[lMAX];
extern int Src, Dst, node_num, edge_num, must_num;
extern int Dist[nMAX][nMAX];
extern set<int> Subject;

int strtoi(const char *str, int len)
{
    int k,result=0;
    for(k=0; k<len; k++)
    {
        result += (str[k]-'0') * (int)pow(10, len-1-k);
    }
    return result;
}

int init(const char *topo_file, const char *demand_file)
{
    /* 初始化 */
    memset(first, -1, sizeof(first));
    memset(pre_first, -1, sizeof(pre_first));
    memset(Dist, -1, sizeof(Dist));
    memset(must, -1, sizeof(must));

    /**/
    set<int>::iterator it;
    for(it=Subject.begin(); it!=Subject.end();)
    {
        Subject.erase(it++);
    }


    /* 打开拓扑文件 */
    FILE *fp = fopen(topo_file, "r");
    if(fp == NULL)
    {
        printf("Failed to open file %s\n", topo_file);
        return 0;
    }

    /* 读取拓扑 */
    int e_cnt = 0, n_cnt = 0;
    int linkID, srcID, destID, cost;
    while(!feof(fp))
    {
        /* 构造邻接矩阵 */
        fscanf(fp, "%d,%d,%d,%d", &linkID, &srcID, &destID, &cost);
        Edge[e_cnt].linkID = linkID;
        Edge[e_cnt].src = srcID;
        Edge[e_cnt].dst = destID;
        Edge[e_cnt].cost = cost;
        int temp = srcID>destID? srcID : destID;
        n_cnt = n_cnt>temp? n_cnt : temp;
        /* 有向边邻接链表 */
        next[e_cnt] = first[srcID];
        first[srcID] = e_cnt;
        /* 有向边反向邻接链表 */
        pre_next[e_cnt] = pre_first[destID];
        pre_first[destID] = e_cnt;

        /*权值矩阵*/
        Dist[srcID][destID] = cost;
        /*统计边数*/
        e_cnt ++;
    }
    fclose(fp);
    node_num = n_cnt + 1;
    edge_num = e_cnt;

    /* 打开约束条件文件 */
    fp = fopen(demand_file, "r");
    if(fp == NULL)
    {
        printf("Failed to open file %s\n", topo_file);
        return 0;
    }

    char buf[100];
    while(!feof(fp))
    {
        /* 读取源点，终点，约束点集 */
        fscanf(fp, "%d,%d,%s" , &Src, &Dst, buf);
    }

    /* 解析约束点集 */
    int cnt = 0;
    int len = strlen(buf);
    char temp[5];
    int i = 0, j = 0;
    while(i<len)
    {
        /* 数字字符暂存 */
        if( isdigit(buf[i]) )
            temp[j++] = buf[i];

        /* 遇到 '|' 或结尾开始解析 */
        if( i==len-1)
        {
            must[cnt] = strtoi(temp, j);
            Subject.insert(must[cnt]);
            j = 0;
            cnt ++;
        }
        else if(buf[i]=='|')
        {
            must[cnt] = strtoi(temp, j);
            Subject.insert(must[cnt]);
            j = 0;
            cnt ++;
        }
        i++;
    }
    must_num = cnt;

    return 0;
}

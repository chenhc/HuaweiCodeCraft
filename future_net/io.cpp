#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "io.h"
#include "DataStructure.h"

extern Link Edge[lMAX];
extern int first[nMAX], next[nMAX], visit[nMAX], must[nMAX];
extern int Src, Dst, edge_num, must_num;


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

    /* 打开拓扑文件 */
    FILE *fp=fopen(topo_file, "r");
    if(fp == NULL)
    {
        printf("Failed to open file %s\n", topo_file);
        return 0;
    }

    /* 读取拓扑 */
    int cnt = 0;
    while(!feof(fp))
    {
        /* 构造邻接矩阵 */
        fscanf(fp, "%d,%d,%d,%d", &Edge[cnt].linkID, &Edge[cnt].src, &Edge[cnt].dst, &Edge[cnt].cost);
        next[cnt] = first[Edge[cnt].src];
        first[Edge[cnt].src] = cnt;
        cnt ++;
    }
    fclose(fp);
    edge_num = cnt-1;

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
    cnt = 0;
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
            j = 0;
            cnt ++;
        }
        else if(buf[i]=='|')
        {
            must[cnt] = strtoi(temp, j);
            j = 0;
            cnt ++;
        }
        i++;
    }
    must_num = cnt;

    return 0;
}

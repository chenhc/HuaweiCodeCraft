#include <cstdio>
#include <cstring>
#include <ctype.h>
#include "Graph.h"
#include "IOHelper.h"

Graph::Graph(const char *topo_file, const char *demand_file)
{
    memset(_first, -1, sizeof(_first));
    memset(_pre_first, -1, sizeof(_pre_first));

    /* �������ļ� */
    FILE *fp = fopen(topo_file, "r");
    if(fp == NULL)
    {
        printf("Failed to open file %s\n", topo_file);
    }

    /* ��ȡ���� */
    int e_cnt = 0, n_cnt = 0;
    int linkID, srcID, destID, cost;
    while(!feof(fp))
    {
        fscanf(fp, "%d,%d,%d,%d", &linkID, &srcID, &destID, &cost);

        /*��¼���Ľڵ�id*/
        int temp = srcID>destID ? srcID : destID;
        n_cnt = n_cnt>temp ? n_cnt : temp;

        Link e(linkID, srcID, destID, cost);

        /*�����ڽӾ���*/
        _next[e_cnt] = _first[srcID];
        _first[srcID] = e_cnt;

        /*������ڽӾ���*/
        _pre_next[e_cnt] = _pre_first[destID];
        _pre_first[destID] = e_cnt;

        /*�洢��*/
        _Edge.push_back(e);

        e_cnt ++;
    }
    /*��¼����,����*/
    _lNum = e_cnt;
    _nNum= n_cnt + 1;
    fclose(fp);

    /* ��ȡҪ���ļ� */
    fp = fopen(demand_file, "r");
    if(fp == NULL)
    {
        printf("Failed to open file %s\n", topo_file);
    }

    char buf[100];
    while(!feof(fp))
    {
        fscanf(fp, "%d,%d,%s" , &_src, &_dst, buf);
    }

    int cnt = 0;
    int len = strlen(buf);
    char temp[5];
    int i = 0, j = 0;
    while(i<len)
    {
        /* �ݴ����� */
        if( isdigit(buf[i]) )
            temp[j++] = buf[i];

        /* �����ַ�����β��ʼ���� */
        if( i==len-1)
        {
            _Specified[cnt] = strtoi(temp, j);
            j = 0;
            cnt ++;
        }
        else if(buf[i]=='|')
        {
            _Specified[cnt] = strtoi(temp, j);
            j = 0;
            cnt ++;
        }
        i++;
    }
    specified_num = cnt;
    fclose(fp);
}



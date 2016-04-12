//
//  main.cpp
//  astar
//
//  Created by 林家馨 on 16/4/12.
//  Copyright (c) 2016年 jessie. All rights reserved.
//

#include <math.h>
#include <stdio.h>
#include <iostream>


enum{
    START = 1,
    BARRIER,
    END
};

const int ROW = 9;
const int COL = 6;

int map[ROW][COL]={
    {1,0,0,0,0,0,},
    {0,0,0,0,0,0,},
    {0,0,0,0,0,0,},
    {0,0,0,0,0,0,},
    {0,0,0,0,0,0,},
    {0,0,0,0,0,0,},
    {0,0,0,0,0,0,},
    {0,0,0,0,3,0,},
    {0,0,0,0,0,0,},
};

typedef struct list{
    int x;
    int y;
    float g; //父节点到邻居的代价1 or 1.4
    float h; //到目的地的曼哈顿距离
    float f; //f=g+h
}list;

struct list openlist[100];
struct list closelist[100];
int openlist_size = 0;

//排序找到f最小的节点
int sortList(list* listArry, int listlen)
{
    int index = 0;
    float f = listArry[0].f;
    for (int i=0; i<listlen-1; i++)
    {
        if (f>=listArry[i+1].f)
        {
            f = listArry[i+1].f;
            index = i+1;
        }
    }
    return index;
}
//将openlist表中的f最小的节点存入到closelist中 (c语言没有引用)
void swpList(list* listsrc, list* listdes, int *listdeslen)
{
    listdes[*listdeslen].x = listsrc->x;
    listdes[*listdeslen].y = listsrc->y;
    listdes[*listdeslen].g = listsrc->g;
    listdes[*listdeslen].h = listsrc->h;
    listdes[*listdeslen].f = listsrc->f;
    (*listdeslen) += 1;
    
    //    printf("\n添加节点到closelist（%d,%d）\n",listsrc->x,listsrc->y);
}

//删除openlist中的最小节点
void deleteNode(list* listArry, int index, int *list_len)
{
    for (int i=index; i<*list_len; i++)
    {
        listArry[i].x = listArry[i+1].x;
        listArry[i].y = listArry[i+1].y;
        listArry[i].g = listArry[i+1].g;
        listArry[i].h = listArry[i+1].h;
        listArry[i].f = listArry[i+1].f;
    }
    
    *list_len -= 1;
}

//计算当前节点到目的节点的曼哈顿距离
float getManhatondistance(int start_x, int start_y, int end_x, int end_y)
{
    float distance = 0;
    int x = std::abs(end_x-start_x);
    int y = std::abs(end_y-start_y);
    
    if (x==y)
    {
        //        distance = x*1.4;
        distance = x+y;
        //        printf("\n（%d,%d）distance = %f\n", start_x, start_y, distance);
    }
    else
    {
        //        distance = abs(x-1)*1+y*1.4;
        distance = x+y;
        //        printf("\n（%d,%d）distance = %f\n", start_x, start_y, distance);
    }
    
    return distance;
}

//判断节点是否在openlist中
int isExistOpenList(int list_len, int x, int y)
{
    for (int i=0; i<list_len; i++)
    {
        if ((openlist[i].x==x)&&(openlist[i].y==y))
        {
            return 1;
        }
    }
    return 0;
}

//寻找邻居节点，并将其加入到openlist中
void addNeighbourNode(list* listArry, int *list_len, int index, int end_x, int end_y)
{
    int index_x = closelist[index].x;
    int index_y = closelist[index].y;
    //    printf("ddd(%d,%d)%d\n",index_x, index_y,index);
    
    /*
     八个方向
     (-1,-1)(-1,0)(-1,1)
     ( 0,-1)( 0,0)( 0,1)
     ( 1,-1)( 1,0)( 1,1)
     */
    
    
    //(-1,0)
    if ((index_x-1>=0)&&(index_y<COL)&&map[index_x-1][index_y+0]!=BARRIER)
    {
        if(!isExistOpenList(*list_len, index_x-1, index_y))
        {
            openlist[*list_len].x = index_x-1;
            openlist[*list_len].y = index_y;
            openlist[*list_len].g = 1;
            openlist[*list_len].h = getManhatondistance(index_x-1, index_y, end_x, end_y);
            openlist[*list_len].f = openlist[*list_len].g + openlist[*list_len].h;
            *list_len += 1;
        }
    }
    //(0,-1)
    if ((index_x>=0)&&(index_y-1>=0)&&map[index_x][index_y-1]!=BARRIER)
    {
        if(!isExistOpenList(*list_len, index_x, index_y-1))
        {
            openlist[*list_len].x = index_x;
            openlist[*list_len].y = index_y-1;
            openlist[*list_len].g = 1;
            openlist[*list_len].h = getManhatondistance(index_x, index_y-1, end_x, end_y);
            openlist[*list_len].f = openlist[*list_len].g + openlist[*list_len].h;
            *list_len += 1;
        }
    }
    //(0,1)
    if ((index_x>=0)&&(index_y+1<COL)&&map[index_x][index_y+1]!=BARRIER)
    {
        if(!isExistOpenList(*list_len, index_x, index_y+1))
        {
            openlist[*list_len].x = index_x;
            openlist[*list_len].y = index_y+1;
            openlist[*list_len].g = 1;
            openlist[*list_len].h = getManhatondistance(index_x, index_y+1, end_x, end_y);
            openlist[*list_len].f = openlist[*list_len].g + openlist[*list_len].h;
            *list_len += 1;
        }
    }
    //(1,0)
    if ((index_x+1<ROW)&&(index_y>=0)&&map[index_x+1][index_y]!=BARRIER)
    {
        if(!isExistOpenList(*list_len, index_x+1, index_y))
        {
            openlist[*list_len].x = index_x+1;
            openlist[*list_len].y = index_y;
            openlist[*list_len].g = 1;
            openlist[*list_len].h = getManhatondistance(index_x+1, index_y, end_x, end_y);
            openlist[*list_len].f = openlist[*list_len].g + openlist[*list_len].h;
            *list_len += 1;
        }
    }
    //(-1,-1)
    if ((index_x-1>=0)&&(index_y-1>=0)&&map[index_x-1][index_y-1]!=BARRIER)
    {
        if(!isExistOpenList(*list_len, index_x-1, index_y-1))
        {
            openlist[*list_len].x = index_x-1;
            openlist[*list_len].y = index_y-1;
            openlist[*list_len].g = 1.4;
            openlist[*list_len].h = getManhatondistance(index_x-1, index_y-1, end_x, end_y);
            openlist[*list_len].f = openlist[*list_len].g + openlist[*list_len].h;
            *list_len += 1;
        }
    }
    //(1,-1)
    if ((index_x+1<ROW)&&(index_y-1>=0)&&map[index_x+1][index_y-1]!=BARRIER)
    {
        if(!isExistOpenList(*list_len, index_x+1, index_y-1))
        {
            openlist[*list_len].x = index_x+1;
            openlist[*list_len].y = index_y-1;
            openlist[*list_len].g = 1.4;
            openlist[*list_len].h = getManhatondistance(index_x+1, index_y-1, end_x, end_y);
            openlist[*list_len].f = openlist[*list_len].g + openlist[*list_len].h;
            *list_len += 1;
        }
    }
    //(-1,1)
    if ((index_x-1>=0)&&(index_y+1<COL)&&map[index_x-1][index_y+1]!=BARRIER)
    {
        if(!isExistOpenList(*list_len, index_x-1, index_y+1))
        {
            openlist[*list_len].x = index_x-1;
            openlist[*list_len].y = index_y+1;
            openlist[*list_len].g = 1.4;
            openlist[*list_len].h = getManhatondistance(index_x-1, index_y+1, end_x, end_y);
            openlist[*list_len].f = openlist[*list_len].g + openlist[*list_len].h;
            *list_len += 1;
        }
    }
    //(1,1)
    if ((index_x+1<ROW)&&(index_y+1<COL)&&map[index_x+1][index_y+1]!=BARRIER)
    {
        if(!isExistOpenList(*list_len, index_x+1, index_y+1))
        {
            openlist[*list_len].x = index_x+1;
            openlist[*list_len].y = index_y+1;
            openlist[*list_len].g = 1.4;
            openlist[*list_len].h = getManhatondistance(index_x+1, index_y+1, end_x, end_y);
            openlist[*list_len].f = openlist[*list_len].g + openlist[*list_len].h;
            *list_len += 1;
        }
    }
}

//判断终点是否在closelist中
int isEndNodeExistCloseTable(list* listArry, int len, int end_x, int end_y)
{
    for (int i=0; i<len; i++)
    {
        if ((listArry[i].x == end_x)&&(listArry[i].y == end_y))
        {
            return 1;
        }
    }
    return 0;
}

int main(int argvc, char **argv)
{
    //    printf("hello astar.\n");
    int start_x=0;
    int start_y=0;
    int end_x=0;
    int end_y=0;
    for (int i=0; i<ROW; i++)
        for (int j=0; j<COL; j++)
        {
            if (map[i][j]==START)
            {
                start_x = i;
                start_y = j;
                
                //                printf("start (%d,%d)\n",start_x,start_y);
            }
            if (map[i][j]==END)
            {
                end_x = i;
                end_y = j;
                //                printf("end (%d,%d)\n",end_x,end_y);
            }
        }
    
    openlist[0].x = start_x;
    openlist[0].y = start_y;
    openlist[0].f = 0;//起点的f为0
    openlist_size = 1;
    
    int closelist_len = 0;
    
    while (openlist_size)
    {
        //        printf("openlist_size qian = %d\n",openlist_size);
        int index = 0; //openlist中f最小的节点下标
        //找到代价最小的节点
        index = sortList(openlist, openlist_size);
        //        printf("index = %d\n",index);
        //将代价最小的插入closelist中
        swpList(&openlist[index], closelist, &closelist_len);
        //        printf("closelist_len = %d\n",closelist_len);
        //从openlist中移除代价最小的节点
        deleteNode(openlist, index, &openlist_size);
        //        printf("openlist_size = %d\n",openlist_size);
        //添加代价最小节点的邻居节点到openlist中
        addNeighbourNode(openlist, &openlist_size, closelist_len-1, end_x, end_y);
        //
        if (isEndNodeExistCloseTable(closelist, closelist_len, end_x, end_y))
        {
            printf("\npath ");
            for (int i=0; i<closelist_len; i++)
            {
                printf("(%d,%d) ",closelist[i].x,closelist[i].y);
            }
            printf("\n\n");
            break;
        }
        
        //        printf("\nOPEN  ");
        //        for (int i=0; i<openlist_size; i++)
        //        {
        //            printf("(%d,%d)->",openlist[i].x,openlist[i].y);
        //        }
        //        printf("\nCLOSE  ");
        //        for (int i=0; i<closelist_len; i++)
        //        {
        //            printf("(%d,%d)->",closelist[i].x,closelist[i].y);
        //        }
        //        printf("\n\n");
    }
    return 0;
}

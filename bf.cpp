//
//  main.cpp
//  BF
//
//  Created by 林家馨 on 16/4/11.
//  Copyright (c) 2016年 jessie. All rights reserved.
//

#include <iostream>
#include<stdio.h>



typedef struct point
{
    int row, col, predecessor;
} item_t;

#define ROW 9
#define COL 6

static item_t queue[512];

int head = 0, tail = 0;

void enqueue(item_t p)
{
    queue[tail++] = p;
}

struct point dequeue(void)
{
    return queue[head++];
}

int is_empty(void)
{
    return head == tail;
}

int graph[ROW][COL]={
    {0,0,0,0,0,0,},
    {0,0,0,0,0,0,},
    {0,0,0,0,0,0,},
    {0,0,0,0,0,0,},
    {0,0,0,0,0,0,},
    {0,0,0,0,0,0,},
    {0,0,0,0,0,0,},
    {0,0,0,0,0,0,},
    {0,0,0,0,0,0,},
};

void print_graph(void)
{
    int i, j;
    for (i = 0; i < ROW; i++)
    {
        
        for (j = 0; j < COL; j++)
            printf("%d ", graph[i][j]);
        putchar('\n');
    }
    printf("*********\n");
}

void visit(int row, int col)
{
    struct point visit_point = { row, col, head - 1 };
    graph[row][col] = 2;
    enqueue(visit_point);
}

int main(void)
{
    struct point p = { 0, 1, -1 };
    
    graph[p.row][p.col] = 1;
    enqueue(p);
    
    while (!is_empty())//队列非空
    {
        p = dequeue();//出队一个点p;
        if (p.row == 7 && p.col == 4) //Gole if (p这个点是终点) break
            break;
        
        if (p.col + 1 < COL   // 否则沿右、下、左、上四个方向探索相邻的点 right
            && graph[p.row][p.col + 1] == 0)//if (和p相邻的点有路可走，并且还没走过)
                                            //将相邻的点标记为已走过并入队，它的前趋就是刚出队的p点;
            visit(p.row, p.col + 1);
        if (p.row + 1 < ROW // down
            && graph[p.row + 1][p.col] == 0)
            visit(p.row + 1, p.col);
        if (p.col - 1 >= 0  //left
            && graph[p.row][p.col - 1] == 0)
            visit(p.row, p.col - 1);
        if (p.row - 1 >= 0  // up 
            && graph[p.row - 1][p.col] == 0)
            visit(p.row - 1, p.col);
        print_graph();
    }
    
    if (p.row == 7 && p.col == 4)//p点是终点
    {
        
        std::cout<<"("<<p.row<<" ,"<<p.col<<")"<<std::endl;//打印p点的坐标
   
        while (p.predecessor != -1)//p点有前趋
        {
            p = queue[p.predecessor];//p点 = p点的前趋;
            printf("(%d, %d)\n", p.row, p.col);//打印p点的坐标;
        }
    }
    else
        printf("No path!\n");
    
    return 0;
}
//
//  main.cpp
//  DF
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

static item_t stack[512];
static int top = 0;

void push(item_t p)
{
    stack[top++] = p;
}

item_t pop(void)
{
    return stack[--top];
}

int is_empty(void)
{
    return top == 0;
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



void visit(int row, int col, struct point pre)
{
    struct point visit_point = { row, col, top-1};
    graph[row][col] = 2;
    push(visit_point);
}

int main(void)
{
    struct point p = { 0, 1, -1};
    graph[p.row][p.col] = 1;
    push(p);
    while (!is_empty())//栈非空
    {
        p = pop();//从栈顶弹出一个点p;
        if (p.row == 7 && p.col == 4)//Goal p这个点是终点
            break;
        if (p.col + 1 < COL//否则沿右、下、左、上四个方向探索相邻的点  right
            && graph[p.row][p.col + 1] == 0)//和p相邻的点有路可走，并且还没走过
            visit(p.row, p.col + 1, p);//将相邻的点标记为已走过并压栈，它的前趋就是p点
        if (p.row + 1 < ROW    //down
            && graph[p.row + 1][p.col] == 0)
            visit(p.row + 1, p.col, p);
        if (p.col - 1 >= 0     //left
            && graph[p.row][p.col - 1] == 0)
            visit(p.row, p.col - 1, p);
        if (p.row - 1 >= 0      //up
            && graph[p.row - 1][p.col] == 0)
            visit(p.row - 1, p.col, p);
        print_graph();
        
    }
    
    if (p.row == 7 && p.col == 4)
    {
        printf("(%d, %d)\n", p.row, p.col);
        while (p.predecessor != -1)
        {
            p = stack[p.predecessor];
            printf("(%d, %d)\n", p.row, p.col);
        }
    }
else
        printf("No path!\n");
    return 0;
}
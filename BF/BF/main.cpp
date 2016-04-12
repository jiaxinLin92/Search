//
//  main.cpp
//  BF
//
//  Created by 林家馨 on 16/4/11.
//  Copyright (c) 2016年 jessie. All rights reserved.
//

#include <iostream>
#include<stdio.h>


#define MAX_ROW 9
#define MAX_COL 6

struct point
{
    int row, col, predecessor;
} queue[512];

int head = 0, tail = 0;

void enqueue(struct point p)
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

int maze[MAX_ROW][MAX_COL] =
{
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};

void print_maze(void)
{
    int i, j;
    for (i = 0; i < MAX_ROW; i++)
    {
        
        for (j = 0; j < MAX_COL; j++)
            printf("%d ", maze[i][j]);
        //std::cout<<maze[i][j]<<std::endl;
        putchar('\n');
    }
    printf("*********\n");
}

void visit(int row, int col)
{
    struct point visit_point = { row, col, head - 1 };
    maze[row][col] = 2;
    enqueue(visit_point);
}

int main(void)
{
    struct point p = { 0, 1, -1 };
    
    maze[p.row][p.col] = 1;
    enqueue(p);
    
    while (!is_empty())
    {
        p = dequeue();
        if (p.row == 7 && p.col == 4) //Gole
            break;
        if (p.col + 1 < MAX_COL /* right */
            && maze[p.row][p.col + 1] == 0)
            visit(p.row, p.col + 1);
        if (p.row + 1 < MAX_ROW /* down */
            && maze[p.row + 1][p.col] == 0)
            visit(p.row + 1, p.col);
        if (p.col - 1 >= 0  /* left */
            && maze[p.row][p.col - 1] == 0)
            visit(p.row, p.col - 1);
        if (p.row - 1 >= 0  /* up */
            && maze[p.row - 1][p.col] == 0)
            visit(p.row - 1, p.col);
        print_maze();
    }
    if (p.row == 7 && p.col == 4)
    {
        
        std::cout<<"("<<p.row<<" ,"<<p.col<<")"<<std::endl;
   
        while (p.predecessor != -1)
        {
            p = queue[p.predecessor];
            printf("(%d, %d)\n", p.row, p.col);
        }
    }
    else
        printf("No path!\n");
    
    return 0;
}
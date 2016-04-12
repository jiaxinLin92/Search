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
    int row, col;
} item_t;
#define MAX_ROW 9
#define MAX_COL 6

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
        putchar('\n');
    }
    printf("*********\n");
}

struct point predecessor[MAX_ROW][MAX_COL] =
{
    {{ -1, -1}, { -1, -1}, { -1, -1}, { -1, -1}, { -1, -1}, { -1, -1}},
    {{ -1, -1}, { -1, -1}, { -1, -1}, { -1, -1}, { -1, -1}, { -1, -1}},
    {{ -1, -1}, { -1, -1}, { -1, -1}, { -1, -1}, { -1, -1}, { -1, -1}},
    {{ -1, -1}, { -1, -1}, { -1, -1}, { -1, -1}, { -1, -1}, { -1, -1}},
    {{ -1, -1}, { -1, -1}, { -1, -1}, { -1, -1}, { -1, -1}, { -1, -1}},
    {{ -1, -1}, { -1, -1}, { -1, -1}, { -1, -1}, { -1, -1}, { -1, -1}},
    {{ -1, -1}, { -1, -1}, { -1, -1}, { -1, -1}, { -1, -1}, { -1, -1}},
    {{ -1, -1}, { -1, -1}, { -1, -1}, { -1, -1}, { -1, -1}, { -1, -1}},
    {{ -1, -1}, { -1, -1}, { -1, -1}, { -1, -1}, { -1, -1}, { -1, -1}},
};

void visit(int row, int col, struct point pre)
{
    struct point visit_point = { row, col };
    maze[row][col] = 2;
    predecessor[row][col] = pre;
    push(visit_point);
}

int main(void)
{
    struct point p = { 0, 1 };
    maze[p.row][p.col] = 1;
    push(p);
    while (!is_empty())
    {
        p = pop();
        if (p.row == 7 && p.col == 4)//Goal
            break;
        if (p.col + 1 < MAX_COL
            /* right */
            && maze[p.row][p.col + 1] == 0)
            visit(p.row, p.col + 1, p);
        if (p.row + 1 < MAX_ROW
            /* down */
            && maze[p.row + 1][p.col] == 0)
            visit(p.row + 1, p.col, p);
        if (p.col - 1 >= 0
            /* left */
            && maze[p.row][p.col - 1] == 0)
            visit(p.row, p.col - 1, p);
        if (p.row - 1 >= 0
            /* up */
            && maze[p.row - 1][p.col] == 0)
            visit(p.row - 1, p.col, p);
        print_maze();
        
    }
    
    if (p.row == 7 && p.col == 4)
    {
        printf("(%d, %d)\n", p.row, p.col);
        while (predecessor[p.row][p.col].row != -1)
        {
            p = predecessor[p.row][p.col];
            printf("(%d, %d)\n", p.row, p.col);
        }
    }
    else
        printf("No path!\n");
    return 0;
}
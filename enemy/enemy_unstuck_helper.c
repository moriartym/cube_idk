#include "../cub3d.h"

void ebfs_one(t_enemy_bfs *bfs)
{
    bfs->size = bfs->width * bfs->height;
    bfs->queue_x = malloc(sizeof(int) * bfs->size);
    bfs->queue_y = malloc(sizeof(int) * bfs->size);
    bfs->front = 0;
    bfs->rear = 0;
    bfs->visited = malloc(sizeof(bool *) * bfs->height);
    bfs->prev_x = malloc(sizeof(int *) * bfs->height);
    bfs->prev_y = malloc(sizeof(int *) * bfs->height);
}

void ebfs_two(t_enemy_bfs *bfs)
{
    bfs->y = 0;
    while (bfs->y < bfs->height)
    {
        bfs->visited[bfs->y] = malloc(sizeof(bool) * bfs->width);
        bfs->prev_x[bfs->y] = malloc(sizeof(int) * bfs->width);
        bfs->prev_y[bfs->y] = malloc(sizeof(int) * bfs->width);

        bfs->x = 0;
        while (bfs->x < bfs->width)
        {
            bfs->visited[bfs->y][bfs->x] = false;
            bfs->prev_x[bfs->y][bfs->x] = -1;
            bfs->prev_y[bfs->y][bfs->x] = -1;
            bfs->x++;
        }
        bfs->y++;
    }
}

void ebfs_three(t_enemy_bfs *bfs)
{
    bfs->dir[0][0] = 0;
    bfs->dir[0][1] = -1;
    bfs->dir[1][0] = 0;
    bfs->dir[1][1] = 1;
    bfs->dir[2][0] = -1;
    bfs->dir[2][1] = 0;
    bfs->dir[3][0] = 1;
    bfs->dir[3][1] = 0;
}


void ebfs_four_helper(char **map,t_enemy_bfs *bfs)
{
    bfs->i = 0;
    while (bfs->i < 4)
    {
        bfs->nx = bfs->x + bfs->dir[bfs->i][0];
        bfs->ny = bfs->y + bfs->dir[bfs->i][1];

        if (bfs->nx >= 0 && bfs->ny >= 0 &&
            bfs->nx < bfs->width && bfs->ny < bfs->height &&
            !bfs->visited[bfs->ny][bfs->nx] && map[bfs->ny][bfs->nx] == '0')
        {
            bfs->queue_x[bfs->rear] = bfs->nx;
            bfs->queue_y[bfs->rear] = bfs->ny;
            bfs->rear++;
            bfs->visited[bfs->ny][bfs->nx] = true;
            bfs->prev_x[bfs->ny][bfs->nx] = bfs->x;
            bfs->prev_y[bfs->ny][bfs->nx] = bfs->y;
        }
        bfs->i++;
    }
}

void ebfs_four(char **map, t_enemy_bfs *bfs)
{
    bfs->queue_x[bfs->rear] = bfs->start_x;
    bfs->queue_y[bfs->rear] = bfs->start_y;
    bfs->rear++;
    bfs->visited[bfs->start_y][bfs->start_x] = true;

    while (bfs->front < bfs->rear)
    {
        bfs->x = bfs->queue_x[bfs->front];
        bfs->y = bfs->queue_y[bfs->front];
        bfs->front++;
        if (bfs->x == bfs->goal_x && bfs->y == bfs->goal_y)
            break;
        ebfs_four_helper(map, bfs);
    }
}
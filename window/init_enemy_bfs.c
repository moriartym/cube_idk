#include "../cub3d.h"

void init_dir(t_var *data, t_bfs *bfs)
{
    bfs->dirs[0][0] = 0;
    bfs->dirs[0][1] = -1;
    bfs->dirs[1][0] = 0;
    bfs->dirs[1][1] = 1;
    bfs->dirs[2][0] = -1;
    bfs->dirs[2][1] = 0;
    bfs->dirs[3][0] = 1;
    bfs->dirs[3][1] = 0;
}

void init_bfs(t_var *data, t_bfs *bfs)
{
    int y;

    y = 0;
    bfs->ipx = (int)(data->player.px / 32);
    bfs->ipy = (int)(data->player.py / 32);
    init_dir(data, bfs);
    bfs->reachable = malloc(sizeof(bool*) * data->map.height);
    while (y < data->map.height)
    {
        bfs->reachable[y] = calloc(data->map.width, sizeof(bool));
        y++;
    }
    bfs->queue_x = malloc(sizeof(int) * (data->map.width * data->map.height));
    bfs->queue_y = malloc(sizeof(int) * (data->map.width * data->map.height));
    bfs->reachable[bfs->ipy][bfs->ipx] = true;
    bfs->queue_x[bfs->rear] = bfs->ipx;
    bfs->queue_y[bfs->rear++] = bfs->ipy;
}

void bfs_check(t_var *data, t_bfs *bfs, int nx, int ny)
{
    if (nx >= 0 && nx < data->map.width && ny >= 0 && ny < data->map.height)
    {
        if (data->map.arr[ny][nx] == '0' && !bfs->reachable[ny][nx])
        {
            bfs->empty_spaces++;
            bfs->reachable[ny][nx] = true;
            bfs->queue_x[bfs->rear] = nx;
            bfs->queue_y[bfs->rear++] = ny;
        }
    }
}

void do_bfs(t_var *data, t_bfs *bfs)
{
    int x;
    int y;
    int nx;
    int i;
    int ny;

    init_bfs(data, bfs);
    while (bfs->front < bfs->rear) 
    {
        x = bfs->queue_x[bfs->front];
        y = bfs->queue_y[bfs->front++];
        i = 0;
        while (i < 4)
        {
            nx = x + bfs->dirs[i][0];
            ny = y + bfs->dirs[i][1];
            bfs_check(data, bfs, nx,ny);
            i++;
        }
    }
}
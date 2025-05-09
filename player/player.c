#include "../cub3d.h"

void player_start(t_var *data, int y, int x)
{
    data->player.py = TILE_SIZE * y + TILE_SIZE / 2 - PLAYER_SIZE / 2;
    data->player.px = TILE_SIZE * x + TILE_SIZE / 2 - PLAYER_SIZE / 2;
}

void player_location(t_var *data, t_drawp *drawp)
{
    drawp->ipx = (int)(data->player.px / TILE_SIZE);
    drawp->ipy = (int)(data->player.py / TILE_SIZE);
    drawp->rel_x = drawp->ipx - data->minimap_offset_x;
    drawp->rel_y = drawp->ipy - data->minimap_offset_y;
    drawp->offset_x = (data->player.px - drawp->ipx * TILE_SIZE) / (float)TILE_SIZE;
    drawp->offset_y = (data->player.py - drawp->ipy * TILE_SIZE) / (float)TILE_SIZE;
    drawp->draw_x = drawp->rel_x * data->minimap.tile_size + drawp->offset_x * data->minimap.tile_size;
    drawp->draw_y = drawp->rel_y * data->minimap.tile_size + drawp->offset_y * data->minimap.tile_size;
}

void draw_player(t_var *data)
{
    t_drawp drawp;
    int by;
    int bx;
    int px;
    int py;

    drawp = (t_drawp) {0};
    player_location(data, &drawp);
    by = -PLAYER_SIZE;
    while (by <= PLAYER_SIZE)
    {
        bx = -PLAYER_SIZE;
        while (bx <= PLAYER_SIZE)
        {
            px = drawp.draw_x + bx;
            py = drawp.draw_y + by;
            if (px >= 0 && px < MINIMAP_SIZE && py >= 0 && py < MINIMAP_SIZE)
                my_mlx_pixel_put(&data->image, px, py, PLAYER_COLOR);
            bx++;
        }
        by++;
    }
}

#include "../cub3d.h"


void draw_3d_helper(t_var *data, t_ray *ray, int lineOff, int lineH)
{
    int color = ray->side == 1 ? 0xCCCCCC : 0xAAAAAA;
    int x;
    int y;
    int w;

    w = 0;
    x = ray->r * STRIP_WIDTH;
    while (w < STRIP_WIDTH)
    {
        if (x + w >= WINDOW_WIDTH)
            continue;
        y = 0;
        while (y < WINDOW_HEIGHT)
        {
            if (x + w < MINIMAP_SIZE && y < MINIMAP_SIZE)
            {
                y++;
                continue;
            }
            if (y < lineOff)
                my_mlx_pixel_put(&data->image, x + w, y, CEILING_COLOR);
            else if (y >= lineOff && y < lineOff + lineH)
                my_mlx_pixel_put(&data->image, x + w, y, color);
            else
                my_mlx_pixel_put(&data->image, x + w, y, FLOOR_COLOR);
            y++;
        }
        w++;
    }
}

void draw_3d(t_var *data, t_ray *ray)
{
    double corrected_dist;
    int lineH;
    int lineOff;

    corrected_dist = ray->disH * cos(normalize_radians(data->player.pa - ray->ra));
    lineH = (TILE_SIZE * WINDOW_HEIGHT) / corrected_dist;
    if (lineH > WINDOW_HEIGHT)
        lineH = WINDOW_HEIGHT;
    lineOff = (WINDOW_HEIGHT / 2) - (lineH / 2);
    draw_3d_helper(data, ray, lineOff, lineH);
}
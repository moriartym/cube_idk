#include "../cub3d.h"

void draw_line(t_var *data, t_line line, int color)
{
    int i;

    i = 0;
    line.dx = line.rx - line.px;
    line.dy = line.ry - line.py;
    if (fabs(line.dx) > fabs(line.dy))
        line.steps = fabs(line.dx);
    else
        line.steps = fabs(line.dy);
    if (line.steps == 0)
        return;
    line.x_inc = line.dx / line.steps;
    line.y_inc = line.dy / line.steps;
    while (i <= line.steps)
    {
        line.px_int = (int)line.px;
        line.py_int = (int)line.py;
        if (line.px_int >= 0 && line.px_int < MINIMAP_SIZE 
                && line.py_int >= 0 && line.py_int < MINIMAP_SIZE) 
            my_mlx_pixel_put(&data->image, line.px_int, line.py_int, color);
        line.px += line.x_inc;
        line.py += line.y_inc;
        i++;
    }
}

void create_rayhit(t_var *data, t_ray *ray, t_rayhit *rayhit, int tile_size)
{
    rayhit->p_tile_x = (int)(data->player.px / TILE_SIZE);
    rayhit->p_tile_y = (int)(data->player.py / TILE_SIZE);
    rayhit->p_offset_x = (data->player.px - rayhit->p_tile_x * TILE_SIZE) / TILE_SIZE;
    rayhit->p_offset_y = (data->player.py - rayhit->p_tile_y * TILE_SIZE) / TILE_SIZE;
    rayhit->draw_px = (rayhit->p_tile_x - data->minimap_offset_x) * tile_size + rayhit->p_offset_x * tile_size;
    rayhit->draw_py = (rayhit->p_tile_y - data->minimap_offset_y) * tile_size + rayhit->p_offset_y * tile_size;
    rayhit->r_tile_x = (int)(ray->rx / TILE_SIZE);
    rayhit->r_tile_y = (int)(ray->ry / TILE_SIZE);
    rayhit->r_offset_x = (ray->rx - rayhit->r_tile_x * TILE_SIZE) / TILE_SIZE;
    rayhit->r_offset_y = (ray->ry - rayhit->r_tile_y * TILE_SIZE) / TILE_SIZE;
    rayhit->draw_rx = (rayhit->r_tile_x - data->minimap_offset_x) * tile_size + rayhit->r_offset_x * tile_size;
    rayhit->draw_ry = (rayhit->r_tile_y - data->minimap_offset_y) * tile_size + rayhit->r_offset_y * tile_size;
}

void cast_rays(t_var *data, t_ray *ray)
{
    float tile_size;
    t_line line;
    t_rayhit rayhit;

    line = (t_line){0};
    rayhit = (t_rayhit){0};
    tile_size = data->minimap.tile_size;
    if (ray->disH < ray->disV)
        ray->side = 1; 
    else
    {
        ray->disH = ray->disV;
        ray->rx = ray->vx;
        ray->ry = ray->vy;
    }
    create_rayhit(data, ray, &rayhit, tile_size);
    line.px = rayhit.draw_px;
    line.py = rayhit.draw_py;
    line.rx = rayhit.draw_rx;
    line.ry = rayhit.draw_ry;
    draw_line(data, line, RAYCAST_COLOR);
}

void draw_rays(t_var *data)
{
    t_ray ray;

    ray = (t_ray){0};
    ray.ra = normalize_radians(data->player.pa - (PI/6));
    ray.r = 0;
    while (ray.r < NUM_RAYS)
    {
        cast_vertical(data, &ray);
        cast_horizontal(data, &ray);
        data->zbuffer[ray.r] = fmin(ray.disH, ray.disV);
        cast_rays(data, &ray);
        draw_3d(data, &ray);
        ray.ra += (PI / 3) / NUM_RAYS;
        ray.ra = normalize_radians(ray.ra);
        ray.r++;
    }
    draw_sprites(data);
}

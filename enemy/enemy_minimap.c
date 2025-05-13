#include "../cub3d.h"

void draw_enemies_init(t_var *data, t_emini *mini, int i)
{
    mini->ex = data->sprites[i].x;
    mini->ey = data->sprites[i].y;
    mini->enemy_tile_x = (int)(mini->ex / TILE_SIZE);
    mini->enemy_tile_y = (int)(mini->ey / TILE_SIZE);
    mini->rel_x = mini->enemy_tile_x - data->minimap_offset_x;
    mini->rel_y = mini->enemy_tile_y - data->minimap_offset_y;
    mini->offset_x = (mini->ex - mini->enemy_tile_x * TILE_SIZE) / (float)TILE_SIZE;
    mini->offset_y = (mini->ey - mini->enemy_tile_y * TILE_SIZE) / (float)TILE_SIZE;
    mini->draw_x = mini->rel_x * data->minimap.tile_size + mini->offset_x * data->minimap.tile_size;
    mini->draw_y = mini->rel_y * data->minimap.tile_size + mini->offset_y * data->minimap.tile_size;
    mini->radius = SPRITE_SIZE_MAP;
    mini->by = -mini->radius;
}

void draw_enemies_loop(t_var *data, t_emini *mini)
{
    while (mini->by <= mini->radius)
    {
        mini->bx = -mini->radius;
        while (mini->bx <= mini->radius)
        {
            mini->px = mini->draw_x + mini->bx;
            mini->py = mini->draw_y + mini->by;
            if (mini->px >= 0 && mini->px < MINIMAP_SIZE &&
                mini->py >= 0 && mini->py < MINIMAP_SIZE)
                my_mlx_pixel_put(&data->image, mini->px, mini->py, ENEMY_COLOR);
            mini->bx++;
        }
        mini->by++;
    }
}

void draw_enemies_minimap(t_var *data)
{
    t_emini mini;
    int i;

    i = 0;
    mini = (t_emini){0};
    while (i < data->num_sprites)
    {
        draw_enemies_init(data, &mini, i);
        draw_enemies_loop(data, &mini);
        i++;
    }
}


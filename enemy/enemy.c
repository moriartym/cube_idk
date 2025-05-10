#include "../cub3d.h"

void draw_enemies_minimap(t_var *data)
{
    for (int i = 0; i < data->num_sprites; i++)
    {
        float ex = data->sprites[i].x;
        float ey = data->sprites[i].y;

        int enemy_tile_x = (int)(ex / TILE_SIZE);
        int enemy_tile_y = (int)(ey / TILE_SIZE);

        int rel_x = enemy_tile_x - data->minimap_offset_x;
        int rel_y = enemy_tile_y - data->minimap_offset_y;

        float offset_x = (ex - enemy_tile_x * TILE_SIZE) / (float)TILE_SIZE;
        float offset_y = (ey - enemy_tile_y * TILE_SIZE) / (float)TILE_SIZE;

        int draw_x = rel_x * data->minimap.tile_size + offset_x * data->minimap.tile_size;
        int draw_y = rel_y * data->minimap.tile_size + offset_y * data->minimap.tile_size;

        int radius = SPRITE_SIZE_MAP;

        for (int by = -radius; by <= radius; by++)
        {
            for (int bx = -radius; bx <= radius; bx++)
            {
                int px = draw_x + bx;
                int py = draw_y + by;

                if (px >= 0 && px < MINIMAP_SIZE && py >= 0 && py < MINIMAP_SIZE)
                    my_mlx_pixel_put(&data->image, px, py, ENEMY_COLOR);
            }
        }
    }
}

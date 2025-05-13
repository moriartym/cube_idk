#include "../cub3d.h"

float calculate_distance(t_var *data, t_sprite *sp)
{
    float dx;
    float dy;
    float final;

    dx = data->player.px - sp->x;
    dy = data->player.py - sp->y;
    final = sqrtf(dx * dx + dy * dy);
    return final;
}

void sort_sprites_by_distance(t_var *data)
{
    int i;
    int j;
    int dist_i;
    int dist_j;

    i = 0;
    while (i < data->num_sprites - 1)
    {
        j = i + 1;
        while (j < data->num_sprites)
        {
            dist_i = calculate_distance(data, &data->sprites[i]);
            dist_j = calculate_distance(data, &data->sprites[j]);
            if (dist_i < dist_j)
            {
                t_sprite temp = data->sprites[i];
                data->sprites[i] = data->sprites[j];
                data->sprites[j] = temp;
            }
            j++;
        }
        i++;
    }
}

void init_seq(t_edraw *draw)
{
    draw->anim_sequence[0] = 0;
    draw->anim_sequence[1] = 1;
    draw->anim_sequence[2] = 2;
    draw->anim_sequence[3] = 3;
    draw->anim_sequence[4] = 4;
    draw->anim_sequence[5] = 3;
    draw->anim_sequence[6] = 2;
    draw->anim_sequence[7] = 1;
    draw->anim_sequence[8] = 0;
    draw->anim_sequence[9] = 5;
    draw->anim_sequence[10] = 6;
    draw->anim_sequence[11] = 7;
    draw->anim_sequence[12] = 8;
    draw->anim_sequence[13] = 7;
    draw->anim_sequence[14] = 6;
    draw->anim_sequence[15] = 5;
    draw->anim_len = sizeof(draw->anim_sequence) 
                    / sizeof(draw->anim_sequence[0]);
}

void init_enemy_draw(t_var *data, t_edraw *draw)
{
    init_seq(draw);
    gettimeofday(&draw->now, NULL);
    draw->elapsed = (draw->now.tv_sec - data->last_anim_time.tv_sec) + (draw->now.tv_usec - data->last_anim_time.tv_usec) / 1000000.0;
    if (draw->elapsed > 0.1)
    {
        data->current_anim_index = (data->current_anim_index + 1) % draw->anim_len;
        gettimeofday(&data->last_anim_time, NULL);
    }
}

int enemy_size(t_var *data, t_edraw *draw, t_sprite *sp)
{
    draw->sx = sp->x - data->player.px;
    draw->sy = sp->y - data->player.py;
    draw->sin_pa = sin(-data->player.pa);
    draw->cos_pa = cos(-data->player.pa);
    draw->dx = draw->sx * draw->cos_pa - draw->sy * draw->sin_pa;
    draw->dy = draw->sx * draw->sin_pa + draw->sy * draw->cos_pa;
    if (draw->dx <= 0.1f)
        return (1);
    draw->fov_scale = (WINDOW_WIDTH / 2.0f) / tan(FOV / 2);
    draw->proj_x = (draw->dy * draw->fov_scale / draw->dx) + (WINDOW_WIDTH / 2.0f);
    draw->sprite_height = (SPRITE_SIZE * draw->fov_scale) / draw->dx;
    draw->sprite_size = (int)draw->sprite_height;
    draw->max_sprite_size = WINDOW_HEIGHT / 2;
    draw->lineH = (TILE_SIZE * WINDOW_HEIGHT) / draw->dx;
    if (draw->lineH > WINDOW_HEIGHT)
        draw->lineH = WINDOW_HEIGHT;
    draw->floorY = (WINDOW_HEIGHT / 2) + (draw->lineH / 2);
    draw->screen_x = (int)draw->proj_x - draw->sprite_size / 2;
    draw->screen_y = draw->floorY - draw->sprite_size;
    if (draw->sprite_size > draw->max_sprite_size)
        draw->screen_y = draw->floorY - draw->max_sprite_size;
    return (0);
}

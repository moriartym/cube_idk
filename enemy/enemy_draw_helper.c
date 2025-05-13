#include "../cub3d.h"

void select_frame(t_var *data, t_edraw *draw)
{
    draw->frame = draw->anim_sequence[data->current_anim_index];
    draw->cur_img = NULL;
    if (draw->frame == 0)
        draw->cur_img = &data->gif.zero;
    else if (draw->frame == 1)
        draw->cur_img = &data->gif.one;
    else if (draw->frame == 2)
        draw->cur_img = &data->gif.two;
    else if (draw->frame == 3)
        draw->cur_img = &data->gif.three;
    else if (draw->frame == 4)
        draw->cur_img = &data->gif.four;
    else if (draw->frame == 5)
        draw->cur_img = &data->gif.five;
    else if (draw->frame == 6)
        draw->cur_img = &data->gif.six;
    else if (draw->frame == 7)
        draw->cur_img = &data->gif.seven;
    else if (draw->frame == 8)
        draw->cur_img = &data->gif.eight;   
    else
        draw->cur_img = &data->gif.zero;
}

void screen_rgba(t_var *data, t_edraw *draw)
{
    draw->b = draw->pixel[0];
    draw->g = draw->pixel[1];
    draw->r = draw->pixel[2];
    draw->a = draw->pixel[3];
}

void screen_draw_helper(t_var *data, t_edraw *draw)
{
    draw->y = 0;
    while (draw->y < draw->sprite_size)
    {
        draw->py = draw->screen_y + draw->y;
        if (draw->py < 0 || draw->py >= WINDOW_HEIGHT)
        {
            draw->y++;
            continue;
        }
        draw->tx = (draw->x * draw->cur_img->width) / draw->sprite_size;
        draw->ty = (draw->y * draw->cur_img->height) / draw->sprite_size;
        draw->offset = draw->ty * draw->cur_img->line_length
                    + draw->tx * (draw->cur_img->bits_per_pixel / 8);
        draw->pixel = draw->cur_img->addr + draw->offset;
        screen_rgba(data, draw);
        if (draw->a != 0)
        {
            draw->y++;
            continue;
        }
        draw->color = (draw->r << 16) | (draw->g << 8) | draw->b;
        my_mlx_pixel_put(&data->image, draw->px, draw->py, draw->color);
        draw->y++;
    }
}

void screen_draw(t_var *data, t_edraw *draw)
{
    draw->x = 0;
    while (draw->x < draw->sprite_size)
    {
        draw->px = draw->screen_x + draw->x;
        if (draw->px < 0 || draw->px >= WINDOW_WIDTH)
        {
            draw->x++;
            continue;
        }
        draw->ray_idx = (draw->px * NUM_RAYS) / WINDOW_WIDTH;
        if (draw->ray_idx < 0 || draw->ray_idx >= NUM_RAYS || draw->dx > data->zbuffer[draw->ray_idx])
        {
            draw->x++;
            continue;
        }
        screen_draw_helper(data, draw);
        draw->x++;
    }
}

void draw_sprites(t_var *data)
{
    t_edraw draw;
    t_sprite *sp;
    int i;

    draw = (t_edraw){0};
    if (data->num_sprites == 0)
        return;
    sort_sprites_by_distance(data);
    init_enemy_draw(data, &draw);
    i = 0;
    while (i < data->num_sprites)
    {
        sp = &data->sprites[i];
        move_enemy_towards_player(data, sp);
        if (enemy_size(data, &draw, sp))
        {
            i++;
            continue;
        }
        select_frame(data, &draw);
        screen_draw(data, &draw);
        i++;
    }
}

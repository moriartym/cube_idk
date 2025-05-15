#include "../cub3d.h"

int is_player_caught(t_sprite *sp, t_play *player, float radius)
{
    float dx;
    float dy;
    float dist;

    dx = sp->x - player->px;
    dy = sp->y - player->py;
    dist = sqrtf(dx * dx + dy * dy);
    return dist < radius;
}

bool is_cell_valid(t_var *data, int x, int y)
{
    if (x < 0 || x >= data->map.width || y < 0 || y >= data->map.height)
        return false;
    return (data->map.arr[y][x] != '1' && data->map.arr[y][x] != '2');
}

void resolve_enemy_dist(t_var *data, t_sprite *sp, t_sprite *other)
{
    float sp_new_x;
    float sp_new_y;
    float other_new_x;
    float other_new_y;
    
    if (sp->dist_sq < sp->min_dist * sp->min_dist && sp->dist_sq > 0)
    {
        sp->dist = sqrt(sp->dist_sq);
        sp->overlap = (sp->min_dist - sp->dist) / 2.0f;
        sp->adjust_x = (sp->dx / sp->dist) * sp->overlap;
        sp->adjust_y = (sp->dy / sp->dist) * sp->overlap;
        sp_new_x = sp->x - sp->adjust_x;
        sp_new_y = sp->y - sp->adjust_y;
        other_new_x = other->x + sp->adjust_x;
        other_new_y = other->y + sp->adjust_y;
        if (is_cell_valid(data, (int)sp_new_x/TILE_SIZE, (int)sp->y/TILE_SIZE))
            sp->x = sp_new_x;
        if (is_cell_valid(data, (int)sp->x/TILE_SIZE, (int)sp_new_y/TILE_SIZE))
            sp->y = sp_new_y;
        if (is_cell_valid(data, (int)other_new_x/TILE_SIZE, (int)other->y/TILE_SIZE))
            other->x = other_new_x;
        if (is_cell_valid(data, (int)other->x/TILE_SIZE, (int)other_new_y/TILE_SIZE))
            other->y = other_new_y;
    }
}

void resolve_enemy_collisions(t_var *data, t_sprite *sp)
{
    int i;
    t_sprite *other;

    i = 0;
    while (i < data->num_sprites)
    {
        other = &data->sprites[i];
        if (other == sp) 
        {
            i++;
            continue;
        }
        sp->dx = other->x - sp->x;
        sp->dy = other->y - sp->y;
        sp->dist_sq = sp->dx * sp->dx + sp->dy * sp->dy;
        sp->min_dist = 10.0f;
        resolve_enemy_dist(data,sp, other);
        i++;
    }
}

void move_enemy_towards_player(t_var *data, t_sprite *sp)
{
    sp->speed = 0.15f;
    sp->margin = 5.0f;
    sp->lil_margin = 0.15f;
    sp->spx = (int)(sp->x / TILE_SIZE);
    sp->spy = (int)(sp->y / TILE_SIZE);
    sp->spx_left = (int)((sp->x - sp->speed - sp->margin) / TILE_SIZE);
    sp->spx_right = (int)((sp->x + sp->speed + sp->margin) / TILE_SIZE);
    sp->spy_up = (int)((sp->y - sp->speed - sp->margin) / TILE_SIZE);
    sp->spy_down = (int)((sp->y + sp->speed + sp->margin) / TILE_SIZE);
    if (sp->is_unstucking)
    {
        unstuck_move(data, sp);
        return ;
    }
    enemy_left(data,sp);
    enemy_right(data,sp);
    enemy_up(data,sp);
    enemy_down(data,sp);
    resolve_enemy_collisions(data, sp);
    if (is_player_caught(sp, &data->player, 10.0f))
        printf("Player caught! 👻\n");
}

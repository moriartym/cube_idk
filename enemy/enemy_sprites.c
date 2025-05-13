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

void resolve_enemy_collisions(t_var *data, t_sprite *sp) {
    for (int i = 0; i < data->num_sprites; ++i) {
        t_sprite *other = &data->sprites[i];
        if (other == sp) continue;

        float dx = other->x - sp->x;
        float dy = other->y - sp->y;
        float dist_sq = dx*dx + dy*dy;
        float min_dist = 10.0f; // Adjust based on enemy size

        if (dist_sq < min_dist * min_dist && dist_sq > 0) {
            float dist = sqrt(dist_sq);
            float overlap = (min_dist - dist) / 2.0f;
            float adjust_x = (dx / dist) * overlap;
            float adjust_y = (dy / dist) * overlap;

            sp->x -= adjust_x;
            sp->y -= adjust_y;
            other->x += adjust_x;
            other->y += adjust_y;
        }
    }
}

bool is_cell_valid(t_var *data, int x, int y) {
    if (x < 0 || x >= data->map.width || y < 0 || y >= data->map.height)
        return false;
    return (data->map.arr[y][x] != '1' && data->map.arr[y][x] != '2');
}

void move_enemy_towards_player(t_var *data, t_sprite *sp) {
    int spx = (int)(sp->x / TILE_SIZE);
    int spy = (int)(sp->y / TILE_SIZE);
    float speed = 0.1f;
    float offset = 10;

    int spx_left = (int)((sp->x - speed - offset) / TILE_SIZE);
    int spx_right = (int)((sp->x + speed + offset) / TILE_SIZE);
    int spy_up = (int)((sp->y - speed - offset) / TILE_SIZE);
    int spy_down = (int)((sp->y + speed + offset) / TILE_SIZE);

    // === Stuck check every 5 seconds ===
    sp->stuck_timer++;
    if (sp->stuck_timer >= 300) { // Assuming ~60 FPS
        float dx = fabsf(sp->x - sp->lx);
        float dy = fabsf(sp->y - sp->ly);
        float dist = sqrtf(dx * dx + dy * dy);

        printf("Enemy distance moved in 5 sec: %.2f\n", dist);

        if (dist < 16.0f) {
            sp->stuck = 1;
            printf("Enemy marked as stuck due to low movement\n");
        }
        sp->lx = sp->x;
        sp->ly = sp->y;
        sp->stuck_timer = 0;
    }

    // === Try to move directly toward player ===
    if (!sp->stuck && sp->x > data->player.px && is_cell_valid(data, spx_left, spy)) {
        sp->x -= speed;
    }
    if (!sp->stuck && sp->x < data->player.px && is_cell_valid(data, spx_right, spy)) {
        sp->x += speed;
    }
    if (!sp->stuck && sp->y > data->player.py && is_cell_valid(data, spx, spy_up)) {
        sp->y -= speed;
    }
    if (!sp->stuck && sp->y < data->player.py && is_cell_valid(data, spx, spy_down)) {
        sp->y += speed;
    }

    // === If not already stuck, but failed to reach target ===
    // if (!sp->stuck) {
    //     if (sp->x > data->player.px && abs(sp->x - data->player.px) > 10)
    //         sp->t_left = 1;
    //     else if (sp->x < data->player.px && abs(sp->x - data->player.px) > 10)
    //         sp->t_right = 1;
    //     else if (sp->y > data->player.py && abs(sp->y - data->player.py) > 10)
    //         sp->t_up = 1;
    //     else if (sp->y < data->player.py && abs(sp->y - data->player.py) > 10)
    //         sp->t_down = 1;
    // }

    if (sp->stuck && !sp->t_left && !sp->t_right && !sp->t_down && !sp->t_up)
    {
        printf("Enemy stuck at (%.2f, %.2f). Player at (%.2f, %.2f)\n", sp->x, sp->y, data->player.px, data->player.py);
        if (sp->x > data->player.px && abs(sp->x - data->player.px) > 5) {
            sp->t_left = 1;
            printf("Trying to move left around obstacle\n");
        }
        if (sp->x < data->player.px && abs(sp->x - data->player.px) > 5) {
            sp->t_right = 1;
            printf("Trying to move right around obstacle\n");
        }
        if (sp->y > data->player.py && abs(sp->y - data->player.py) > 5) {
            sp->t_up = 1;
            printf("Trying to move up around obstacle\n");
        }
        if (sp->y < data->player.py && abs(sp->y - data->player.py) > 5) {
            sp->t_down = 1;
            printf("Trying to move down around obstacle\n");
        }
    }


    // === Stuck Movement Logic ===
    if (sp->stuck && sp->t_left) {
        printf("gogogo\n");
        if (sp->up == 0 && sp->down == 0)
            sp->up = 1;

        if (sp->up && is_cell_valid(data, spx, spy_up))
            sp->y -= speed;
        else {
            sp->up = 0;
            sp->down = 1;
        }

        if (sp->down && is_cell_valid(data, spx, spy_down))
            sp->y += speed;
        else {
            sp->t_left = 0;
            sp->stuck = 0;
            sp->up = 0;
            sp->down = 0;
        }

        if (is_cell_valid(data, spx_left, spy)) {
            sp->t_left = 0;
            sp->stuck = 0;
            sp->up = 0;
            sp->down = 0;
        }
    }
    else if (sp->stuck && sp->t_right) {
        if (sp->up == 0 && sp->down == 0)
            sp->up = 1;

        if (sp->up && is_cell_valid(data, spx, spy_up))
            sp->y -= speed;
        else {
            sp->up = 0;
            sp->down = 1;
        }

        if (sp->down && is_cell_valid(data, spx, spy_down))
            sp->y += speed;
        else {
            sp->t_right = 0;
            sp->stuck = 0;
            sp->up = 0;
            sp->down = 0;
        }

        if (is_cell_valid(data, spx_right, spy)) {
            sp->t_right = 0;
            sp->stuck = 0;
            sp->up = 0;
            sp->down = 0;
        }
    }
    else if (sp->stuck && sp->t_up) {
        if (sp->left == 0 && sp->right == 0)
            sp->left = 1;

        if (sp->left && is_cell_valid(data, spx_left, spy))
            sp->x -= speed;
        else {
            sp->left = 0;
            sp->right = 1;
        }

        if (sp->right && is_cell_valid(data, spx_right, spy))
            sp->x += speed;
        else {
            sp->t_up = 0;
            sp->stuck = 0;
            sp->left = 0;
            sp->right = 0;
        }

        if (is_cell_valid(data, spx, spy_up)) {
            sp->t_up = 0;
            sp->stuck = 0;
            sp->left = 0;
            sp->right = 0;
        }
    }
    else if (sp->stuck && sp->t_down) {
        if (sp->left == 0 && sp->right == 0)
            sp->left = 1;

        if (sp->left && is_cell_valid(data, spx_left, spy))
            sp->x -= speed;
        else {
            sp->left = 0;
            sp->right = 1;
        }

        if (sp->right && is_cell_valid(data, spx_right, spy))
            sp->x += speed;
        else {
            sp->t_down = 0;
            sp->stuck = 0;
            sp->left = 0;
            sp->right = 0;
        }

        if (is_cell_valid(data, spx, spy_down)) {
            sp->t_down = 0;
            sp->stuck = 0;
            sp->left = 0;
            sp->right = 0;
        }
    }

    resolve_enemy_collisions(data, sp);

    if (is_player_caught(sp, &data->player, 10.0f)) {
        printf("Player caught!\n");
        // Handle game over
    }
}

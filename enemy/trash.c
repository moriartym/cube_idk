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

void find_escape_direction(t_var* data, t_sprite* sp, int block_x, int block_y, const char* direction) {
    if (strcmp(direction, "horizontal") == 0) {
        // Stuck left/right → Search up/down
        for (int dy = 1; dy <= 5; dy++) {
            if (is_cell_valid(data, block_x, block_y + dy)) {
                sp->try_down = 1;
                return;
            }
        }
        for (int dy = 1; dy <= 5; dy++) {
            if (is_cell_valid(data, block_x, block_y - dy)) {
                sp->try_up = 1;
                return;
            }
        }
    } else if (strcmp(direction, "vertical") == 0) {
        // Stuck up/down → Search left/right
        for (int dx = 1; dx <= 5; dx++) {
            if (is_cell_valid(data, block_x + dx, block_y)) {
                sp->try_right = 1;
                return;
            }
        }
        for (int dx = 1; dx <= 5; dx++) {
            if (is_cell_valid(data, block_x - dx, block_y)) {
                sp->try_left = 1;
                return;
            }
        }
    }
}


void move_enemy_towards_player(t_var *data, t_sprite *sp) {
    float speed = 0.1f;
    float margin = 5.0f;
    float lil_margin = 0.1f;

    int spx = (int)(sp->x / TILE_SIZE);
    int spy = (int)(sp->y / TILE_SIZE);

    int spx_left = (int)((sp->x - speed - margin) / TILE_SIZE);
    int spx_right = (int)((sp->x + speed + margin) / TILE_SIZE);
    int spy_up = (int)((sp->y - speed - margin) / TILE_SIZE);
    int spy_down = (int)((sp->y + speed + margin) / TILE_SIZE);

 
   if (sp->is_unstucking) {
    speed = 1;
    lil_margin = 1;
    // Handle horizontal blockages
    if (sp->go_left) {
        if (!sp->try_up && !sp->try_down) {
            find_escape_direction(data, sp, spx_left, spy, "horizontal");
        }
    }
    if (sp->go_right) {
        if (!sp->try_up && !sp->try_down) {
            find_escape_direction(data, sp, spx_right, spy, "horizontal");
        }
    }

    // Handle vertical blockages
    if (sp->go_up) {
        if (!sp->try_left && !sp->try_right) {
            find_escape_direction(data, sp, spx, spy_up, "vertical");
        }
    }
    if (sp->go_down) {
        if (!sp->try_left && !sp->try_right) {
            find_escape_direction(data, sp, spx, spy_down, "vertical");
        }
    }

    // Apply movement based on try flags
   if (sp->try_down) {
    if (is_cell_valid(data, spx, spy_down)) {
        // Horizontal nudge while moving down
        if (!is_cell_valid(data, spx_left, spy) && is_cell_valid(data, spx, spy))
            sp->x += lil_margin;
        if (!is_cell_valid(data, spx_right, spy) && is_cell_valid(data, spx, spy))
            sp->x -= lil_margin;

        sp->y += speed;
    } else {
        sp->try_right = 0;
        sp->try_up = 0;
        sp->try_down = 0;
        sp->try_left = 0;
        sp->go_up = 0;
        sp->go_down = 0;
        sp->go_right = 0;
        sp->go_left = 0;
        sp->is_unstucking = 0;
    }
    }

    if (sp->try_up) {
        if (is_cell_valid(data, spx, spy_up)) {
            // Horizontal nudge while moving up
            if (!is_cell_valid(data, spx_left, spy) && is_cell_valid(data, spx, spy))
                sp->x += lil_margin;
            if (!is_cell_valid(data, spx_right, spy) && is_cell_valid(data, spx, spy))
                sp->x -= lil_margin;

            sp->y -= speed;
        } else {
            sp->try_right = 0;
            sp->try_up = 0;
            sp->try_down = 0;
            sp->try_left = 0;
            sp->go_up = 0;
            sp->go_down = 0;
            sp->go_right = 0;
            sp->go_left = 0;
            sp->is_unstucking = 0;
        }
    }

    if (sp->try_right) {
        if (is_cell_valid(data, spx_right, spy)) {
            // Vertical nudge while moving right
            if (!is_cell_valid(data, spx, spy_up) && is_cell_valid(data, spx, spy))
                sp->y += lil_margin;
            if (!is_cell_valid(data, spx, spy_down) && is_cell_valid(data, spx, spy))
                sp->y -= lil_margin;

            sp->x += speed;
        } else {
            sp->try_right = 0;
            sp->try_up = 0;
            sp->try_down = 0;
            sp->try_left = 0;
            sp->go_up = 0;
            sp->go_down = 0;
            sp->go_right = 0;
            sp->go_left = 0;
            sp->is_unstucking = 0;
        }
    }

    if (sp->try_left) {
        if (is_cell_valid(data, spx_left, spy)) {
            // Vertical nudge while moving left
            if (!is_cell_valid(data, spx, spy_up) && is_cell_valid(data, spx, spy))
                sp->y += lil_margin;
            if (!is_cell_valid(data, spx, spy_down) && is_cell_valid(data, spx, spy))
                sp->y -= lil_margin;

            sp->x -= speed;
        } else {
            sp->try_right = 0;
            sp->try_up = 0;
            sp->try_down = 0;
            sp->try_left = 0;
            sp->go_up = 0;
            sp->go_down = 0;
            sp->go_right = 0;
            sp->go_left = 0;
            sp->is_unstucking = 0;
        }
    }


    resolve_enemy_collisions(data, sp);
    return;
}


    // ======== STUCK DETECTION & ESCAPE ========
    // Horizontal stuck detection
    if (!is_cell_valid(data, spx_left, spy) && fabsf(sp->y - data->player.py) < margin) {
        printf("stuck left\n");
        sp->is_unstucking = 1;
        sp->go_left = 1;
        return;
    }

    if (!is_cell_valid(data, spx_right, spy) && fabsf(sp->y - data->player.py) < margin) {
        printf("stuck right\n");
        sp->is_unstucking = 1;
        sp->go_right = 1;
        return;
    }

    // Vertical stuck detection
    if (!is_cell_valid(data, spx, spy_up) && fabsf(sp->x - data->player.px) < margin) {
        printf("stuck up\n");
        sp->is_unstucking = 1;
        sp->go_up = 1;
        return;
    }

    if (!is_cell_valid(data, spx, spy_down) && fabsf(sp->x - data->player.px) < margin) {
        printf("stuck down\n");
        sp->is_unstucking = 1;
        sp->go_down = 1;
        return;
    }

    // ======== HORIZONTAL MOVEMENT WITH VERTICAL NUDGE IF BLOCKED ========
    if (sp->x > data->player.px && is_cell_valid(data, spx_left, spy)) {
        if (!is_cell_valid(data, spx, spy_up) && is_cell_valid(data, spx, spy))
            sp->y += lil_margin;
        if (!is_cell_valid(data, spx, spy_down) && is_cell_valid(data, spx, spy))
            sp->y -= lil_margin;
        sp->x -= speed;

    } else if (sp->x < data->player.px && is_cell_valid(data, spx_right, spy)) {
        if (!is_cell_valid(data, spx, spy_up) && is_cell_valid(data, spx, spy))
            sp->y += lil_margin;
        if (!is_cell_valid(data, spx, spy_down) && is_cell_valid(data, spx, spy))
            sp->y -= lil_margin;
        sp->x += speed;
    }

    // ======== VERTICAL MOVEMENT WITH HORIZONTAL NUDGE IF BLOCKED ========
    if (sp->y > data->player.py && is_cell_valid(data, spx, spy_up)) {
        if (!is_cell_valid(data, spx_left, spy) && is_cell_valid(data, spx, spy))
            sp->x += lil_margin;
        if (!is_cell_valid(data, spx_right, spy) && is_cell_valid(data, spx, spy))
            sp->x -= lil_margin;
        sp->y -= speed;

    } else if (sp->y < data->player.py && is_cell_valid(data, spx, spy_down)) {
        if (!is_cell_valid(data, spx_left, spy) && is_cell_valid(data, spx, spy))
            sp->x += lil_margin;
        if (!is_cell_valid(data, spx_right, spy) && is_cell_valid(data, spx, spy))
            sp->x -= lil_margin;
        sp->y += speed;
    }

    resolve_enemy_collisions(data, sp);

    if (is_player_caught(sp, &data->player, 10.0f)) {
        printf("Player caught! 👻\n");
    }
}

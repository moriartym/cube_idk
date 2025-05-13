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
    const float SPEED = 0.3f;
    const float STUCK_THRESHOLD = 25.0f;  // Distance to consider unstuck
    const int MAX_ESCAPE_ATTEMPTS = 120;  // 2 seconds at 60 FPS

    float dx = data->player.px - sp->x;
    float dy = data->player.py - sp->y;
    float distance_to_player = sqrtf(dx*dx + dy*dy);

    // Normalize direction vector
    if (distance_to_player > 0) {
        dx /= distance_to_player;
        dy /= distance_to_player;
    }

    // --- Stuck System ---
    if (sp->stuck) {
        // Track how long we've been trying to escape
        sp->stuck_escape_timer++;
        
        // Continue moving in escape direction if possible
        float escape_dx = sp->stuck_escape_x;
        float escape_dy = sp->stuck_escape_y;
        
        int new_x = (int)((sp->x + escape_dx * SPEED) / TILE_SIZE);
        int new_y = (int)((sp->y + escape_dy * SPEED) / TILE_SIZE);
        
        if (is_cell_valid(data, new_x, new_y)) {
            sp->x += escape_dx * SPEED;
            sp->y += escape_dy * SPEED;
        }
        else {
            // Find new escape direction perpendicular to player direction
            float temp = escape_dx;
            sp->stuck_escape_x = -escape_dy;
            sp->stuck_escape_y = temp;
        }

        // Check if we've moved enough to become unstuck
        float moved_distance = sqrtf(powf(sp->x - sp->lx, 2) + powf(sp->y - sp->ly, 2));
        if (moved_distance > STUCK_THRESHOLD || sp->stuck_escape_timer > MAX_ESCAPE_ATTEMPTS) {
            sp->stuck = 0;
            sp->stuck_escape_timer = 0;
            printf("Enemy unstuck!\n");
        }
    }
    else {
        // --- Normal Movement ---
        float target_x = sp->x + dx * SPEED;
        float target_y = sp->y + dy * SPEED;
        
        // Check X movement
        int new_spx = (int)(target_x / TILE_SIZE);
        if (is_cell_valid(data, new_spx, (int)(sp->y / TILE_SIZE))) {
            sp->x = target_x;
        }
        
        // Check Y movement
        int new_spy = (int)(target_y / TILE_SIZE);
        if (is_cell_valid(data, (int)(sp->x / TILE_SIZE), new_spy)) {
            sp->y = target_y;
        }

        // --- Stuck Detection ---
        sp->stuck_timer++;
        if (sp->stuck_timer >= 300) {  // 5 seconds at 60 FPS
            float moved_dist = sqrtf(powf(sp->x - sp->lx, 2) + powf(sp->y - sp->ly, 2));
            
            if (moved_dist < 16.0f) {
                sp->stuck = 1;
                sp->stuck_escape_x = -dy;  // Initial perpendicular direction
                sp->stuck_escape_y = dx;
                sp->lx = sp->x;
                sp->ly = sp->y;
                printf("Enemy stuck! Trying escape direction: (%.2f, %.2f)\n", 
                      sp->stuck_escape_x, sp->stuck_escape_y);
            }
            sp->stuck_timer = 0;
            sp->lx = sp->x;
            sp->ly = sp->y;
        }
    }

    resolve_enemy_collisions(data, sp);

    if (is_player_caught(sp, &data->player, 10.0f)) {
        printf("Player caught!\n");
        // Handle game over
    }
}
#include "../cub3d.h"

int is_player_caught(t_sprite *sp, t_play *player, float radius) {
    float dx = sp->x - player->px;
    float dy = sp->y - player->py;
    float dist = sqrtf(dx * dx + dy * dy);
    return dist < radius;
}


// Utility function to check for walls (simplified)
int is_wall_at(float x, float y, t_var *data) {
    int map_x = (int)(x / TILE_SIZE);
    int map_y = (int)(y / TILE_SIZE);
    
    if (map_x < 0 || map_x >= data->map.width || map_y < 0 || map_y >= data->map.height)
        return 1;  // Outside the map or wall

    if (data->map.arr[map_y][map_x] == '1')  // 1 represents a wall
        return 1;  // Wall found
    return 0;  // No wall
}

int is_wall_near(float x, float y, t_var *data, float margin) {
    return (
        is_wall_at(x - margin, y - margin, data) ||
        is_wall_at(x + margin, y - margin, data) ||
        is_wall_at(x - margin, y + margin, data) ||
        is_wall_at(x + margin, y + margin, data)
    );
}


// Helper function to calculate distance between player and enemy
float calculate_distance(t_var *data, t_sprite *sp) {
    float dx = data->player.px - sp->x;
    float dy = data->player.py - sp->y;
    return sqrtf(dx * dx + dy * dy);
}

// Function to manually sort sprites by distance (descending order)
void sort_sprites_by_distance(t_var *data) {
    int num_sprites = data->num_sprites;
    for (int i = 0; i < num_sprites - 1; i++) {
        for (int j = i + 1; j < num_sprites; j++) {
            // Calculate distances for both sprites
            float dist_i = calculate_distance(data, &data->sprites[i]);
            float dist_j = calculate_distance(data, &data->sprites[j]);

            // Swap if the distance is greater for the first sprite (farthest first)
            if (dist_i < dist_j) {
                t_sprite temp = data->sprites[i];
                data->sprites[i] = data->sprites[j];
                data->sprites[j] = temp;
            }
        }
    }
}


void move_enemy_towards_player(t_var *data, t_sprite *sp) {
    float dx = data->player.px - sp->x;
    float dy = data->player.py - sp->y;
    float dist = sqrtf(dx * dx + dy * dy);
    if (dist == 0) return;

    dx /= dist;
    dy /= dist;

    float speed = 0.2f;
    float collision_margin = 5.0f; // Half of enemy size (10/2)

    // Calculate desired movement
    float desired_x = sp->x + dx * speed;
    float desired_y = sp->y + dy * speed;

    // Check direct path with dynamic margin
    if (!is_wall_near(desired_x, desired_y, data, collision_margin)) {
        sp->x = desired_x;
        sp->y = desired_y;
    } else {
        // Calculate perpendicular directions for wall sliding
        float perp_x1 = dy;
        float perp_y1 = -dx;
        float perp_x2 = -dy;
        float perp_y2 = dx;

        // Try first perpendicular direction
        float slide_x = sp->x + perp_x1 * speed;
        float slide_y = sp->y + perp_y1 * speed;
        if (!is_wall_near(slide_x, slide_y, data, collision_margin)) {
            sp->x = slide_x;
            sp->y = slide_y;
            return;
        }

        // Try second perpendicular direction
        slide_x = sp->x + perp_x2 * speed;
        slide_y = sp->y + perp_y2 * speed;
        if (!is_wall_near(slide_x, slide_y, data, collision_margin)) {
            sp->x = slide_x;
            sp->y = slide_y;
            return;
        }

        // Try pure X-axis movement
        if (!is_wall_near(sp->x + dx * speed, sp->y, data, collision_margin)) {
            sp->x += dx * speed;
        }
        // Try pure Y-axis movement
        else if (!is_wall_near(sp->x, sp->y + dy * speed, data, collision_margin)) {
            sp->y += dy * speed;
        }
        // Try reverse directions
        else {
            // Reverse X
            if (!is_wall_near(sp->x - dx * speed, sp->y, data, collision_margin)) {
                sp->x -= dx * speed;
            }
            // Reverse Y
            else if (!is_wall_near(sp->x, sp->y - dy * speed, data, collision_margin)) {
                sp->y -= dy * speed;
            }
        }
    }

    // Player collision check
    if (is_player_caught(sp, &data->player, 10.0f)) {
        printf("The player died\n");
        // Handle game over
    }
}

void draw_sprites(t_var *data) {
    int num_sprites = data->num_sprites;
    if (num_sprites == 0)
        return;

    // Sort sprites by distance in descending order (farthest first)
    sort_sprites_by_distance(data);

    // Update animation frame
    static const int anim_sequence[] = {0, 1, 2, 3, 4, 3, 2, 1, 0, 5, 6, 7, 8};
    static const int anim_len = sizeof(anim_sequence) / sizeof(anim_sequence[0]);

    struct timeval now;
    gettimeofday(&now, NULL);
    double elapsed = (now.tv_sec - data->last_anim_time.tv_sec) +
                     (now.tv_usec - data->last_anim_time.tv_usec) / 1000000.0;

    if (elapsed > 0.1) {
        data->current_anim_index = (data->current_anim_index + 1) % anim_len;
        gettimeofday(&data->last_anim_time, NULL);
    }

    // Loop through sorted sprites
    for (int i = 0; i < num_sprites; i++) {
        t_sprite *sp = &data->sprites[i];

        // Move enemy toward player
        move_enemy_towards_player(data, sp);

        float sx = sp->x - data->player.px;
        float sy = sp->y - data->player.py;

        float sin_pa = sin(-data->player.pa);
        float cos_pa = cos(-data->player.pa);

        float dx = sx * cos_pa - sy * sin_pa;
        float dy = sx * sin_pa + sy * cos_pa;

        if (dx <= 0.1f) continue;

        float fov_scale = (WINDOW_WIDTH / 2.0f) / tan(FOV / 2);
        float proj_x = (dy * fov_scale / dx) + (WINDOW_WIDTH / 2.0f);
        float sprite_height = (SPRITE_SIZE * fov_scale) / dx;
        int sprite_size = (int)sprite_height;

        int max_sprite_size = WINDOW_HEIGHT / 2;
        float lineH = (TILE_SIZE * WINDOW_HEIGHT) / dx;
        lineH = lineH > WINDOW_HEIGHT ? WINDOW_HEIGHT : lineH;
        int floorY = (WINDOW_HEIGHT / 2) + (lineH / 2);

        int screen_x = (int)proj_x - sprite_size / 2;
        int screen_y = (sprite_size > max_sprite_size)
            ? floorY - max_sprite_size
            : floorY - sprite_size;

        // Select current animation image
        int frame = anim_sequence[data->current_anim_index];
        t_img *cur_img = NULL;
        switch (frame) {
            case 0: cur_img = &data->gif.zero; break;
            case 1: cur_img = &data->gif.one; break;
            case 2: cur_img = &data->gif.two; break;
            case 3: cur_img = &data->gif.three; break;
            case 4: cur_img = &data->gif.four; break;
            case 5: cur_img = &data->gif.five; break;
            case 6: cur_img = &data->gif.six; break;
            case 7: cur_img = &data->gif.seven; break;
            case 8: cur_img = &data->gif.eight; break;
            default: cur_img = &data->gif.zero; break;
        }

        // Draw the sprite
        for (int x = 0; x < sprite_size; x++) {
            int px = screen_x + x;
            if (px < 0 || px >= WINDOW_WIDTH) continue;

            int ray_idx = (px * NUM_RAYS) / WINDOW_WIDTH;
            if (ray_idx < 0 || ray_idx >= NUM_RAYS) continue;
            if (dx > data->zbuffer[ray_idx]) continue;

            for (int y = 0; y < sprite_size; y++) {
                int py = screen_y + y;
                if (py < 0 || py >= WINDOW_HEIGHT) continue;

                int tx = (x * cur_img->width) / sprite_size;
                int ty = (y * cur_img->height) / sprite_size;

                int offset = ty * cur_img->line_length + tx * (cur_img->bits_per_pixel / 8);
                char *pixel = cur_img->addr + offset;
                unsigned char b = pixel[0];
                unsigned char g = pixel[1];
                unsigned char r = pixel[2];
                unsigned char a = pixel[3];

                if (a != 0) continue;  // Skip transparent pixels

                int color = (r << 16) | (g << 8) | b;
                my_mlx_pixel_put(&data->image, px, py, color);
            }
        }
    }
}

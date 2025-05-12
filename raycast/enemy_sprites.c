#include "../cub3d.h"

int is_player_caught(t_sprite *sp, t_play *player, float radius) {
    float dx = sp->x - player->px;
    float dy = sp->y - player->py;
    float dist = sqrtf(dx * dx + dy * dy);
    return dist < radius;
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

bool is_valid(t_var *data, int x, int y, bool visited[data->map.height][data->map.width], t_sprite *current_enemy) {
    if (x < 0 || x >= data->map.width || y < 0 || y >= data->map.height)
        return false;
    if (data->map.arr[y][x] == '1'|| data->map.arr[y][x] == '2' || visited[y][x])
        return false;
    return true;
}

int bfs(t_var *data, Point start, Point goal, Point path[], int *path_len, t_sprite *current_enemy) {
    Point queue[data->map.height * data->map.width];
    Point came_from[data->map.height][data->map.width];
    bool visited[data->map.height][data->map.width];

    for (int i = 0; i < data->map.height; ++i) {
        for (int j = 0; j < data->map.width; ++j) {
            visited[i][j] = false;
        }
    }

    int front = 0, back = 0;
    queue[back++] = start;
    visited[start.y][start.x] = true;

    bool found = false;

    while (front < back) {
        Point current = queue[front++];
        if (current.x == goal.x && current.y == goal.y) {
            found = true;
            break;
        }

        Point directions[] = {{1,0}, {-1,0}, {0,1}, {0,-1}};
        for (int i = 0; i < 4; ++i) {
            int nx = current.x + directions[i].x;
            int ny = current.y + directions[i].y;
            if (is_valid(data, nx, ny, visited, current_enemy)) {
                queue[back++] = (Point){nx, ny};
                visited[ny][nx] = true;
                came_from[ny][nx] = current;
            }
        }
    }

    if (!found) {
        *path_len = 0;
        return 0;
    }

    // Reconstruct path
    Point current = goal;
    int length = 0;
    while (!(current.x == start.x && current.y == start.y)) {
        path[length++] = current;
        current = came_from[current.y][current.x];
    }
    *path_len = length;
    return 1;
}


void clamp_position_to_walls(t_var *data, t_sprite *sp) {
    int ex = (int)(sp->x / TILE_SIZE);
    int ey = (int)(sp->y / TILE_SIZE);

    // Clamp position to stay 5 pixels away from adjacent walls
    // Left wall
    if (ex > 0 && (data->map.arr[ey][ex - 1] == '1' || data->map.arr[ey][ex - 1] == '2')) {
        float left_boundary = ex * TILE_SIZE + 5;
        if (sp->x < left_boundary)
            sp->x = left_boundary;
    }
    // Right wall
    if (ex < data->map.width - 1 && (data->map.arr[ey][ex + 1] == '1' || data->map.arr[ey][ex + 1] == '2')) {
        float right_boundary = (ex + 1) * TILE_SIZE - 5;
        if (sp->x > right_boundary)
            sp->x = right_boundary;
    }
    // Top wall
    if (ey > 0 && (data->map.arr[ey - 1][ex] == '1' || data->map.arr[ey - 1][ex] == '2')) {
        float top_boundary = ey * TILE_SIZE + 5;
        if (sp->y < top_boundary)
            sp->y = top_boundary;
    }
    // Bottom wall
    if (ey < data->map.height - 1 && (data->map.arr[ey + 1][ex] == '1' && data->map.arr[ey + 1][ex] == '2')) {
        float bottom_boundary = (ey + 1) * TILE_SIZE - 5;
        if (sp->y > bottom_boundary)
            sp->y = bottom_boundary;
    }
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

void move_enemy_towards_player(t_var *data, t_sprite *sp) {
    float dx_to_player = data->player.px - sp->x;
    float dy_to_player = data->player.py - sp->y;
    float dist_to_player = sqrt(dx_to_player * dx_to_player + dy_to_player * dy_to_player);

    if (dist_to_player < TILE_SIZE) {
        float speed = 0.3f;
        if (dist_to_player > 1.0f) {
            sp->x += speed * (dx_to_player / dist_to_player);
            sp->y += speed * (dy_to_player / dist_to_player);
        }
    } else {
        Point path[100];
        int path_len = 0;
        int ex = (int)sp->x / TILE_SIZE;
        int ey = (int)sp->y / TILE_SIZE;
        int px = (int)data->player.px / TILE_SIZE;
        int py = (int)data->player.py / TILE_SIZE;

        if (bfs(data, (Point){ex, ey}, (Point){px, py}, path, &path_len, sp)) {
            Point next = path[path_len - 1];
            float target_x = next.x * TILE_SIZE + TILE_SIZE / 2;
            float target_y = next.y * TILE_SIZE + TILE_SIZE / 2;

            float dx = target_x - sp->x;
            float dy = target_y - sp->y;
            float distance = sqrt(dx*dx + dy*dy);

            float speed = 0.3f;
            if (distance > 1.0f) {
                sp->x += speed * (dx / distance);
                sp->y += speed * (dy / distance);
            }
        }
    }

    // Ensure enemy stays 5 pixels away from walls
    clamp_position_to_walls(data, sp);

    // Resolve collisions with other enemies
    resolve_enemy_collisions(data, sp);

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

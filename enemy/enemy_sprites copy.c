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
        float speed = 0.05f;
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

            float speed = 0.05f;
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

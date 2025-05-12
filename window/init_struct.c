#include "../cub3d.h"

void init_player(t_var *data)
{
    player_start(data, data->map.ypos, data->map.xpos);
    data->player.pa = P2;
    data->player.pdy = sinf(data->player.pa);
    data->player.pdx = cosf(data->player.pa);
}
void init_sprites(t_var *data) {
    int empty_spaces = 0;

    for (int y = 0; y < data->map.height; y++) {
        for (int x = 0; x < data->map.width; x++) {
            if (data->map.arr[y][x] == '0')
                empty_spaces++;
        }
    }

    int num_enemies = empty_spaces / 30;
    data->num_sprites = num_enemies;
    data->sprites = malloc(sizeof(t_sprite) * data->num_sprites);

    srand(time(NULL));

    int count = 0;
    int max_attempts = 1000;
    int attempts = 0;

    int player_tile_x = (int)(data->player.px / 32);
    int player_tile_y = (int)(data->player.py / 32);

    // Check if player is on a valid tile
    if (player_tile_x < 0 || player_tile_x >= data->map.width || 
        player_tile_y < 0 || player_tile_y >= data->map.height ||
        data->map.arr[player_tile_y][player_tile_x] != '0') {
        fprintf(stderr, "Invalid player starting position\n");
        data->num_sprites = 0;
        free(data->sprites);
        return;
    }

    // BFS to find reachable areas
    bool **reachable = malloc(sizeof(bool*) * data->map.height);
    for (int y = 0; y < data->map.height; y++) {
        reachable[y] = calloc(data->map.width, sizeof(bool));
    }

    int dirs[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    int queue_x[data->map.width * data->map.height];
    int queue_y[data->map.width * data->map.height];
    int front = 0, rear = 0;

    reachable[player_tile_y][player_tile_x] = true;
    queue_x[rear] = player_tile_x;
    queue_y[rear++] = player_tile_y;

    while (front < rear) {
        int x = queue_x[front];
        int y = queue_y[front++];

        for (int i = 0; i < 4; i++) {
            int nx = x + dirs[i][0];
            int ny = y + dirs[i][1];

            if (nx >= 0 && nx < data->map.width && ny >= 0 && ny < data->map.height) {
                if (data->map.arr[ny][nx] == '0' && !reachable[ny][nx]) {
                    reachable[ny][nx] = true;
                    queue_x[rear] = nx;
                    queue_y[rear++] = ny;
                }
            }
        }
    }

    // Place enemies in reachable areas
    while (count < num_enemies && attempts++ < max_attempts) {
        int rx = rand() % data->map.width;
        int ry = rand() % data->map.height;

        if (reachable[ry][rx] && 
            !(rx == player_tile_x && ry == player_tile_y) &&
            abs(rx - player_tile_x) >= 2 && 
            abs(ry - player_tile_y) >= 2) {
            
            data->sprites[count++] = (t_sprite){
                .type = 2,
                .x = rx * 32 + 16,
                .y = ry * 32 + 16,
                .z = 0
            };
        }
    }

    data->num_sprites = count;

    // Cleanup BFS memory
    for (int y = 0; y < data->map.height; y++) {
        free(reachable[y]);
    }
    free(reachable);

    // Debug print
    for (int i = 0; i < data->num_sprites; i++) {
        printf("Enemy %d: x = %f, y = %f\n", i, data->sprites[i].x, data->sprites[i].y);
    }
}

void load_single_gif_frame(t_var *data, t_img *img, const char *path) {
    img->img = mlx_xpm_file_to_image(data->mlx, (char *)path, &img->width, &img->height);
    if (!img->img) {
        fprintf(stderr, "Failed to load image: %s\n", path);
        exit(1);
    }
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
}

void load_enemy_gifs(t_var *data) {
    load_single_gif_frame(data, &data->gif.zero,  "textures/hangy-0.xpm");
    load_single_gif_frame(data, &data->gif.one,   "textures/hangy-1.xpm");
    load_single_gif_frame(data, &data->gif.two,   "textures/hangy-2.xpm");
    load_single_gif_frame(data, &data->gif.three, "textures/hangy-3.xpm");
    load_single_gif_frame(data, &data->gif.four,  "textures/hangy-4.xpm");
    load_single_gif_frame(data, &data->gif.five,  "textures/hangy-5.xpm");
    load_single_gif_frame(data, &data->gif.six,   "textures/hangy-6.xpm");
    load_single_gif_frame(data, &data->gif.seven, "textures/hangy-7.xpm");
    load_single_gif_frame(data, &data->gif.eight, "textures/hangy-8.xpm");
}


bool can_reach_playable_area(t_var *data, Point start) {
    Point queue[data->map.height * data->map.width];
    bool visited[data->map.height][data->map.width];
    bool has_playable = false;

    for (int i = 0; i < data->map.height; ++i) {
        for (int j = 0; j < data->map.width; ++j) {
            visited[i][j] = false;
        }
    }

    int front = 0, back = 0;
    queue[back++] = start;
    visited[start.y][start.x] = true;

    Point directions[] = {{1,0}, {-1,0}, {0,1}, {0,-1}};

    int step_count = 0;

    while (front < back) {
        Point current = queue[front++];

        step_count++;

        if (step_count > data->map.width * data->map.height) {
            break;
        }

        if (data->map.arr[current.y][current.x] == '0') {
            has_playable = true;
        }

        for (int i = 0; i < 4; ++i) {
            int nx = current.x + directions[i].x;
            int ny = current.y + directions[i].y;

            if (nx >= 0 && nx < data->map.width && ny >= 0 && ny < data->map.height &&
                !visited[ny][nx] && (data->map.arr[ny][nx] == '0' || data->map.arr[ny][nx] == '8')) {
                
                queue[back++] = (Point){nx, ny};
                visited[ny][nx] = true;
            }
        }
    }

    return has_playable;
}

void place_winning_tiles(t_var *data) {
    srand(time(NULL));
    int w = data->map.width;
    int h = data->map.height;

    int px = (int)(data->player.px / TILE_SIZE);
    int py = (int)(data->player.py / TILE_SIZE);

    if (can_reach_playable_area(data, (Point){px, py})) {
        Point *reachable_zeros = malloc(w * h * sizeof(Point));
        int count = 0;

        bool visited[h][w];
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                visited[i][j] = false;
            }
        }

        Point queue[w * h];
        int front = 0, back = 0;
        queue[back++] = (Point){px, py};
        visited[py][px] = true;

        Point directions[] = {{1,0}, {-1,0}, {0,1}, {0,-1}};

        while (front < back) {
            Point current = queue[front++];

            if (data->map.arr[current.y][current.x] == '0') {
                reachable_zeros[count++] = current;
            }

            for (int i = 0; i < 4; ++i) {
                int nx = current.x + directions[i].x;
                int ny = current.y + directions[i].y;

                if (nx >= 0 && nx < w && ny >= 0 && ny < h &&
                    !visited[ny][nx] && (data->map.arr[ny][nx] == '0' || data->map.arr[ny][nx] == '8')) {

                    visited[ny][nx] = true;
                    queue[back++] = (Point){nx, ny};
                }
            }
        }

        if (count > 0) {
            int index = rand() % count;
            Point selected = reachable_zeros[index];
            data->map.arr[selected.y][selected.x] = '8';
        } else {
            printf("No reachable '0' tiles to place the winning tile.\n");
        }

        free(reachable_zeros);
    } else {
        printf("No reachable area to place the winning tile.\n");
    }
}

void init_all(t_var *data, t_cub *cube)
{
    data->mlx = mlx_init();
    if (!data->mlx)
        return;
    data->win = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
    if (!data->win)
        return;
    load_enemy_gifs(data); 
    data->map = cube->map;
    data->move = (t_move) {0};
    data->minimap = (t_minimap) {0};
    init_player(data);
    init_sprites(data);
    data->last_mouse_x = -1;
    place_winning_tiles(data);
}






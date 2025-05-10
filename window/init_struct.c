#include "../cub3d.h"

void init_player(t_var *data)
{
    player_start(data, data->map.ypos, data->map.xpos);
    data->player.pa = P2;
    data->player.pdy = sinf(data->player.pa);
    data->player.pdx = cosf(data->player.pa);
}


void init_sprites(t_var *data)
{
    int empty_spaces = 0;

    for (int y = 0; y < data->map.height; y++)
    {
        for (int x = 0; x < data->map.width; x++)
        {
            if (data->map.arr[y][x] == '0')
                empty_spaces++;
        }
    }

    int num_enemies = empty_spaces / 30;
    printf("num ene %d %d\n", num_enemies, empty_spaces );
    data->num_sprites = num_enemies;
    data->sprites = malloc(sizeof(t_sprite) * data->num_sprites);

    srand(time(NULL));

    int count = 0;
    int max_attempts = 1000;
    int attempts = 0;

    int player_tile_x = (int)(data->player.px / 32);
    int player_tile_y = (int)(data->player.py / 32);

    while (count < num_enemies && attempts < max_attempts)
    {
        int rx = rand() % data->map.width;
        int ry = rand() % data->map.height;
        attempts++;

        if (data->map.arr[ry][rx] != '0')
            continue;
        // Must not be same x AND same y as player
        if (rx == player_tile_x && ry == player_tile_y)
            continue;

        // Enforce at least 2 tiles distance in both directions
        if (abs(rx - player_tile_x) < 2 || abs(ry - player_tile_y) < 2)
            continue;

        data->sprites[count++] = (t_sprite){
            .type = 2,
            .x = rx * 32 + 16,
            .y = ry * 32 + 16,
            .z = 0
        };
    }

    data->num_sprites = count;

    for (int i = 0; i < data->num_sprites; i++)
    {
        printf("Enemy %d: x = %f, y = %f, z = %f\n",
               i, data->sprites[i].x, data->sprites[i].y, data->sprites[i].z);
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
}






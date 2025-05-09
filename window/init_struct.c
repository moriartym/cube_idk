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
    data->num_sprites = 7;
    data->sprites = malloc(sizeof(t_sprite) * data->num_sprites);
    *data->sprites = (t_sprite){0};
    data->sprites[0] = (t_sprite){.type = 1, .x =  48.0, .y = 48.0, .z = 0};// z not used
    data->sprites[1] = (t_sprite){.type = 1, .x =  48.0, .y = 80.0, .z = 0};// z not used
    data->sprites[2] = (t_sprite){.type = 1, .x =  48.0, .y = 112.0, .z = 0};// z not used
    data->sprites[3] = (t_sprite){.type = 1, .x =  48.0, .y = 144.0, .z = 0};// z not used
    data->sprites[4] = (t_sprite){.type = 1, .x =  48.0, .y = 176.0, .z = 0};// z not used
    data->sprites[5] = (t_sprite){.type = 1, .x =  48.0, .y = 208.0, .z = 0};// z not used
    data->sprites[6] = (t_sprite){.type = 1, .x =  48.0, .y = 240.0, .z = 0};// z not used
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






#include "../cub3d.h"

void load_single_gif_frame(t_var *data, t_img *img, const char *path)
{
    img->img = mlx_xpm_file_to_image(data->mlx, (char *)path, &img->width, &img->height);
    if (!img->img)
    {
        fprintf(stderr, "Failed to load image: %s\n", path);
        exit(1);
    }
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
}

void load_enemy_gifs(t_var *data)
{
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

void place_enemy(t_var *data, t_bfs *bfs)
{
    int count;
    int attempts;
    int rx;
    int ry;

    count = 0;
    attempts = 0;
    while (count < data->num_sprites && attempts++ < bfs->empty_spaces)
    {
        rx = rand() % data->map.width;
        ry = rand() % data->map.height;
        if (bfs->reachable[ry][rx] && 
            !(rx == bfs->ipx && ry == bfs->ipy) &&
            abs(rx - bfs->ipx) >= 5 && 
            abs(ry - bfs->ipy) >= 5)
        {
            data->sprites[count].type = 2;
            data->sprites[count].x = rx * 32 + 16;
            data->sprites[count].y = ry * 32 + 16;
            data->sprites[count].z = 0;
            count++;
        }
    }
    data->num_sprites = count;
}

void init_sprites(t_var *data)
{
    t_bfs bfs;
    int y;

    bfs = (t_bfs){0};
    srand(time(NULL));
    do_bfs(data, &bfs);
    data->num_sprites = bfs.empty_spaces / 30;
    data->sprites = malloc(sizeof(t_sprite) * data->num_sprites);
    place_enemy(data, &bfs);
    y = 0; 
    while (y < data->map.height)
    {
        free(bfs.reachable[y]);
        y++;
    }
    free(bfs.reachable);
    // debug
    for (int i = 0; i < data->num_sprites; i++) {
        printf("Enemy %d: x = %f, y = %f\n", i, data->sprites[i].x, data->sprites[i].y);
    }
}

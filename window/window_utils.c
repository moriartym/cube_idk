#include "../cub3d.h"

void create_image_buffer(t_var *data)
{
    data->image.img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    data->image.addr = mlx_get_data_addr(data->image.img,
            &data->image.bits_per_pixel,
            &data->image.line_length,
            &data->image.endian);
}

void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char *dst;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}
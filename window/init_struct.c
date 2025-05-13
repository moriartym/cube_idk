#include "../cub3d.h"

void init_player(t_var *data)
{
    player_start(data, data->map.ypos, data->map.xpos);
    data->player.pa = P2;
    data->player.pdy = sinf(data->player.pa);
    data->player.pdx = cosf(data->player.pa);
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






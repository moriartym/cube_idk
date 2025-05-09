#include "../cub3d.h"

void movement_init(t_var *data, t_movestat *movestat)
{
    movestat->delta_time = get_delta_time(data);
    if (data->move.move_al)
        data->player.pa -= ROTATION_SPEED * movestat->delta_time;
    if (data->move.move_ar)
        data->player.pa += ROTATION_SPEED * movestat->delta_time;
    data->player.pa = normalize_radians(data->player.pa);
    data->player.pdy = sinf(data->player.pa) * MOVEMENT_SPEED * movestat->delta_time;
    data->player.pdx = cosf(data->player.pa) * MOVEMENT_SPEED * movestat->delta_time;
    if (data->player.pdx < 0)
        movestat->xo = -10;
    else
        movestat->xo = 10;
    if (data->player.pdy < 0)
        movestat->yo = -10;
    else
        movestat->yo = 10;
    movestat->ipx = data->player.px / TILE_SIZE;
    movestat->ipx_add_xo = (data->player.px + movestat->xo) / TILE_SIZE;
    movestat->ipx_sub_xo = (data->player.px - movestat->xo) / TILE_SIZE;
    movestat->ipy = data->player.py / TILE_SIZE;
    movestat->ipy_add_yo = (data->player.py + movestat->yo) / TILE_SIZE;
    movestat->ipy_sub_yo = (data->player.py - movestat->yo) / TILE_SIZE;
}

void movement_ws(t_var *data, t_movestat *movestat)
{
    if (data->move.move_w)
    {
        if (data->map.arr[movestat->ipy][movestat->ipx_add_xo] == '0' || data->map.arr[movestat->ipy][movestat->ipx_add_xo] == '3')
            data->player.px += data->player.pdx;
        if (data->map.arr[movestat->ipy_add_yo][movestat->ipx] == '0' || data->map.arr[movestat->ipy_add_yo][movestat->ipx] == '3')
            data->player.py += data->player.pdy;       
    }
    if (data->move.move_s)
    {
        if (data->map.arr[movestat->ipy][movestat->ipx_sub_xo] == '0' || data->map.arr[movestat->ipy][movestat->ipx_sub_xo] == '3')
            data->player.px -= data->player.pdx;
        if (data->map.arr[movestat->ipy_sub_yo][movestat->ipx] == '0' || data->map.arr[movestat->ipy_sub_yo][movestat->ipx] == '3')
            data->player.py -= data->player.pdy;    
    }
}

void movement_da(t_var *data, t_movestat *movestat)
{
    int strafe_ipx;
    int strafe_ipy;

    if (data->move.move_d)
    {   
        strafe_ipx = (data->player.px - movestat->yo) / TILE_SIZE;
        strafe_ipy = (data->player.py + movestat->xo) / TILE_SIZE;
        if (data->map.arr[movestat->ipy][strafe_ipx] == '0' || data->map.arr[movestat->ipy][strafe_ipx] == '3')
            data->player.px -= data->player.pdy;
        if (data->map.arr[strafe_ipy][movestat->ipx] == '0' || data->map.arr[strafe_ipy][movestat->ipx] == '3')
            data->player.py += data->player.pdx;
    }
    if (data->move.move_a)
    {
        strafe_ipx = (data->player.px + movestat->yo) / TILE_SIZE;
        strafe_ipy = (data->player.py - movestat->xo) / TILE_SIZE;
        if (data->map.arr[movestat->ipy][strafe_ipx] == '0' || data->map.arr[movestat->ipy][strafe_ipx] == '3')
            data->player.px += data->player.pdy;
        if (data->map.arr[strafe_ipy][movestat->ipx] == '0' || data->map.arr[strafe_ipy][movestat->ipx] == '3')
            data->player.py -= data->player.pdx;
    }
}

void update_movement(t_var *data)
{
    t_movestat movestat;

    movestat = (t_movestat){0};
    movement_init(data, &movestat);
    movement_ws(data, &movestat);
    movement_da(data, &movestat);
}
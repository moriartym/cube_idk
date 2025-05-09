#include "../cub3d.h"

double get_delta_time(t_var *data)
{
    struct timeval current_time;
    double delta_time;

    gettimeofday(&current_time, NULL);
    delta_time = (current_time.tv_sec - data->last_time.tv_sec) +
                 (current_time.tv_usec - data->last_time.tv_usec) / 1000000.0;
    data->last_time = current_time;
    if (delta_time > MAX_DELTA_TIME)
        delta_time = MAX_DELTA_TIME;
    return delta_time;
}

float normalize_radians(float angle)
{
    while (angle < 0)
        angle += 2 * PI;
    while (angle >= 2 * PI)
        angle -= 2 * PI;
    return angle;
}

int handle_keypress(int keysym, t_var *data)
{
    if (keysym == XK_Escape)
        close_window(data);
    else if (keysym == XK_a)
        data->move.move_a = 1;
    else if (keysym == XK_d)
        data->move.move_d = 1;
    else if (keysym == XK_w)
        data->move.move_w = 1;
    else if (keysym == XK_s)
        data->move.move_s = 1;
    else if (keysym == XK_Left)
        data->move.move_al = 1;
    else if (keysym == XK_Right)
        data->move.move_ar = 1;
    else if (keysym == XK_m)
        mouse_state(data);
    else if (keysym == XK_c)
        create_door(data);
    else if (keysym == XK_o)
        open_door(data);
    return 0;
}

int handle_keyrelease(int keysym, t_var *data)
{
    if (keysym == XK_a)
        data->move.move_a = 0;
    else if (keysym == XK_d)
        data->move.move_d = 0;
    else if (keysym == XK_w)
        data->move.move_w = 0;
    else if (keysym == XK_s)
        data->move.move_s = 0;
    else if (keysym == XK_Left)
        data->move.move_al = 0;
    else if (keysym == XK_Right)
        data->move.move_ar = 0;
    return 0;
}

int handle_mouse_move(int x, int y, t_var *data)
{
    int delta_x;

    if (data->mouse_state)
    {    
        if (data->last_mouse_x == -1)
        {
            data->last_mouse_x = x;
            return 0;
        }
        delta_x = x - data->last_mouse_x;
        data->last_mouse_x = x;
        data->player.pa += delta_x * MOUSE_SENSITIVITY;
        data->player.pa = normalize_radians(data->player.pa);
    }
    return 0;
}

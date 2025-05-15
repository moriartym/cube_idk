#include "../cub3d.h"

int enemy_left(t_var *data, t_sprite *sp)
{
    if ((sp->is_unstucking || sp->x > data->player.px))
    {
        if (is_cell_valid(data, sp->spx_left, sp->spy))
        {
            if (!is_cell_valid(data, sp->spx_left, sp->spy_up) && is_cell_valid(data, sp->spx, sp->spy))
            {
                sp->y += sp->lil_margin;
                return (0);
            }
            if (!is_cell_valid(data, sp->spx_left, sp->spy_down) && is_cell_valid(data, sp->spx, sp->spy))
            {
                sp->y -= sp->lil_margin;
                return (0);
            }
            sp->x -= sp->speed;
            return (0);
        }
        sp->is_unstucking = 1;
    } 
    return (1);
}

int enemy_right(t_var *data, t_sprite *sp)
{
    if ((sp->is_unstucking || sp->x < data->player.px))
    {
        if (is_cell_valid(data, sp->spx_right, sp->spy))
        {
            if (!is_cell_valid(data, sp->spx_right, sp->spy_up) && is_cell_valid(data, sp->spx, sp->spy))
            {
                sp->y += sp->lil_margin;
                return (0);
            }
            if (!is_cell_valid(data, sp->spx_right, sp->spy_down) && is_cell_valid(data, sp->spx, sp->spy))
            {
                sp->y -= sp->lil_margin;
                return (0);
            }
            sp->x += sp->speed;
            return (0);
        }
        sp->is_unstucking = 1;
    }
    return (1);
}

int enemy_up(t_var *data, t_sprite *sp)
{
    if ((sp->is_unstucking || sp->y > data->player.py))
    {
        if (is_cell_valid(data, sp->spx, sp->spy_up))
        {
            if (!is_cell_valid(data, sp->spx_left, sp->spy_up) && is_cell_valid(data, sp->spx, sp->spy))
            {
                sp->x += sp->lil_margin;
                return (0);
            }
            if (!is_cell_valid(data, sp->spx_right, sp->spy_up) && is_cell_valid(data, sp->spx, sp->spy))
            {
                sp->x -= sp->lil_margin;
                return (0);
            }
            sp->y -= sp->speed;
            return (0);
        }
        sp->is_unstucking = 1;
    }
    return (1);
}

int enemy_down(t_var *data, t_sprite *sp)
{
    if ((sp->is_unstucking || sp->y < data->player.py))
    {
        if (is_cell_valid(data, sp->spx, sp->spy_down))
        {
            if (!is_cell_valid(data, sp->spx_left, sp->spy_down) && is_cell_valid(data, sp->spx, sp->spy))
            {
                sp->x += sp->lil_margin;
                return (0);
            }
            if (!is_cell_valid(data, sp->spx_right, sp->spy_down) && is_cell_valid(data, sp->spx, sp->spy))
            {
                sp->x -= sp->lil_margin;
                return (0);
            }
            sp->y += sp->speed;
            return (0);
        }
        sp->is_unstucking = 1;
    }
    return (1);
}

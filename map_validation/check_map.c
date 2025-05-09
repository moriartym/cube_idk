#include "../cub3d.h"

void	validate_map_char(t_map *map)
{
	int	i;
	int	j;
	int	player;

	i = 0;
	player = 0;
	while (map->arr[i])
	{
		j = 0;
		while (map->arr[i][j])
		{
			if (!(ft_strchr(" 01NSEW\n", map->arr[i][j])))
				handle_error("The map must be composed \
					of only 0, 1, N, S, E, W");
			if (ft_strchr("NSEW", map->arr[i][j]))
			{
				map->xpos = j;
				map->ypos = i;
				player++;
			}
			j++;
		}
		i++;
	}
	if (player == 0)
		handle_error("There is no player's start position");
	if (player > 1)
		handle_error("There is mutiple player's start position");
}

void	check_surrounding(t_map *map, int y, int x)
{
	char	left;
	char	right;
	char	up;
	char	down;

	if (x == 0 || x == map->max_length - 1
		|| y == 0 || y == map->height - 1)
		handle_error("The map must be surrounded by walls");
	left = map->arr[y - 1][x];
	right = map->arr[y + 1][x];
	up = map->arr[y][x - 1];
	down = map->arr[y][x + 1];
	if (left == 'X' || right == 'X' || up == 'X' || down == 'X')
		handle_error("The map must be surrounded by walls");
}

void	change_player(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (map->arr[y])
	{
		x = 0;
		while (map->arr[y][x])
		{
			if (ft_strchr("NSEW", map->arr[y][x]))
				map->arr[y][x] = '0';
			x++;
		}
		y++;
	}
}

void	check_wall(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (map->arr[y])
	{
		x = 0;
		while (map->arr[y][x])
		{
			if (map->arr[y][x] == '0')
				check_surrounding(map, y, x);
			x++;
		}
		y++;
	}
}

int	check_map(t_map *map)
{
	validate_map_char(map);
	find_max_row_length(map);
	replace_space(map);
	check_wall(map);
	change_player(map);
	return (0);
}

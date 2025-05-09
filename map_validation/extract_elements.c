#include "../cub3d.h"

int	extract_elements(t_map *map, int fd)
{
	char	*line;
	char	**arr;
	int		i;
	
	i = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		arr = ft_split(line, ' ');
		if (!arr)
			return (free(line), ft_error_return("malloc failed"));
		if (verify_id(map, arr, i) == 1)
			return (ft_free_2d(&arr), free(line), 1);
		ft_free_2d(&arr);
		free(line);
		if (map->elements_set == 6)
			break ;
		i++;
	}
	map->content_start = i;
	return (0);
}

int	verify_id(t_map *map, char **arr, int line)
{
	t_id	*id;

	if (ft_arrlen(arr) == 1 && ft_strcmp(arr[0], "\n") == 0)
		return (0);
	else if (ft_arrlen(arr) != 2)
		return (element_err(line), 1);
	else if (ft_strcmp(arr[0], "NO") == 0 && !map->north.filename)
		id = set_id(&map->north, NORTH);
	else if (ft_strcmp(arr[0], "EA") == 0 && !map->east.filename)
		id = set_id(&map->east, EAST);
	else if (ft_strcmp(arr[0], "SO") == 0 && !map->south.filename)
		id = set_id(&map->south, SOUTH);
	else if (ft_strcmp(arr[0], "WE") == 0 && !map->west.filename)
		id = set_id(&map->west, WEST);
	else if (ft_strcmp(arr[0], "F") == 0 && !map->floor.filename && verify_rgb(arr[1]) == 0)
		id = set_id(&map->floor, FLOOR);
	else if (ft_strcmp(arr[0], "C") == 0 && !map->ceiling.filename && verify_rgb(arr[1]) == 0)
		id = set_id(&map->ceiling, CEILING);
	else
		return (element_err(line), 1);
	id->filename = ft_strdup(arr[1]);
	if (!id->filename)
		return (ft_error_return("malloc failed"), 1);
	map->elements_set++;
	return (0);
}

int	verify_rgb(char *value)
{
	char	**arr;
	int		i;

	arr = ft_split(value, ',');
	if (!arr)
		return (ft_error_return("malloc failed"));
	if (ft_arrlen(arr) != 3)
		return (ft_free_2d(&arr), 1);
	i = 0;
	while (i < 3)
	{
		if (!ft_range(ft_atoi(arr[i]), 0, 255))
			return (ft_free_2d(&arr), 1);
		i++;
	}
	return (0);
}

t_id	*set_id(t_id *id, direction value)
{
	id->direction = value;
	return (id);
}

#include "../cub3d.h"

int	extract_map(t_map *map)
{
	int	fd;

	if (check_map_name(map->name) == 1)
		return (1);
	fd = open(map->name, O_RDONLY);
	if (fd == -1)
		return (ft_error_return(map->name));
	if (extract_elements(map, fd) == 1)
		return (1);
	if (extract_content(map, fd) == 1)
		return (1);
	// printf("map height: %d\n", map->height);
	// int i = 0;
	// while (map->arr[i])
	// {
	// 	printf("height %d: %s\n", i, map->arr[i]);
	// 	i++;
	// }
	if (check_map(map) == 1)
		return (1);

	map->width = map->max_length - 1;
	return (0);
}

int	check_map_name(char *file)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	i -= 4;
	if (ft_strncmp(file + i, ".cub", 4) != 0)
	{
		ft_putstr_fd("File must be in .cub\n", 2);
		return(1);
	}
	return (0);
}

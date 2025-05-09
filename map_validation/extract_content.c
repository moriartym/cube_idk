#include "../cub3d.h"

int	extract_content(t_map *map, int fd)
{
	get_map_height(map, fd);
	close(fd);
	return (fill_map_arr(map));
}

void	get_map_height(t_map *map, int fd)
{
	char	*line;
	int		space;

	space = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] == '\n' && space == 1)
		{
			free(line);
			map->content_start++;
			continue ;
		}
		free(line);
		map->height++;
		space = 0;
	}
}

int	fill_map_arr(t_map *map)
{
	char	**buff;
	char	*str;
	int		fd;
	int		i;

	fd = open(map->name, O_RDONLY);
	if (fd == -1)
		return (ft_error_return(map->name));
	buff = malloc ((map->height + 1) * sizeof(char *));
	if (!buff)
		return (close(fd), ft_error_return("malloc failed"));
	skip_to_content(map, fd);
	i = 0;
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break;
		buff[i] = str;
		i++;
	}
	buff[i] = NULL;
	map->arr = buff;
	close(fd);
	return (0);
}

void	skip_to_content(t_map *map, int fd)
{
	char	*line;
	int		i;

	i = 0;
	while (i < map->content_start)
	{
		line = get_next_line(fd);
		free(line);
		i++;
	}
	return ;
}

#include "../cub3d.h"

void	handle_error(char *err)
{
	if (!err)
		return ;
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(err, 2);
	ft_putstr_fd("\n", 2);
	exit (1);
}

int	element_err(int line)
{
	char	*str;

	str = ft_itoa(line);
	if (!line)
		return (ft_error_return("malloc failed"));
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd("Invalid configuration of map elements in line ", 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
	free(str);
	return (0);
}

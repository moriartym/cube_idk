#include "cub3d.h"

int main(int argc, char **argv)
{
	t_cub	cub;

	cub = (t_cub){0};
	if (argc != 2)
		return (ft_putstr_fd("./cub3d map.cub\n", 1), 1);
	cub.map = (t_map){0};
	cub.map.name = argv[1];
	// cub.map.name = "map/valid.cub";
	cub.map.name = "map/valid.cub";
	if (extract_map(&cub.map) == 1)
		return (1);
	if (create_visual(&cub))
		return (1);
}
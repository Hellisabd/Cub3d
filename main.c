#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_map	map;

	if (argc == 1)
		return (printf("Error\nPlease load a .cub file!\n"), 1);
	if (argc == 2)
	{
		open_map(&map, argv);
		parsing_map(&map);
		free_and_destroy(&map);
	}
	if (argc > 2)
		return (printf("Error\nToo many arguments!\n"), 1);
}

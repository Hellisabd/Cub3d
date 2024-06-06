#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_map	map;

	if (argc == 1)
		return (printf("Error\nPlease load a .cub file!\n"), 1);
	if (argc == 2)
	{
		open_map(&map, argv);
		if (-1 == parsing_map(&map))
			printf("open map\n");
		debug_nbr(RED, "bonjour Antoine", 9);
		debug_str(BLUE, "Comment tu vas", "de bon matin");
		free_and_destroy(&map);
	}
	if (argc > 2)
		return (printf("Error\nToo many arguments!\n"), 1);
}

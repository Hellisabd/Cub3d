#include "cub3D.h"

void	init_var(t_map *map)
{
	map->length = NULL;	
	map->no =NULL;
	map->so =NULL;
	map->we =NULL;
	map->ea =NULL;
	map->c =NULL;
	map->f =NULL;
}

int	main(int argc, char **argv)
{
	t_map	map;

	if (argc == 1)
		return (printf("Error\nPlease load a .cub file!\n"), 1);
	if (argc == 2)
	{
		init_var(&map);
		open_map(&map, argv);
		if (-1 == parsing_map(&map))
			printf("open map\n");
		free_and_destroy(&map);
	}
	if (argc > 2)
		return (printf("Error\nToo many arguments!\n"), 1);
}

#include "cub3D.h"

void	init_var(t_map *map)
{
	map->length = NULL;
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->c = NULL;
	map->f = NULL;
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	cub.map = malloc(sizeof(t_map));
	if (argc == 1)
		return (printf("Error\nPlease load a .cub file!\n"), 1);
	if (argc > 2)
		return (printf("Error\nToo many arguments!\n"), 1);
	if (argc == 2)
	{
		init_var(cub.map);
		open_map(cub.map, argv);
		if (-1 == parsing_map(cub.map))
			printf("open map\n");
		open_window(&cub);
		free_and_destroy(cub.map);
	}
}

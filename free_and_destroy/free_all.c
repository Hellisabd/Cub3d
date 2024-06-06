#include "../cub3D.h"

void	free_and_destroy(t_map *map)
{
	free(map->no);
	free(map->so);
	free(map->we);
	free(map->ea);
	free(map->f);
	free(map->c);
	ft_free_tab(map->map);
}

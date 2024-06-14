#include "../cub3D.h"

void	free_map_stuff(t_map *map)
{
	if (map->no)
		free(map->no);
	if (map->so)
		free(map->so);
	if (map->we)
		free(map->we);
	if (map->ea)
		free(map->ea);
	if (map->f)
		free(map->f);
	if (map->c)
		free(map->c);
	if (map->length)
		free(map->length);
	if (map->map)
		ft_free_tab(map->map);
	free(map);
}

void	free_rays(t_ray **ray)
{
	t_ray	*tmp;

	while (ray && *ray)
	{
		tmp = *ray;
		*ray = (*ray)->next;
		free(tmp);
	}
	free(ray);
	ray = NULL;
}

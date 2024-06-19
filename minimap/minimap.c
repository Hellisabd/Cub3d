#include "../cub3D.h"

size_t ft_strlen_custom(char *str)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] >= 13 || str[i] <= 9 || str[i] != ' ')
			count = i;
		i++;
	}
	return (count);
}

int init_data_mini_map(t_mini_map *minimap, t_map *map)
{
	size_t max_length;
	int	i;

	i = 0;
	max_length = 0;
	while (map->map[i])
	{
		if (max_length < ft_strlen_custom(map->map[i]))
			max_length = ft_strlen_custom(map->map[i]);
		i++;
	}
	minimap->size_wall_x = ceil(WIDTH / (float)(max_length));
	minimap->size_wall_y = ceil(HEIGHT / (float)(i));
	minimap->width = minimap->size_wall_x * max_length;
	minimap->height = minimap->size_wall_y * i;
	return (0);
}

int	put_wall(t_map *map, t_cub *g, t_player *player)
{
	int pos_x = 0;
	int pos_y = 0;
	int i = -1;
	int j;
	while (map->map[++i])
	{
		pos_x = 0;
		j = 0;
		while (map->map[i][j] && map->map[i][j] != '\n')
		{
			if (map->map[i][j] == '1')
			{
				mlx_image_to_window(g->mlx, g->mini_map.wall_i, pos_x, pos_y);
				// mlx_set_instance_depth(g->mini_map.wall_i->instances, 76666);
			}
			if (map->map[i][j] == g->map->player_char)
			{
				player->pos_x = pos_x;
				player->pos_y = pos_y;
				mlx_image_to_window(g->mlx, g->mini_map.player_i, pos_x, pos_y);
				// mlx_set_instance_depth(g->mini_map.player_i->instances, 76666);
			}
			pos_x += g->mini_map.size_wall_x;
			j++;
		}
		pos_y += g->mini_map.size_wall_y;
	}
	return (0);
}

int map_to_window(t_cub *cub)
{
	init_mini_map(cub, &cub->mini_map);
	if (-1 == mlx_image_to_window(cub->mlx, cub->mini_map.background_i, 0, 0))
		exit(1);
	put_wall(cub->map, cub, &cub->player);
	if (cub->map->player_char == 'N')
		cub->rot = PI;
	if (cub->map->player_char == 'S')
		cub->rot = 0;
	if (cub->map->player_char == 'E')
		cub->rot = PI / 2;
	if (cub->map->player_char == 'W')
		cub->rot = -PI / 2;
	return (0);
}

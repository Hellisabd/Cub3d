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
	minimap->size_wall_x = ceil(WIDTH / (float)(max_length)) / 5;
	minimap->size_wall_y = ceil(HEIGHT / (float)(i)) / 5;
	minimap->width = minimap->size_wall_x * max_length;
	minimap->height = minimap->size_wall_y * i;
	return (0);
}

int	put_wall(t_map *map, t_cub *g)
{
	int pos_x = 0;
	int pos_y = 0;
	int i = -1;
	static int round = 0;
	int j;
	while (map->map[++i])
	{
		pos_x = 0;
		j = 0;
		while (map->map[i][j] && map->map[i][j] != '\n')
		{
			if (map->map[i][j] == 'd' && g->anim.door_opening == END)
				map->map[i][j] = 'o';
			else if (map->map[i][j] == 'd' && g->anim.door_closing == END)
				map->map[i][j] = 'D';
			if (map->map[i][j] == 'D')
				mlx_image_to_window(g->mlx, g->mini_map.door_i, pos_x, pos_y);
			if (map->map[i][j] == '1')
				mlx_image_to_window(g->mlx, g->mini_map.wall_i, pos_x, pos_y);
			// if (round == 0 &&  map->map[i][j] == g->map->player_char)
			// {
			// 	map->map[i][j] = '0';
			// 	mlx_image_to_window(g->mlx, g->mini_map.player_i, pos_x, pos_y);
			// } 
			pos_x += g->mini_map.size_wall_x;
			j++;
		}
		pos_y += g->mini_map.size_wall_y;
	}
	// if (round != 0)
	// 	mlx_image_to_window(g->mlx, g->mini_map.player_i, g->player.pos_x, g->player.pos_y);
	round++;
	return (0);
}

int map_to_window(t_cub *cub, bool actualise)
{
	if (actualise == false)
		init_mini_map(cub, &cub->mini_map);
	else
	{
		 cub->mini_map.background_i = mlx_texture_to_image(cub->mlx, cub->mini_map.background_t);
			mlx_resize_image(cub->mini_map.background_i, cub->mini_map.width, cub->mini_map.height);
	}
	if (-1 == mlx_image_to_window(cub->mlx, cub->mini_map.background_i, 0, 0))
		exit(1);
	put_wall(cub->map, cub);
	return (0);
}

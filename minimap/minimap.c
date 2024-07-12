/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:46:08 by amirloup          #+#    #+#             */
/*   Updated: 2024/07/12 11:53:48 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

size_t	ft_strlen_custom(char *str)
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

int	init_data_mini_map(t_mini_map *minimap, t_map *map)
{
	int	i;

	i = 0;
	map->max_length = 0;
	while (map->map[i])
	{
		if ((size_t)map->max_length < ft_strlen_custom(map->map[i]))
			map->max_length = ft_strlen_custom(map->map[i]);
		i++;
	}
	minimap->size_wall_x = ceil(HEIGHT / (float)(map->max_length)) / 5;
	minimap->size_wall_y = ceil(HEIGHT / (float)(i)) / 5;
	minimap->width = minimap->size_wall_x * map->max_length;
	minimap->height = minimap->size_wall_y * i;
	return (0);
}

void	put_wall_2(t_map *map, t_cub *g)
{
	if (map->map[map->i][map->j] == 'd' && g->anim.door_opening == END)
		map->map[map->i][map->j] = 'o';
	else if (map->map[map->i][map->j] == 'd' && \
		g->anim.door_closing == END)
		map->map[map->i][map->j] = 'D';
	if (map->map[map->i][map->j] == 'D')
		if (mlx_image_to_window(g->mlx, g->mini_map.door_i, \
			map->pos_x, map->pos_y) == -1)
			exit((print_error(WINDOW), free_in_window(g), \
				EXIT_FAILURE));
	if (map->map[map->i][map->j] == '1')
		if (mlx_image_to_window(g->mlx, g->mini_map.wall_i, \
			map->pos_x, map->pos_y) == -1)
			exit((print_error(WINDOW), free_in_window(g), \
				EXIT_FAILURE));
}

int	put_wall(t_map *map, t_cub *g)
{
	map->pos_x = 0;
	map->pos_y = 0;
	map->i = -1;
	while (map->map[++map->i])
	{
		map->pos_x = WIDTH - g->mini_map.width;
		map->j = 0;
		while (map->map[map->i][map->j] && map->map[map->i][map->j] != '\n')
		{
			put_wall_2(map, g);
			map->pos_x += g->mini_map.size_wall_x;
			map->j++;
		}
		map->pos_y += g->mini_map.size_wall_y;
	}
	return (0);
}

int	map_to_window(t_cub *cub, bool actualise)
{
	if (actualise == false)
		init_mini_map(cub, &cub->mini_map);
	else
	{
		cub->mini_map.background_i = mlx_texture_to_image(cub->mlx, \
			cub->mini_map.background_t);
		if (mlx_resize_image(cub->mini_map.background_i, cub->mini_map.width, \
			cub->mini_map.height) == false)
			exit((print_error(RESIZE), free_in_window(cub), EXIT_FAILURE));
	}
	if (-1 == mlx_image_to_window(cub->mlx, cub->mini_map.background_i, WIDTH - \
		cub->mini_map.width, 0))
		exit((print_error(WINDOW), free_in_window(cub), EXIT_FAILURE));
	put_wall(cub->map, cub);
	return (0);
}

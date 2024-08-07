/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:23:09 by amirloup          #+#    #+#             */
/*   Updated: 2024/08/07 15:30:07 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	count_player(t_map *map, t_cub *cub)
{
	int	i;
	int	j;
	int	c;

	(void)cub;
	i = 1;
	c = 0;
	while (i < map->height)
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S'
				|| map->map[i][j] == 'E' || map->map[i][j] == 'W')
			{
				map->player_char = map->map[i][j];
				c++;
			}
			j++;
		}
		i++;
	}
	return (c);
}

int	*get_length(t_map *map)
{
	int	i;
	int	*length;

	i = -1;
	length = malloc(sizeof(int) * map->height);
	if (!length)
		return (NULL);
	while (map->map[++i])
	{
		length[i] = ft_strlen(map->map[i]);
		if (length[i] > 100 || map->height > 100)
			return (print_error("Map too big\n"), \
				free(length), NULL);
	}
	return (length);
}

int	check_hole(t_map *map, int *i, int *j)
{
	if (map->map[*i][*j] == '0' || map->map[*i][*j] == 'E'
		|| map->map[*i][*j] == 'S' || map->map[*i][*j] == 'N'
		|| map->map[*i][*j] == 'W' || map->map[*i][*j] == 'D'
		|| map->map[*i][*j] == 'A' || map->map[*i][*j] == 'X')
	{
		if (ft_isspace(map->map[*i][(*j) - 1]))
			return (-1);
		if (ft_isspace(map->map[*i][(*j) + 1]))
			return (-1);
		if (map->length[(*i) - 1] < (*j) - 1
			|| ft_isspace(map->map[*i - 1][*j]))
			return (-1);
		if (map->length[(*i) + 1] < (*j) + 1
			|| ft_isspace(map->map[(*i) + 1][*j]))
			return (-1);
	}
	return (0);
}

int	basic_check(t_map *map, int j, t_cub *cub)
{
	if (count_player(map, cub) != 1)
		return (print_error(PLAYER), -1);
	while (map->map[0][j] && (map->map[0][j] == '1'
		|| ft_isspace(map->map[0][j])))
		j++;
	if (map->map[0][j])
		exit((free_map_stuff(map), print_error("Wrong input\n"), EXIT_FAILURE));
	j = 0;
	while (map->map[map->height - 1][j] && (map->map[map->height - 1][j] == '1'
		|| ft_isspace(map->map[map->height - 1][j])))
		j++;
	if (map->map[map->height - 1][j])
		return (-1);
	return (0);
}

int	parsing_map(t_map *map, t_cub *cub)
{
	int	i;
	int	j;

	map->length = get_length((i = 0, j = 0, map));
	if (!map->length)
		return (-1);
	if (basic_check(map, j, cub) == -1)
		return (print_error("Map open\n"), -1);
	while (++i < map->height - 1)
	{
		j = -1;
		while (map->map[i][++j])
		{
			if (check_hole(map, &i, &j) == -1)
				return (print_error("Map open\n"), -1);
			if (map->map[i][j] != '0' && map->map[i][j] != 'E'
				&& map->map[i][j] != 'S' && map->map[i][j] != 'N'
				&& map->map[i][j] != 'W' && map->map[i][j] != 'D'
				&& map->map[i][j] != 'A' && map->map[i][j] != 'X'
				&& map->map[i][j] != '1' && map->map[i][j] != ' '
				&& map->map[i][j] != '\n')
				return (print_error("Wrong input\n"), -1);
		}
	}
	return (0);
}

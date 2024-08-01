/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:53:18 by amirloup          #+#    #+#             */
/*   Updated: 2024/08/01 11:10:23 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	check_floor_and_ceiling(t_map *map)
{
	map->i = 0;
	map->tab_f = ft_split(map->f, ',');
	if (!map->tab_f)
		return (print_error(MALLOC), 1);
	map->tab_c = ft_split(map->c, ',');
	if (!map->tab_c)
		return (print_error(MALLOC), 1);
	if (map->tab_f[0] == NULL || map->tab_f[1] == NULL || map->tab_f[2] == NULL
		|| map->tab_f[3] != NULL || map->tab_c[0] == NULL
		|| map->tab_c[1] == NULL || map->tab_c[2] == NULL
		|| map->tab_c[3] != NULL)
		return (print_error(RGB), ft_free_tab(map->tab_f), \
			ft_free_tab(map->tab_c), 1);
	while (map->i < 3)
	{
		map->rgb_f[map->i] = ft_atoi(map->tab_f[map->i]);
		map->rgb_c[map->i] = ft_atoi(map->tab_c[map->i]);
		if (map->rgb_f[map->i] < 0 || map->rgb_f[map->i] > 255
			|| map->rgb_c[map->i] < 0 || map->rgb_c[map->i] > 255)
			return (print_error(RGB), \
			ft_free_tab(map->tab_f), ft_free_tab(map->tab_c), 1);
		map->i++;
	}
	return (ft_free_tab(map->tab_f), ft_free_tab(map->tab_c), 0);
}

void	get_textures_2(t_map *map, char *line)
{
	if (line[0] == 'E' && line[1] == 'A')
	{
		map->i_ea++;
		if (map->i_ea <= 1)
			map->ea = ft_strtrim((map->ea = ft_strdup(line + 3), map->ea), " ");
		if (!map->ea)
			exit ((free_map_stuff(map), EXIT_FAILURE));
	}
	if (line[0] == 'F')
	{
		map->i_f++;
		if (map->i_f <= 1)
			map->f = ft_strtrim((map->f = ft_strdup(line + 2), map->f), " ");
		if (!map->f)
			exit ((free_map_stuff(map), EXIT_FAILURE));
	}
	if (line[0] == 'C')
	{
		map->i_c++;
		if (map->i_c <= 1)
			map->c = ft_strdup(line + 2);
		if (!map->c)
			exit ((free_map_stuff(map), EXIT_FAILURE));
	}
}

void	get_textures_3(t_map *map, char *line)
{
	if (line[0] == 'W' && line[1] == 'E')
	{
		map->i_we++;
		if (map->i_we <= 1)
		{
			map->we = ft_strdup(line + 3);
			map->we = ft_strtrim(map->we, " ");
		}
		if (!map->we)
			exit ((free_map_stuff(map), EXIT_FAILURE));
	}
}

void	get_textures(t_map *map, char *line)
{
	if (line[0] == 'N' && line[1] == 'O')
	{
		map->i_no++;
		if (map->i_no <= 1)
		{
			map->no = ft_strdup(line + 3);
			map->no = ft_strtrim(map->no, " ");
		}
		if (!map->no)
			exit ((free_map_stuff(map), EXIT_FAILURE));
	}
	if (line[0] == 'S' && line[1] == 'O')
	{
		map->i_so++;
		if (map->i_so <= 1)
			map->so = ft_strtrim((map->so = ft_strdup(line + 3), map->so), " ");
		if (!map->so)
			exit ((free_map_stuff(map), EXIT_FAILURE));
	}
	get_textures_2(map, line);
	get_textures_3(map, line);
	if (map->i_no > 1 || map->i_so > 1 || map->i_we > 1 || map->i_ea > 1 \
		|| map->i_f > 1 || map->i_c > 1)
		exit ((print_error(TEXTURE2), EXIT_FAILURE));
}

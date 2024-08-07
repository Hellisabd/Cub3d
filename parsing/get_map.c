/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:22:40 by amirloup          #+#    #+#             */
/*   Updated: 2024/08/07 15:30:59 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	remove_blank(t_map *map)
{
	int		i;
	int		j;
	int		k;
	char	**new_map;

	i = 0;
	j = map->height - 1;
	while (ft_strisspace(map->map[i]) == true)
		i++;
	while (ft_strisspace(map->map[j]) == true)
		j--;
	map->height = j - i + 1;
	new_map = malloc(sizeof(char *) * (map->height + 1));
	if (!new_map)
		exit((free_map_stuff(map), print_error(MALLOC), EXIT_FAILURE));
	k = 0;
	while (i <= j)
	{
		new_map[k] = ft_strdup(map->map[i]);
		i++;
		k++;
	}
	new_map[k] = NULL;
	ft_free_tab(map->map);
	map->map = new_map;
}

void	get_map_heigth(t_map *map, char **argv)
{
	int		fd;
	char	*line;

	map->height = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit((free_map_stuff(map), print_error(LOAD_MAP), EXIT_FAILURE));
	line = get_next_line(fd);
	if (!line)
		exit((free_map_stuff(map), print_error(EMPTY), EXIT_FAILURE));
	while (line != NULL)
	{
		if (line[0] != 'N' && line[0] != 'S' && line[0] != 'W' && line[0] != 'E'
			&& line[0] != 'F' && line[0] != 'C' /*&& line[0] != '\n'
			&& ft_strisspace(line) == false*/)
			map->height++;
		free(line);
		line = get_next_line(fd);
	}
	if (!map->height)
		exit((free_map_stuff(map), print_error(EMPTY), EXIT_FAILURE));
	close (fd);
}

void	get_map(char *line, t_map *map, int fd)
{
	while (line != NULL)
	{
		get_textures(map, line);
		if (line[0] != 'N' && line[0] != 'S' && line[0] != 'W' && line[0] != 'E'
			&& line[0] != 'F' && line[0] != 'C' /*&& line[0] != '\n'
			&& ft_strisspace(line) == false*/)
		{
			map->map[map->i] = ft_strdup(line);
			if (!map->map[map->i++])
				exit ((free_map_stuff(map), EXIT_FAILURE));
		}
		free(line);
		line = get_next_line(fd);
	}
	map->map[map->i] = NULL;
	remove_blank(map);
	map->no = ft_strtrim(map->no, "\n");
	map->so = ft_strtrim(map->so, "\n");
	map->we = ft_strtrim(map->we, "\n");
	map->ea = ft_strtrim(map->ea, "\n");
	map->f_h = rgb_to_hex(map->f);
	map->c_h = rgb_to_hex(map->c);
	if (!map->no || !map->so || !map->we || !map->ea || map->f_h == INT_MIN \
		|| map->c_h == INT_MIN)
		exit ((free_map_stuff(map), print_error(MISSING), EXIT_FAILURE));
}

void	open_map(t_map *map, char **argv)
{
	int		fd;
	char	*line;

	map->i_no = 0;
	map->i_so = 0;
	map->i_we = 0;
	map->i_ea = 0;
	map->i_f = 0;
	map->i_c = 0;
	map->i = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit((free_map_stuff(map), print_error(LOAD_MAP), EXIT_FAILURE));
	check_cub(map, argv[1]);
	get_map_heigth(map, argv);
	map->map = malloc(sizeof(char *) * (map->height + 1));
	if (!map->map)
		exit((free_map_stuff(map), print_error(MALLOC), EXIT_FAILURE));
	line = get_next_line(fd);
	get_map(line, map, fd);
	if (!map->no || !map->so || !map->we || !map->ea || !map->f || !map->c)
		exit((print_error(TEXTURE), free_map_stuff(map), EXIT_FAILURE));
	if (check_floor_and_ceiling(map) == 1)
		exit ((free_map_stuff(map), EXIT_FAILURE));
	close (fd);
}

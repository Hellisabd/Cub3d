/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:22:40 by amirloup          #+#    #+#             */
/*   Updated: 2024/07/11 13:22:57 by amirloup         ###   ########.fr       */
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

void	get_textures(t_map *map, char *line)
{
	if (line[0] == 'N' && line[1] == 'O')
		map->no = ft_strdup(line + 3);
	if (line[0] == 'S' && line[1] == 'O')
		map->so = ft_strdup(line + 3);
	if (line[0] == 'W' && line[1] == 'E')
		map->we = ft_strdup(line + 3);
	if (line[0] == 'E' && line[1] == 'A')
		map->ea = ft_strdup(line + 3);
	if (line[0] == 'F')
		map->f = ft_strdup(line + 2);
	if (line[0] == 'C')
		map->c = ft_strdup(line + 2);
}

void	get_map_heigth(t_map *map, char **argv)
{
	int		fd;
	char	*line;

	map->height = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit((print_error(LOAD_MAP), EXIT_FAILURE));
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line[0] != 'N' && line[0] != 'S' && line[0] != 'W' && line[0] != 'E'
			&& line[0] != 'F' && line[0] != 'C' && line[0] != '\n'
			&& ft_strisspace(line) == false)
			map->height++;
		free(line);
		line = get_next_line(fd);
	}
	close (fd);
}

void	get_map(char *line, t_map *map, int fd)
{
	while (line != NULL)
	{
		get_textures(map, line);
		if (line[0] != 'N' && line[0] != 'S' && line[0] != 'W' && line[0] != 'E'
			&& line[0] != 'F' && line[0] != 'C' && line[0] != '\n'
			&& ft_strisspace(line) == false)
			map->map[map->i++] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
	}
	map->map[map->i] = NULL;
	map->no = ft_strtrim(map->no, "\n");
	map->so = ft_strtrim(map->so, "\n");
	map->we = ft_strtrim(map->we, "\n");
	map->ea = ft_strtrim(map->ea, "\n");
	map->f_h = rgb_to_hex(map->f);
	map->c_h = rgb_to_hex(map->c);
}

void	open_map(t_map *map, char **argv)
{
	int		fd;
	char	*line;

	map->i = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit((print_error(LOAD_MAP), EXIT_FAILURE));
	check_cub(argv[1]);
	get_map_heigth(map, argv);
	map->map = malloc(sizeof(char *) * (map->height + 1));
	if (!map->map)
		exit((print_error(MALLOC), EXIT_FAILURE));
	line = get_next_line(fd);
	get_map(line, map, fd);
	if (!map->no || !map->so || !map->we || !map->ea || !map->f || !map->c)
		exit((print_error(TEXTURE), free_map_stuff(map), EXIT_FAILURE));
	if (check_floor_and_ceiling(map) == 1)
		exit ((free_map_stuff(map), EXIT_FAILURE));
	close (fd);
}

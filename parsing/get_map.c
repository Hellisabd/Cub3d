/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:41:38 by amirloup          #+#    #+#             */
/*   Updated: 2024/06/05 16:30:15 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	check_cub(char *s)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	if (s[i - 1] != 'b' || s[i - 2] != 'u' \
		|| s[i - 3] != 'c' || s[i - 4] != '.')
		exit((ft_printf("Error\nThe map is not a .cub file!\n"), EXIT_FAILURE));
}

int	check_floor_and_ceiling(t_map *map)
{
	char	**tab_f;
	char	**tab_c;
	int		n_f[3];
	int		n_c[3];
	int		i;

	i = 0;
	tab_f = ft_split(map->f, ',');
	tab_c = ft_split(map->c, ',');
	while (i < 3)
	{
		n_f[i] = ft_atoi(tab_f[i]);
		n_c[i] = ft_atoi(tab_c[i]);
		if (n_f[i] < 0 || n_f[i] > 255 || n_c[i] < 0 || n_c[i] > 255)
		{
			printf("Error\nWrong RGB format!\n");
			ft_free_tab(tab_f);
			ft_free_tab(tab_c);
			return (1);
		}
		i++;
	}
	ft_free_tab(tab_f);
	ft_free_tab(tab_c);
	return (0);
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

void	open_map(t_map *map, char **argv)
{
	int		fd;
	char	*line;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit((ft_printf("Error\nError while opening the map!\n"), EXIT_FAILURE));
	check_cub(argv[1]);
	line = get_next_line(fd);
	while (line != NULL)
	{
		get_textures(map, line);
		
		free(line);
		line = get_next_line(fd);
	}
	if (!map->no || !map->so || !map->we || !map->ea || !map->f || !map->c)
		exit((printf("Error\nTexture is missing!\n"), EXIT_FAILURE));
	if (check_floor_and_ceiling(map) == 1)
		exit (EXIT_FAILURE);
	printf("%s", map->no);
	printf("%s", map->so);
	printf("%s", map->we);
	printf("%s", map->ea);
	printf("%s", map->f);
	printf("%s", map->c);
	close (fd);
}

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
	int		i;

	i = 0;
	tab_f = ft_split(map->f, ',');
	if (!tab_f)
		return (printf("Error\nMalloc error!\n"), 1);
	tab_c = ft_split(map->c, ',');
	if (!tab_c)
		return (printf("Error\nMalloc error!\n"), 1);
	while (i < 3)
	{
		map->rgb_f[i] = ft_atoi(tab_f[i]);
		map->rgb_c[i] = ft_atoi(tab_c[i]);
		if (tab_f[3] != NULL || tab_c[3] != NULL || map->rgb_f[i] < 0 || map->rgb_f[i] > 255
			|| map->rgb_c[i] < 0 || map->rgb_c[i] > 255)
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

void	get_map_heigth(t_map *map, char **argv)
{
	int		fd;
	char	*line;

	map->height = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit((ft_printf("Error\nError while opening the map!\n"), EXIT_FAILURE));
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

void	open_map(t_map *map, char **argv)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit((ft_printf("Error\nError while opening the map!\n"), EXIT_FAILURE));
	check_cub(argv[1]);
	get_map_heigth(map, argv);
	map->map = malloc(sizeof(char *) * map->height);
	if (!map->map)
		exit((printf("Error\nMalloc error\n"), EXIT_FAILURE));
	line = get_next_line(fd);
	while (line != NULL)
	{
		get_textures(map, line);
		if (line[0] != 'N' && line[0] != 'S' && line[0] != 'W' && line[0] != 'E'
			&& line[0] != 'F' && line[0] != 'C' && line[0] != '\n'
			&& ft_strisspace(line) == false)
			map->map[i++] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
	}
	if (!map->no || !map->so || !map->we || !map->ea || !map->f || !map->c)
		exit((printf("Error\nTexture is missing!\n"), EXIT_FAILURE));
	if (check_floor_and_ceiling(map) == 1)
		exit (EXIT_FAILURE);
	close (fd);
}

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
	map->i = 0;
	map->tab_f = ft_split(map->f, ',');
	if (!map->tab_f)
		return (printf("Error\nMalloc error!\n"), 1);
	map->tab_c = ft_split(map->c, ',');
	if (!map->tab_c)
		return (printf("Error\nMalloc error!\n"), 1);
	if (map->tab_f[0] == NULL || map->tab_f[1] == NULL || map->tab_f[2] == NULL
		|| map->tab_f[3] != NULL || map->tab_c[0] == NULL
		|| map->tab_c[1] == NULL || map->tab_c[2] == NULL
		|| map->tab_c[3] != NULL)
		return (printf("Error\nWrong RGB format!\n"), ft_free_tab(map->tab_f), \
			ft_free_tab(map->tab_c), 1);
	while (map->i < 3)
	{
		map->rgb_f[map->i] = ft_atoi(map->tab_f[map->i]);
		map->rgb_c[map->i] = ft_atoi(map->tab_c[map->i]);
		if (map->rgb_f[map->i] < 0 || map->rgb_f[map->i] > 255
			|| map->rgb_c[map->i] < 0 || map->rgb_c[map->i] > 255)
			return (printf("Error\nWrong RGB format!\n"), \
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

	map->i = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit((ft_printf("Error\nError while opening the map!\n"), EXIT_FAILURE));
	check_cub(argv[1]);
	get_map_heigth(map, argv);
	map->map = malloc(sizeof(char *) * (map->height + 1));
	if (!map->map)
		exit((printf("Error\nMalloc error\n"), EXIT_FAILURE));
	line = get_next_line(fd);
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
	if (!map->no || !map->so || !map->we || !map->ea || !map->f || !map->c)
		exit((printf("Error\nTexture is missing!\n"), free_and_destroy(map), EXIT_FAILURE));
	if (check_floor_and_ceiling(map) == 1)
		exit ((free_and_destroy(map), EXIT_FAILURE));
	close (fd);
}

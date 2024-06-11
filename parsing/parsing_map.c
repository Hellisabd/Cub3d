#include "../cub3D.h"

void	set_player(char dir, t_cub *cub)
{
	if (dir == 'N')
	{
		cub->dir_x = 0;
		cub->dir_y = -1;
	}
	if (dir == 'S')
	{
		cub->dir_x = 0;
		cub->dir_y = 1;
	}
	if (dir == 'E')
	{
		cub->dir_x = 1;
		cub->dir_y = 0;
	}
	if (dir == 'W')
	{
		cub->dir_x = -1;
		cub->dir_x = 0;
	}
}

int	count_player(t_map *map, t_cub *cub)
{
	int	i;
	int	j;
	int	c;

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
				map->d = map->map[i][j];
				set_player(map->map[i][j], cub);
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
		length[i] = ft_strlen(map->map[i]);
	return (length);
}

int	check_hole(t_map *map, int *i, int *j)
{
	if (map->map[*i][*j] == '0' || map->map[*i][*j] == 'E'
		|| map->map[*i][*j] == 'S' || map->map[*i][*j] == 'N'
			|| map->map[*i][*j] == 'W')
	{
		if (ft_isspace(map->map[*i][(*j) - 1]))
			return (debug_str(BLUE, NULL, "sortie 3"), -1);
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
		return (-2);
	while (map->map[0][j] && (map->map[0][j] == '1'
		|| ft_isspace(map->map[0][j])))
		j++;
	if (map->map[0][j])
		return (debug_str(BLUE, NULL, "sortie 1"), -1);
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

	i = 1;
	j = 0;
	map->length = get_length(map);
	if (basic_check(map, j, cub) == -1)
		return (-1);
	while (i < map->height - 1)
	{
		j = 0;
		while (map->map[i][j])
		{
			if (check_hole(map, &i, &j) == -1)
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

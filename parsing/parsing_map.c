#include "../cub3D.h"

int	*get_length(t_map *map)
{
	int	i;
	int *length;

	i =  -1;
	length = malloc(sizeof(int) * map->height);
	while (map->map[++i])
		length[i] = ft_strlen(map->map[i]);
	return (length);
}

int	parsing_map(t_map *map)
{
	int i = 1;
	int	j = 0;

	map->length = get_length(map);
	i = 0;
	while (map->map[0][j] && (map->map[0][j] == '1' || ft_isspace(map->map[0][j])))
		j++;
	if (map->map[0][j])
		return (debug_str(BLUE, NULL, "sortie 1"), -1);
	j = 0;
	while (map->map[map->height - 1][j] && (map->map[map->height - 1][j] == '1' || ft_isspace(map->map[map->height - 1][j])))
		j++;
	if (map->map[map->height - 1][j])
		return (-1);
	while (i < map->height - 2)
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == 0)
			{
				if (map->map[i][j - 1] != '1' || ft_isspace(map->map[i][j - 1]))
					return (debug_str(BLUE, NULL, "sortie 3"), -1);
				if (map->map[i][j + 1] != '1' || ft_isspace(map->map[i][j + 1]))
					return (-1);
				if (map->length[i - 1] < j - 1 || map->map[i - 1][j] != '1' || ft_isspace(map->map[i - 1][j]))
					return (-1);
				if (map->length[i + 1] < j + 1 || map->map[i + 1][j] != '1' || ft_isspace(map->map[i + 1][j]))
					return (-1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

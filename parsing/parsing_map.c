#include "../cub3D.h"

int	*get_length(char **map)
{
	int *length;
	int	i;

	length = malloc(sizeof(int) * map->heigth);
	while (map[i])
		length[i++] = ft_strlen(map[i]);
	return (length);
}

int	parsing_map(char **map)
{
	int i = 1;
	int	j = 0;
	int	*length;

	length = get_length(map);
	while (map[0][j] && (map[0][j] == 1 || ft_isspace(map[0][j])))
		j++;
	if (map[0][j])
		return (-1);
	j = 0;
	while (map[map->height - 1] && (map[map->height - 1][i] == 1 || ft_isspace(map[map->height - 1][j])))
		j++;
	if (map[map->height - 1][j])
		return (-1);
	while (i < map->height - 2)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 0)
			{
				if (map[i][j - 1] != 1 || ft_isspace(map[i][j - 1]))
					return (-1);
				if (map[i][j + 1] != 1 || ft_isspace(map[i][j + 1]))
					return (-1);
				if (map[i - 1][j] != 1 || ft_isspace(map[i - 1][j]))
					return (-1);
				if (map[i - 1][j] != 1 || ft_isspace(map[i + 1][j]))
					return (-1);
			}
			j++;
		}
		i++;
	}
}
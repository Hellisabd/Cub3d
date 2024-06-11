#include "../cub3D.h"

void	set_player_pos(t_cub *cub)
{
	int	i;
	int	j;

	i = 1;
	while (i < cub->map->height)
	{
		j = 0;
		while (cub->map->map[i][j])
		{
			if (cub->map->map[i][j] == 'N' || cub->map->map[i][j] == 'S'
				|| cub->map->map[i][j] == 'E' || cub->map->map[i][j] == 'W')
			{
				cub->p_x = j + 0.5;
				cub->p_y = i + 0.5;
			}
			j++;
		}
		i++;
	}
}

void	raycasting(t_cub *cub)
{
	float	x;
	float	y;
	int		i;
	int		j;

	set_player_pos(cub);
	x = cub->p_x;
	y = cub->p_y;
	printf("x: %f\n", x);
	printf("y: %f\n", y);
	i = (int)(x - ((int)(x * 10) % 10));
	j = (int)(y - ((int)(y * 10) % 10));
	printf("i: %i\n", i);
	printf("j: %i\n", j);
	// while (cub->map->map[i][j] == '0')
	// {

	// }
	// printf("%f\n", abs(cub->p_y - y));
}

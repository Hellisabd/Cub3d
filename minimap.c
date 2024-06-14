#include "cub3D.h"

int	put_wall(t_mini_map *mini_map, int i, int j)
{
	int pos_x = ;
	int pos_y = ;
	mlx_image_to_window(mini_map->wall_i);
	
}

int map_to_window(t_cub *cub)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (cub->map->map[i])
	{
		while (cub->map->map[i][j])
		{
			if (cub->map->map[i][j] == 1)
				put_wall(cub->mini_map, i, j);
		}
	}
}

#include "cub3D.h"

int init_mini_map(t_cub *cub, t_mini_map *mini_map)
{
	mini_map->wall_t = mlx_load_png(WALL);
	mini_map->background_t = mlx_load_png(BACKGROUND);
	mlx_texture_to_image(cub->mlx, mini_map->background_t);
	mlx_texture_to_image(cub->mlx, mini_map->wall_t);
}
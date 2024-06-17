#include "../cub3D.h"

void	open_window(t_cub *cub)
{
	init_data_mini_map(&cub->mini_map, cub->map);
	cub->mlx = mlx_init(cub->mini_map.width, cub->mini_map.height, "cub3D", true);
	if (!cub->mlx)
		exit((ft_printf("Error\nInitializing MLX!\n"), EXIT_FAILURE));
	mlx_set_window_pos(cub->mlx, 1000, 500);
	mlx_set_window_limit(cub->mlx, cub->mini_map.width, cub->mini_map.height, cub->mini_map.width, cub->mini_map.height);
	raycasting(cub);
	map_to_window(cub);
	draw_ray(cub->ray, &cub->mini_map, cub);
	// mlx_loop_hook(cub->mlx, ft_hook, (void *)cub);
	mlx_loop(cub->mlx);
	mlx_terminate(cub->mlx);
}

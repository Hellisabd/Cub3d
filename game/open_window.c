#include "../cub3D.h"

void	open_window(t_cub *cub)
{
	// cub->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	// if (!cub->mlx)
	// 	exit((ft_printf("Error\nInitializing MLX!\n"), EXIT_FAILURE));
	// mlx_set_window_pos(cub->mlx, 1000, 500);
	// mlx_set_window_limit(cub->mlx, WIDTH, HEIGHT, WIDTH, HEIGHT);
	cub->rot = PI / 2;
	raycasting(cub);
	// while (1)
		// ;
	// mlx_loop_hook(cub->mlx, ft_hook, (void *)cub);
	// mlx_loop(cub->mlx);
	// mlx_terminate(cub->mlx);
}

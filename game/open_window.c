#include "../cub3D.h"

void	move(mlx_key_data_t key, void *param)
{
	t_cub	*cub;

	cub = param;
	// if (key.key == MLX_KEY_W && (key.action == 1 || key.action == 2))
	// 	move_up(cub);
	// if (key.key == MLX_KEY_S && (key.action == 1 || key.action == 2))
	// 	move_down(cub);
	// if (key.key == MLX_KEY_A && (key.action == 1 || key.action == 2))
	// 	move_left(cub);
	// if (key.key == MLX_KEY_D && (key.action == 1 || key.action == 2))
	// 	move_rigth(cub);
	if (key.key == MLX_KEY_RIGHT && (key.action == 1 || key.action == 2))
		{
			cub->rot -= PI / 10;
			raycasting(cub);
			draw_ray(&cub->ray, &cub->mini_map, cub, H_GREEN);
		}
	if (key.key == MLX_KEY_LEFT && (key.action == 1 || key.action == 2))
		{
			cub->rot += PI / 10;
			raycasting(cub);
			draw_ray(&cub->ray, &cub->mini_map, cub, H_GREEN);
		}
}

void	ft_hook(void *param)
{
	t_cub	*cub;

	cub = param;
	mlx_key_hook(cub->mlx, move, (void *)cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub->mlx);
}

void	open_window(t_cub *cub)
{
	init_data_mini_map(&cub->mini_map, cub->map);
	cub->mlx = mlx_init(cub->mini_map.width, cub->mini_map.height, "cub3D", true);
	if (!cub->mlx)
		exit((ft_printf("Error\nInitializing MLX!\n"), EXIT_FAILURE));
	mlx_set_window_pos(cub->mlx, 1000, 500);
	mlx_set_window_limit(cub->mlx, cub->mini_map.width, cub->mini_map.height, cub->mini_map.width, cub->mini_map.height);
	debug_nbr(RED, "mini_map_height :", cub->mini_map.height);
	debug_nbr(RED, "mini_map_width :", cub->mini_map.width);
	cub->rot = 0;
	raycasting(cub);
	map_to_window(cub);
	draw_ray(&cub->ray, &cub->mini_map, cub, H_GREEN);
	mlx_loop_hook(cub->mlx, ft_hook, (void *)cub);
	mlx_loop(cub->mlx);
	mlx_terminate(cub->mlx);
}

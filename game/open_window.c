#include "../cub3D.h"

// void	move(mlx_key_data_t key, void *param)
// {
// 	t_cub	*cub;

// 	g = param;
// 	cub->p_pos_x = cub->sprite.player_left->instances[0].x;
// 	cub->p_pos_y = cub->sprite.player_left->instances[0].y;
// 	cub->p_coord_x = round(cub->p_pos_x * (float)(cub->data.width - 1) / WIDTH);
// 	cub->p_coord_y = round(cub->p_pos_y * (float)cub->data.height / HEIGHT);
// 	if (key.key == MLX_KEY_W && (key.action == 1 || key.action == 2) \
// 		&& check_up(g) == 1 && cub->success == 0 && cub->alive == 1)
// 		move_up(g);
// 	if (key.key == MLX_KEY_S && (key.action == 1 || key.action == 2) \
// 		&& check_down(g) == 1 && cub->success == 0 && cub->alive == 1)
// 		move_down(g);
// 	if (key.key == MLX_KEY_A && (key.action == 1 || key.action == 2) \
// 		&& check_left(g) == 1 && cub->success == 0 && cub->alive == 1)
// 		move_left(g);
// 	if (key.key == MLX_KEY_D && (key.action == 1 || key.action == 2) \
// 		&& check_rigth(g) == 1 && cub->success == 0 && cub->alive == 1)
// 		move_rigth(g);
// }

void	ft_hook(void *param)
{
	t_cub	*cub;

	cub = param;
	// mlx_key_hook(cub->mlx, move, (void *)g);
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
	raycasting(cub);
	map_to_window(cub);
	draw_ray(cub->ray, &cub->mini_map, cub);
	mlx_loop_hook(cub->mlx, ft_hook, (void *)cub);
	mlx_loop(cub->mlx);
	mlx_terminate(cub->mlx);
}

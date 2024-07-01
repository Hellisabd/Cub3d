#include "../cub3D.h"

void	move_player(t_cub *cub, float dir)
{
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT_SHIFT))
		cub->speed = cub->mini_map.size_wall_x / 4;
	else
		cub->speed = cub->mini_map.size_wall_x / 8;
	int	deplacement_x;
	int	deplacement_y;

	deplacement_x = (int)(round(cos(dir) * cub->speed));
	deplacement_y = (int)(round(sin(dir) * cub->speed));
	
	// debug_nbr(RED, "next_pos_x :", (int)round((float)(cub->player.pos_x + deplacement_x) / (float)cub->mini_map.size_wall_x));
	if (cub->map->map[(int)round(((cub->player.pos_y - cub->mini_map.size_wall_y / 2) + deplacement_y) / (float)cub->mini_map.size_wall_y)][((int)round((float)((cub->player.pos_x - cub->mini_map.size_wall_x / 2) + deplacement_x) / (float)cub->mini_map.size_wall_x))] == '1')
		return ;
	else if (cub->map->map[(int)round(((cub->player.pos_y + cub->mini_map.size_wall_y / 2) + deplacement_y) / (float)cub->mini_map.size_wall_y)][((int)round((float)((cub->player.pos_x + cub->mini_map.size_wall_x / 2) + deplacement_x) / (float)cub->mini_map.size_wall_x))] == '1')
		return ;
	else if (cub->map->map[(int)round(((cub->player.pos_y - cub->mini_map.size_wall_y / 2) + deplacement_y) / (float)cub->mini_map.size_wall_y)][((int)round((float)((cub->player.pos_x + cub->mini_map.size_wall_x / 2) + deplacement_x) / (float)cub->mini_map.size_wall_x))] == '1')
		return ;
	else if (cub->map->map[(int)round(((cub->player.pos_y + cub->mini_map.size_wall_y / 2) + deplacement_y) / (float)cub->mini_map.size_wall_y)][((int)round((float)((cub->player.pos_x - cub->mini_map.size_wall_x / 2) + deplacement_x) / (float)cub->mini_map.size_wall_x))] == '1')
		return ;
	cub->player.pos_x += deplacement_x;
	cub->mini_map.player_i->instances->x += deplacement_x;
	cub->player.pos_y += deplacement_y;
	cub->mini_map.player_i->instances->y += deplacement_y;
}

void	move_left(t_cub *cub)
{
		move_player(cub, cub->player.dir_left);
}

void	move_right(t_cub *cub)
{
		move_player(cub, cub->player.dir_right);
}

void	move_down(t_cub *cub)
{
		move_player(cub, cub->player.dir_down);
}

void	move_up(t_cub *cub)
{
		move_player(cub, cub->player.dir_up);
}

void	rotations(double xpos, double ypos, void *param)
{
	t_cub	*cub;
	int		x;
	int		y;

	cub = param;
	x = (int)xpos;
	y = (int)ypos;
	mlx_get_mouse_pos(cub->mlx, &x, &y);
	if (x > WIDTH / 2)
		cub->rot += PI / 20;
	if (x < WIDTH / 2)
		cub->rot -= PI / 20;
	mlx_set_mouse_pos(cub->mlx, WIDTH / 2, HEIGHT / 2);
}

void	move(t_cub *cub)
{
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
		move_up(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
		move_down(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
		move_left(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
		move_right(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
		cub->rot += PI / 10;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
		cub->rot -= PI / 10;
}

void	refresh(t_cub *cub)
{
	cub->player.dir_up = cub->rot;
	cub->player.dir_down = cub->rot + PI;
	if (cub->player.dir_down >= 2 * PI)
		cub->player.dir_down -= 2 * PI;
	cub->player.dir_left = cub->rot + 3 * PI / 2;
	if (cub->player.dir_left >= 2 * PI)
		cub->player.dir_left -= 2 * PI;
	cub->player.dir_right = cub->rot + PI / 2;
	if (cub->player.dir_right >= 2 * PI)
		cub->player.dir_right -= 2 * PI;
	raycasting(cub);
	draw_ray(&cub->ray, &cub->mini_map, cub, H_GREEN);
}

void	ft_hook(void *param)
{
	t_cub	*cub;

	cub = param;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub->mlx);
	move(cub);
	refresh(cub);
}

void	ft_cursor(t_cub *cub)
{
	mlx_win_cursor_t	*cursor;

	cub->cursor_t = mlx_load_png(CURSOR);
	if (cub->cursor_t == NULL)
		debug_str(RED, NULL, "failed to load textures");
	cursor = mlx_create_cursor(cub->cursor_t);
	mlx_set_cursor(cub->mlx, cursor);
}

void	init_raycast(t_cub *cub)
{
	if (cub->map->player_char == 'N')
		cub->rot = -PI / 2;
	if (cub->map->player_char == 'S')
		cub->rot = PI / 2;
	if (cub->map->player_char == 'E')
		cub->rot = 0;
	if (cub->map->player_char == 'W')
		cub->rot = PI;
	cub->ray = NULL;
}

void	open_window(t_cub *cub)
{
	init_data_mini_map(&cub->mini_map, cub->map);
	set_player_pos(cub);
	cub->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!cub->mlx)
		exit((ft_printf("Error\nInitializing MLX!\n"), EXIT_FAILURE));
	mlx_set_window_pos(cub->mlx, 500, 250);
	mlx_set_window_limit(cub->mlx, WIDTH, HEIGHT, WIDTH, HEIGHT);
	ft_cursor(cub);
	init_raycast(cub);
	lets_go_3d(cub);
	raycasting(cub);
	map_to_window(cub);
	draw_ray(&cub->ray, &cub->mini_map, cub, H_GREEN);
	mlx_set_mouse_pos(cub->mlx, WIDTH / 2, HEIGHT / 2);
	mlx_loop_hook(cub->mlx, ft_hook, (void *)cub);	
	mlx_cursor_hook(cub->mlx, rotations, (void *)cub);
	// mlx_key_hook(cub->mlx, key_modifiers, (void *)cub);
	mlx_loop(cub->mlx);
	mlx_terminate(cub->mlx);
}

#include "../cub3D.h"

bool	next_step_is_not_wall(int x, int y, t_cub *cub, int dir)
{
	int i;
	int j;

	if (dir == RIGHT)
	{
		i = floor(y / cub->mini_map.size_wall_y);
		j = 2 + floor(x / cub->mini_map.size_wall_x);
		if (j < 2 + floor((x + 10) / cub->mini_map.size_wall_x))
		{
			if (cub->map->map[i][j] == '1')
				return (false);
			return (true);
		}
	}
	else if (dir == LEFT)
	{
		i = floor(y / cub->mini_map.size_wall_y);
		j = floor(x / cub->mini_map.size_wall_x);
		// debug_nbr(RED, "pos_x on map", j);
		// debug_nbr(RED, "next_pos", floor((x - 10) / cub->mini_map.size_wall_x));
		// debug_char(BLUE, "pos player on map", cub->map->map[i][j]);
		if (cub->map->map[i][(int)floor((x - 10) / cub->mini_map.size_wall_x)] == '1')
			return (false);
	}
	else if (dir == UP)
	{
		i = floor(y / cub->mini_map.size_wall_y);
		j = floor(x / cub->mini_map.size_wall_x);
		// debug_nbr(RED, "pos_x on map", j);
		// debug_nbr(RED, "next_pos", floor((x - 10) / cub->mini_map.size_wall_x));
		// debug_char(BLUE, "pos player on map", cub->map->map[i][j]);
		if (cub->map->map[(int)floor((y - 10) / cub->mini_map.size_wall_y)][j] == '1')
			return (false);
	}
	else if (dir == DOWN)
	{
		i = 2 + floor(y / cub->mini_map.size_wall_y);
		j = floor(x / cub->mini_map.size_wall_x);
		if (i < 2 + floor((y + 10) / cub->mini_map.size_wall_y))
		{
			if (cub->map->map[i][j] == '1')
				return (false);
			return (true);
		}
	}
	return (true);
}

void move_player(t_cub *cub, float dir)
{
	int dist = 10;
	int	deplacement_x;
	int	deplacement_y;

	deplacement_x = (int)(round(cos(dir) * dist));
	deplacement_y = (int)(round(sin(dir) * dist));
	cub->player.pos_x += deplacement_x;
	cub->mini_map.player_i->instances->x += deplacement_x;
	cub->player.pos_y += deplacement_y;
	cub->mini_map.player_i->instances->y += deplacement_y;
}

void	move_left(t_cub *cub)
{
	if (next_step_is_not_wall(cub->player.pos_x, cub->player.pos_y, cub, LEFT))
	{
		move_player(cub, cub->player.dir_left);
		raycasting(cub);
		draw_ray(&cub->ray, &cub->mini_map, cub, H_GREEN);
	}
}

void	move_right(t_cub *cub)
{
	if (next_step_is_not_wall(cub->player.pos_x, cub->player.pos_y, cub, RIGHT))
	{
		move_player(cub, cub->player.dir_right);
		raycasting(cub);
		draw_ray(&cub->ray, &cub->mini_map, cub, H_GREEN);
	}
}

void	move_down(t_cub *cub)
{
	if (next_step_is_not_wall(cub->player.pos_x, cub->player.pos_y, cub, DOWN))
	{
		move_player(cub, cub->player.dir_up);
		raycasting(cub);
		draw_ray(&cub->ray, &cub->mini_map, cub, H_GREEN);
	}
}

void	move_up(t_cub *cub)
{
	if (next_step_is_not_wall(cub->player.pos_x, cub->player.pos_y, cub, UP))
	{
		move_player(cub, cub->player.dir_up);
		raycasting(cub);
		draw_ray(&cub->ray, &cub->mini_map, cub, H_GREEN);
	}
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
	{
		cub->rot += PI / 40;
		raycasting(cub);
		draw_ray(&cub->ray, &cub->mini_map, cub, H_GREEN);
	}
	if (x < WIDTH / 2)
	{
		cub->rot -= PI / 40;
		raycasting(cub);
		draw_ray(&cub->ray, &cub->mini_map, cub, H_GREEN);
	}
	mlx_set_mouse_pos(cub->mlx, WIDTH / 2, HEIGHT / 2);
}

void	move(mlx_key_data_t key, void *param)
{
	t_cub	*cub;

	cub = param;
	if (key.key == MLX_KEY_W && (key.action == 1 || key.action == 2))
		move_up(cub);
	if (key.key == MLX_KEY_S && (key.action == 1 || key.action == 2))
		move_down(cub);
	if (key.key == MLX_KEY_A && (key.action == 1 || key.action == 2))
		move_left(cub);
	if (key.key == MLX_KEY_D && (key.action == 1 || key.action == 2))
		move_right(cub);
	if (key.key == MLX_KEY_RIGHT && (key.action == 1 || key.action == 2))
	{
		cub->rot += PI / 10;
		raycasting(cub);
		draw_ray(&cub->ray, &cub->mini_map, cub, H_GREEN);
	}
	if (key.key == MLX_KEY_LEFT && (key.action == 1 || key.action == 2))
	{
		cub->rot -= PI / 10;
		raycasting(cub);
		draw_ray(&cub->ray, &cub->mini_map, cub, H_GREEN);
	}
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
}

void	ft_hook(void *param)
{
	t_cub	*cub;

	cub = param;
	mlx_cursor_hook(cub->mlx, rotations, (void *)cub);
	mlx_key_hook(cub->mlx, move, (void *)cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub->mlx);
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
	mlx_loop(cub->mlx);
	mlx_terminate(cub->mlx);
}

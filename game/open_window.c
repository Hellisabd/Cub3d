#include "../cub3D.h"

void	move_player(t_cub *cub, float dir)
{
	static int	stamina = 100;
	
	cub->speed = cub->mini_map.size_wall_x / 8;
	cub->stamina = stamina;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT_SHIFT) && stamina > 0)
	{
		cub->speed = cub->mini_map.size_wall_x / 4;
		if (cub->speed == 0)
			cub->speed = 2;
		// debug_nbr(GREEN, NULL, stamina);
		cub->stamina = stamina;
		stamina--;
	}
	if (!mlx_is_key_down(cub->mlx, MLX_KEY_LEFT_SHIFT) && stamina < 100)
	{
		cub->speed = cub->mini_map.size_wall_x / 8;
		if (cub->speed == 0)
			cub->speed = 1;
		if (stamina > 100)
			stamina = 100;
		// debug_nbr(BLUE, NULL, stamina);
		cub->stamina = stamina;
		stamina++;
	}
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

void	put_stamina(t_cub *cub)
{
	int	n;
	int	x;
	int	y;
	
	n = 100;
	y = HEIGHT - 150;
	x = WIDTH / 2 - 300;
	while (n-- >= cub->stamina)
	{
		if (n == cub->stamina)
		{
			while (x++ < WIDTH / 2 + 300 - (6 * (100 - n)))
			{
				y = HEIGHT - 150;
				while (y < HEIGHT - 100)
					mlx_put_pixel(cub->world.hud, x, y++, H_YELLOW);
			}
			while (x++ < WIDTH / 2 + 300)
			{
				y = HEIGHT - 150;
				while (y < HEIGHT - 100)
					mlx_put_pixel(cub->world.hud, x, y++, 0);
			}
		}
	}
}

void	move_left(t_cub *cub)
{
	move_player(cub, cub->player.dir_left);
	put_stamina(cub);
}

void	move_right(t_cub *cub)
{
	move_player(cub, cub->player.dir_right);
	put_stamina(cub);
}

void	move_down(t_cub *cub)
{
	move_player(cub, cub->player.dir_down);
	put_stamina(cub);
}

void	move_up(t_cub *cub)
{
	move_player(cub, cub->player.dir_up);
	put_stamina(cub);
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

int	respawn_doors(t_map *map, int actual_x, int actual_y)
{
	int pos_x = actual_x - 2;
	int pos_y = actual_y - 2;
	if (pos_y < 0)
		pos_y = 0;
	if (pos_x < 0)
		pos_x = 0;
	if (pos_x == 0)
	{
		while (map->map[pos_y][pos_x] && pos_x <= actual_x + 2)
		{
		// debug_nbr(RED, "pos_x :", pos_x);
		// debug_nbr(RED, "pos_y :", pos_y);
			if (map->map[pos_y][pos_x] == 'd')
				return (map->map[pos_y][pos_x] = 'D', 1);
			else
				pos_x++;
		}
		while (map->map[pos_y] && map->map[pos_y][pos_x] && pos_y <= actual_y + 2)
		{
			// debug_nbr(RED, "pos_x :", pos_x);
			// debug_nbr(RED, "pos_y :", pos_y);
			if (map->map[pos_y][pos_x] == 'd')
				return (map->map[pos_y][pos_x] = 'D', 1);
			else
				pos_y++;
		}
		if (!map->map[pos_y])
			pos_y--;
		// debug_nbr(RED, "pos_x :", pos_x);
		// debug_nbr(RED, "pos_y :", pos_y);
		while (map->map[pos_y][pos_x] && pos_x <= actual_x - 2 && pos_x > 0)
		{
			// debug_nbr(RED, "pos_x :", pos_x);
			// debug_nbr(RED, "pos_y :", pos_y);
			if (map->map[pos_y][pos_x] == 'd')
				return (map->map[pos_y][pos_x] = 'D', 1);
			else
				pos_x--;
		}
	}
	else if (pos_y == 0)
	{
		while (map->map[pos_y] && map->map[pos_y][pos_x] && pos_y <= actual_y + 2)
		{
			// debug_nbr(RED, "pos_x :", pos_x);
			// debug_nbr(RED, "pos_y :", pos_y);
			if (map->map[pos_y][pos_x] == 'd')
				return (map->map[pos_y][pos_x] = 'D', 1);
			else
				pos_y++;
		}
		while (map->map[pos_y][pos_x] && pos_x <= actual_x + 2)
		{
			// debug_nbr(RED, "pos_x :", pos_x);
			// debug_nbr(RED, "pos_y :", pos_y);
			if (map->map[pos_y][pos_x] == 'd')
				return (map->map[pos_y][pos_x] = 'D', 1);
			else
				pos_x++;
		}
		while (map->map[pos_y] && map->map[pos_y][pos_x] && pos_y <= actual_y - 2 && pos_y > 0)
		{
			// debug_nbr(RED, "pos_x :", pos_x);
			// debug_nbr(RED, "pos_y :", pos_y);
			if (map->map[pos_y][pos_x] == 'd')
				return (map->map[pos_y][pos_x] = 'D', 1);
			else
				pos_y--;
		}
	}
	else
	{
		while (map->map[pos_y][pos_x] && pos_x <= actual_x + 2)
		{
			// debug_nbr(RED, "pos_x :", pos_x);
			// debug_nbr(RED, "pos_y :", pos_y);
			if (map->map[pos_y][pos_x] == 'd')
				return (map->map[pos_y][pos_x] = 'D', 1);
			else
				pos_x++;
		}
		while (map->map[pos_y] && map->map[pos_y][pos_x] && pos_y <= actual_y - 2 && pos_y > 0)
		{
			// debug_nbr(RED, "pos_x :", pos_x);
			// debug_nbr(RED, "pos_y :", pos_y);
			if (map->map[pos_y][pos_x] == 'd')
				return (map->map[pos_y][pos_x] = 'D', 1);
			else
				pos_y--;
		}
		while (map->map[pos_y][pos_x] && pos_x <= actual_x - 2 && pos_x > 0)
		{
			// debug_nbr(RED, "pos_x :", pos_x);
			// debug_nbr(RED, "pos_y :", pos_y);
			if (map->map[pos_y][pos_x] == 'd')
				return (map->map[pos_y][pos_x] = 'D', 1);
			else
				pos_x--;
		}
		while (map->map[pos_y] && map->map[pos_y][pos_x] && pos_y <= actual_y - 2 && pos_y > 0)
		{
			// debug_nbr(RED, "pos_x :", pos_x);
			// debug_nbr(RED, "pos_y :", pos_y);
			if (map->map[pos_y][pos_x] == 'd')
				return (map->map[pos_y][pos_x] = 'D', 1);
			else
				pos_y--;
		}
	}
	return (0);
}

int open_door(t_cub *cub)
{
	int player_y;
	int player_x;

	player_y = cub->player.pos_y / cub->mini_map.size_wall_y;
	player_x = cub->player.pos_x / cub->mini_map.size_wall_x;
	if (cub->map->map[player_y][player_x + 1] == 'D')
	{
		cub->map->map[player_y][player_x] = cub->map->player_char;
		cub->map->map[player_y][player_x + 1] = 'd';
		return (1);
	}
	if (cub->map->map[player_y + 1][player_x] == 'D')
	{
		cub->map->map[player_y][player_x] = cub->map->player_char;
		cub->map->map[player_y + 1][player_x] = 'd';
		return (1);
	}
	if (cub->map->map[player_y - 1][player_x] == 'D')
	{
		cub->map->map[player_y][player_x] = cub->map->player_char;
		cub->map->map[player_y - 1][player_x] = 'd';
		return (1);
	}
	if (cub->map->map[player_y][player_x - 1] == 'D')
	{
		cub->map->map[player_y][player_x] = cub->map->player_char;
		cub->map->map[player_y][player_x - 1] = 'd';
		return (1);
	}
	if (respawn_doors(cub->map, player_x, player_y) == 1)
		return (1);
	return (0);
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
	if (open_door(cub) == 1)
	{
		mlx_delete_image(cub->mlx, cub->mini_map.background_i);
		map_to_window(cub);
	}
	draw_ray(&cub->ray, &cub->mini_map, cub, H_GREEN);
}

void	ft_hook(void *param)
{
	t_cub	*cub;

	cub = param;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub->mlx);
	cub->anim.time += cub->mlx->delta_time;
	if (cub->anim.time > 0.03)
	{
		move(cub);
		refresh(cub);
		cub->anim.time = 0;
	}
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

void	fog(t_cub *cub)
{
	int x = 0;
	int y = 0;
	int opacity = 255;
	int calc_x;
	int calc_y;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (x % 4 == 0 || y % 4 == 0)
			{
				if (x >= WIDTH / 2)
				{
					calc_x = x - WIDTH / 2;
				}
				else
					calc_x = WIDTH / 2 - x;
				if (y > HEIGHT / 2)
					calc_y = y - HEIGHT / 2;
				else 
					calc_y = HEIGHT / 2 - y;
				opacity = sqrt(calc_x * calc_x + calc_y * calc_y);
				opacity /= 4;
			}
			if (opacity > 240)
				opacity = 240;
			if (opacity < 0)
				opacity = 0;
			// debug_nbr(GREEN, "opacity :", opacity);
			mlx_put_pixel(cub->world.fog, x, y, opacity);
			x++;
		}
		y++;
	}
}

void	open_window(t_cub *cub)
{
	init_data_mini_map(&cub->mini_map, cub->map);
	set_player_pos(cub);
	set_enemy_pos(cub);
	cub->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!cub->mlx)
		exit((ft_printf("Error\nInitializing MLX!\n"), EXIT_FAILURE));
	mlx_set_window_pos(cub->mlx, 500, 250);
	mlx_set_window_limit(cub->mlx, WIDTH, HEIGHT, WIDTH, HEIGHT);
	cub->anim.time = 0;
	cub->anim.count = 0;
	cub->anim.i_no = 0;
	cub->anim.i_so = 0;
	cub->anim.i_we = 0;
	cub->anim.i_ea = 0;
	cub->anim.b_no = false;
	cub->anim.b_so = false;
	cub->anim.b_we = false;
	cub->anim.b_ea = false;
	ft_cursor(cub);
	init_raycast(cub);
	lets_go_3d(cub);
	raycasting(cub);
	map_to_window(cub);
	draw_ray(&cub->ray, &cub->mini_map, cub, H_GREEN);
	mlx_set_mouse_pos(cub->mlx, WIDTH / 2, HEIGHT / 2);
	fog(cub);
	mlx_loop_hook(cub->mlx, ft_hook, (void *)cub);	
	mlx_cursor_hook(cub->mlx, rotations, (void *)cub);
	mlx_loop(cub->mlx);
	mlx_terminate(cub->mlx);
}

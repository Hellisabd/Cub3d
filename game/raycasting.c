#include "../cub3D.h"

void	print_map(t_cub *cub)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < (size_t)cub->map->height)
	{
		j = 0;
		while (j < ft_strlen(cub->map->map[i]))
		{
			if (cub->map->map[i][j] == '1')
				printf("%s%c%s", RED, cub->map->map[i][j], NC);
			else if (cub->map->map[i][j] == '0')
				printf("%s%c%s", BLUE, cub->map->map[i][j], NC);
			else if (cub->map->map[i][j] == 'P')
				printf("%s%c%s", GREEN, cub->map->map[i][j], NC);
			else 
				printf("%s%c%s", YELLOW, cub->map->map[i][j], NC);
			j++;
		}
		i++;
	}
	printf("\n");
}

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

float	calc_ray_y(float dist_y, t_cub *cub)
{
	float	next;

	next = dist_y / sin(cub->angle);
	return (next);
}

float	calc_ray_x(float dist_x, t_cub *cub)
{
	float	next;

	next = dist_x / cos(cub->angle);
	return (next);
}

void	draw_ray(t_ray **ray, t_mini_map *mini_map, t_cub *cub, int color)
{
	int y;
	int x;

	x = 0;
	y = 0;
	// mini_map->background_i = mlx_new_image(cub->mlx, cub->mini_map.width, cub->mini_map.height);
	while (y != cub->mini_map.height)
	{
		x = 0;
		while (x != cub->mini_map.width)
		{
			mlx_put_pixel(mini_map->background_i, x, y, 0xFFFFFFFF);
			x++;
		}
		y++;
	}
	t_ray *tmp;
	while (*ray)
	{
		drawline(*ray, mini_map, &cub->player, color);
		tmp = *ray;
		*ray = (*ray)->next;
		free(tmp);
	}
	ray = NULL;
	// mlx_image_to_window(cub->mlx, mini_map->background_i, 0, 0);
	// mlx_set_instance_depth(mini_map->background_i->instances, depth++);
}

void	raycasting(t_cub *cub)
{
	int		i;
	int		j;
	// float		dist_hyp_x;
	// float		dist_hyp_y;
	// bool	incr_y;
	// bool	incr_x;

	// incr_x = false;
	// incr_y = false;

	// debug_float(RED, "p_x :", cub->p_x);
	// debug_nbr(GREEN, "player pos_x :", cub->player.pos_x);
	// debug_float(RED, "p_y :", cub->p_y);
	// debug_nbr(GREEN, "player pos_y :", cub->player.pos_y);
	// debug_float(BLUE, "trying to ind good res :", cub->player.pos_x / cub->mini_map.size_wall_x + (cub->p_x - fabs(floor(cub->p_x))));
	cub->p_x = 0.5 + (float)cub->player.pos_x / (float)cub->mini_map.size_wall_x;
	cub->p_y =  0.5 +(float)cub->player.pos_y / (float)cub->mini_map.size_wall_y;
	if (cub->rot > 2 * PI)
		cub->rot -= 2 * PI;
	if (cub->rot < -2 * PI)
		cub ->rot += 2 * PI;
	cub->fov = PI * 66 / 180;
	cub->angle = -cub->fov / 2;
	cub->angle += cub->rot;
	cub->n = 10.00001;
	while (cub->angle <= ((cub->fov / 2) + cub->rot))
	{
		i = floor(cub->p_y);
		j = floor(cub->p_x);
		if ((cub->angle < 0 && cub->angle > -PI) || (cub->angle > PI && cub->angle < 2 * PI))
			cub->dist_y = fabs(ceil(cub->p_y)) - cub->p_y;
		else
			cub->dist_y = fabs(floor(cub->p_y)) - cub->p_y;
		if ((cub->angle > PI / 2 && cub->angle < 3 * PI / 2) || (cub->angle > -3 * PI / 2 && cub->angle < -PI / 2))
			cub->dist_x = fabs(floor(cub->p_x)) - cub->p_x;
		else
			cub->dist_x = fabs(ceil(cub->p_x)) - cub->p_x;
		cub->next_x =  calc_ray_x(fabs(cub->dist_x), cub);
		// dist_hyp_x = cub->next_x;
		cub->next_y =  calc_ray_y(fabs(cub->dist_y), cub);
		// dist_hyp_y = cub->next_y;
		printf("%sangle: %f | dist_x: %f | dist_y: %f%s\n", BLUE, cub->angle, cub->dist_x, cub->dist_y, NC);
		// debug_float(GREEN, "next_x", cub->next_x);
		// debug_float(GREEN, "next_y", cub->next_y);
		while (cub->map->map[i][j] == '0' || cub->map->map[i][j] == cub->map->player_char)
		{
			if (cub->dist_x < 0 && cub->dist_y < 0) //2eme quadrant
			{
				// debug_str(RED, NULL, "2eme quadrant");
				if (fabs(cub->next_x) <= fabs(cub->next_y))
				{
					// incr_x = true;
					j--;
					// dist_hyp_x = cub->dist_x;
					cub->dist_x -= 1;
					cub->hyp = cub->next_x;
					cub->next_x = calc_ray_x((cub->dist_x), cub);
				}
				else
				{
					// incr_y = true;
					i--;
					// dist_hyp_y = cub->dist_y;
					cub->dist_y -= 1;
					cub->hyp = cub->next_y;
					cub->next_y = calc_ray_y((cub->dist_y), cub);
				}
			}
			else if (cub->dist_x < 0 && cub->dist_y > 0) //3eme quadrant
			{
				// debug_str(RED, NULL, "3eme quadrant");
				if (fabs(cub->next_x) <= fabs(cub->next_y))
				{
					// incr_x = true;
					j--;
					// dist_hyp_x = cub->dist_x;
					cub->dist_x -= 1;
					cub->hyp = cub->next_x;
					cub->next_x = calc_ray_x((cub->dist_x), cub);
				}
				else
				{
					// incr_y = true;
					i++;
					// dist_hyp_y = cub->dist_y;
					cub->dist_y += 1;
					cub->hyp = cub->next_y;
					cub->next_y = calc_ray_y((cub->dist_y), cub);
				}
			}
			else if (cub->dist_x > 0 && cub->dist_y > 0) //4eme quadrant
			{
				// debug_str(RED, NULL, "4eme quadrant");
				if (fabs(cub->next_x) <= fabs(cub->next_y))
				{
					// incr_x = true;
					j++;
					// dist_hyp_x = cub->dist_x;
					cub->dist_x += 1;
					cub->hyp = cub->next_x;
					cub->next_x = calc_ray_x((cub->dist_x), cub);
				}
				else
				{
					// incr_y = true;
					i++;
					// dist_hyp_y = cub->dist_y;
					cub->dist_y += 1;
					cub->hyp = cub->next_y;
					cub->next_y = calc_ray_y((cub->dist_y), cub);
				}
			}
			else if (cub->dist_x > 0 && cub->dist_y < 0) //1er quadrant 
			{
				// debug_str(RED, NULL, "1er quadrant");
				if (fabs(cub->next_x) <= fabs(cub->next_y))
				{
					// incr_x = true;
					j++;
					// dist_hyp_x = cub->dist_x;
					cub->dist_x += 1;
					cub->hyp = cub->next_x;
					cub->next_x = calc_ray_x((cub->dist_x), cub);
				}
				else
				{
					// incr_y = true;
					i--;
					// dist_hyp_y = cub->dist_y;
					cub->dist_y -= 1;
					cub->hyp = cub->next_y;
					cub->next_y = calc_ray_y((cub->dist_y), cub);
				}
			}
			// if (x == angle 0 && dist_y > 0)
			// if (cub->dist_y < 0 && fabs(cub->next_x) >= fabs(cub->next_y))
			// {
			// 	if ((cub->angle > PI / 2 && cub->angle < 3 * PI / 2) || (cub->angle < -PI / 2 && cub->angle > -3 * PI / 2))
			// 	{
			// 		i--;
			// 		cub->dist_y -= 1;
			// 		cub->hyp = cub->next_y;
			// 		cub->next_y = -calc_ray_y(cub->dist_y, cub);
			// 	}
			// 	else
			// 	{
			// 		i++;
			// 		cub->dist_y -= 1;
			// 		cub->hyp = cub->next_y;
			// 		cub->next_y = calc_ray_y(cub->dist_y, cub);
			// 	}
			// }
			// else if (cub->dist_y > 0 && fabs(cub->next_x) >= fabs(cub->next_y))
			// {
			// 	if ((cub->angle > PI / 2 && cub->angle < 3 * PI / 2) || (cub->angle < -PI / 2 && cub->angle > -3 * PI / 2))
			// 	{
			// 		i--;
			// 		cub->dist_y += 1;
			// 		cub->hyp = cub->next_y;
			// 		cub->next_y = -calc_ray_y(cub->dist_y, cub);
			// 	}
			// 	else
			// 	{
			// 		i++;
			// 		cub->dist_y += 1;
			// 		cub->hyp = cub->next_y;
			// 		cub->next_y = calc_ray_y(cub->dist_y, cub);
			// 	}
			// }
			// else if (cub->dist_x < 0 && fabs(cub->next_y) >= fabs(cub->next_x))
			// {
			// 	if ((cub->angle < 0 && cub->angle > -PI) || (cub->angle > PI && cub->angle < 2 * PI))
			// 	{
			// 		j--;
			// 		cub->dist_x -= 1;
			// 		cub->hyp = cub->next_x;
			// 		cub->next_x = -calc_ray_x(cub->dist_x, cub);
			// 	}
			// 	else
			// 	{
			// 		j++;
			// 		cub->dist_x -= 1;
			// 		cub->hyp = cub->next_x;
			// 		cub->next_x = calc_ray_x(cub->dist_x, cub);
			// 	}
			// }
			// else if (cub->dist_x > 0 && fabs(cub->next_y) >= fabs(cub->next_x))
			// {
			// 	if ((cub->angle < 0 && cub->angle > -PI) || (cub->angle > PI && cub->angle < 2 * PI))
			// 	{
			// 		j++;
			// 		cub->dist_x += 1;
			// 		cub->hyp = cub->next_x;
			// 		cub->next_x = calc_ray_x(cub->dist_x, cub);
			// 	}
			// 	else
			// 	{
			// 		j--;
			// 		cub->dist_x += 1;
			// 		cub->hyp = cub->next_x;
			// 		cub->next_x = -calc_ray_x(cub->dist_x, cub);
			// 	}
			// }
		}
		if (round(cub->angle * 10000) == 0 || round(cub->angle * 10000) == round(10000 * PI))
			cub->y = cub->p_y;
		else
			cub->y = (cub->p_y) + sin(cub->angle) * fabs(cub->hyp);
			// cub->y = (cub->p_y) + dist_hyp_y;
		if (round(cub->angle * 10000) == round(10000 *PI / 2) || round(cub->angle * 10000) == round(10000 * 3 *PI / 2))
			cub->x = cub->p_x;
		else
			cub->x = (cub->p_x) + cos(cub->angle) * fabs(cub->hyp);
			// cub->x = (cub->p_x) + dist_hyp_x;
		ft_add_back_raycast(&cub->ray, cub, cub->x, cub->y);
		cub->angle += cub->fov / cub->n;
	}
	debug_float(RED, "rot: ", cub->rot);
	// debug_float(RED, "next_x", cub->next_x);
	// debug_float(RED, "next_y", cub->next_y);
	// debug_float(RED, "pos_x", cub->p_x);
	// debug_float(RED, "pos_y ", cub->p_y);
	debug_float(YELLOW, "PI/2 = ", PI / 2);
	debug_float(YELLOW, "PI = ", PI);
	debug_float(YELLOW, "3PI/2 = ", 3 * PI / 2);
	debug_float(YELLOW, "2PI = ", 2 * PI);
	// debug_float(BLUE, "dist_x: ", cub->dist_x);
	// debug_float(BLUE, "dist_y: ", cub->dist_y);
	// debug_float(BLUE, "dist_hyp_x: ", dist_hyp_x);
	// debug_float(BLUE, "dist_hyp_y: ", dist_hyp_y);
	printlist((cub->ray), GREEN);
	printf("\n");
}

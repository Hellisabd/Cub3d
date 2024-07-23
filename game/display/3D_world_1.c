/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3D_world_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:57:09 by amirloup          #+#    #+#             */
/*   Updated: 2024/07/23 10:35:38 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	put_wall_in3d(t_wall *wall, t_cub *cub, mlx_image_t *image, \
	int **pixel_tab)
{
	int		column_tab;
	float	line_tab;
	int		start;

	if (wall->side == 1)
		wall->ratio_width = wall->ray->y - floor(wall->ray->y);
	else
		wall->ratio_width = wall->ray->x - floor(wall->ray->x);
	wall->ratio_height = (float)image->height / (float)wall->img_height;
	start = (wall->img_height - HEIGHT) / 2;
	if (start < 0)
		start = 0;
	line_tab = start * wall->ratio_height;
	column_tab = (int)(wall->ratio_width * image->width) - 1;
	if (column_tab < 0)
		column_tab = 0;
	while ((int)floor(line_tab) < (int)image->height && wall->y < HEIGHT)
	{
		mlx_put_pixel(cub->world.background_i, wall->x, wall->y, \
		(int)pixel_tab[column_tab][(int)floor(line_tab)]);
		wall->y++;
		line_tab += wall->ratio_height;
	}
}

void	disp_world(t_cub *cub, t_ray *ray, int x)
{
	t_wall	wall;

	wall.y = 0;
	wall.ray = ray;
	wall.img_height = (int)(HEIGHT / ray->hyp * cos(ray->angle - cub->rot));
	wall.x = x;
	while (wall.y <= (HEIGHT - wall.img_height) / 2)
	{
		mlx_put_pixel(cub->world.background_i, x, wall.y, cub->map->c_h);
		wall.y++;
	}
	if (ray->door)
	{
		put_wall_in3d(&wall, cub, cub->world.door_i[0], \
			cub->world.tab_anim_door[0]);
		ray->door = false;
	}
	disp_world_2(cub, ray, &wall);
	while (wall.y < HEIGHT)
	{
		mlx_put_pixel(cub->world.background_i, x, wall.y, cub->map->f_h);
		wall.y++;
	}
}

int	draw_walls(t_cub *cub, t_ray *ray)
{
	int	ratio;
	int	i;

	i = 0;
	ratio = WIDTH / cub->n;
	cub->n_ray = 0;
	cub->exit.n_ray = 0;
	if (cub->n_enemy == 1)
		maths_enemy(cub);
	if (cub->n_exit == 1)
		maths_exit(cub);
	while (i < WIDTH && ray)
	{
		if (i % ratio == 0)
		{
			ray = ray->next;
			if (!ray)
				break ;
		}
		disp_world(cub, ray, i);
		if (cub->n_exit == 1)
			put_exit(cub, ray, i);
		if (cub->n_enemy == 1)
			put_enemy(cub, ray, i);
		i++;
	}
	return (0);
}

int	lets_go_3d(t_cub *cub)
{
	init_world(cub);
	if (cub->n_enemy == 1)
		init_enemy(cub);
	init_blink(cub);
	init_death(cub);
	if (cub->n_exit == 1)
		init_exit(cub);
	cub->world.background_i = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (mlx_image_to_window(cub->mlx, cub->world.background_i, 0, 0) == -1)
		exit((print_error(WINDOW), free_in_window(cub), EXIT_FAILURE));
	cub->world.npc = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (mlx_image_to_window(cub->mlx, cub->world.npc, 0, 0) == -1)
		exit((print_error(WINDOW), free_in_window(cub), EXIT_FAILURE));
	cub->world.fog = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (mlx_image_to_window(cub->mlx, cub->world.fog, 0, 0) == -1)
		exit((print_error(WINDOW), free_in_window(cub), EXIT_FAILURE));
	cub->world.hud = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (mlx_image_to_window(cub->mlx, cub->world.hud, 0, 0) == -1)
		exit((print_error(WINDOW), free_in_window(cub), EXIT_FAILURE));
	return (0);
}

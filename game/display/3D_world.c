/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3D_world.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:57:09 by amirloup          #+#    #+#             */
/*   Updated: 2024/07/11 15:17:40 by amirloup         ###   ########.fr       */
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
	if ((int)round(ray->x * 100000) % 100000 == 0 && \
		(int)round(ray->y * 100000) % 100000 != 0)
	{
		wall.side = 1;
		if (ray->x > cub->p_x)
		{
			if (cub->map->map[(int)floor(ray->y)][(int)round(ray->x)] == 'D')
				put_wall_in3d(&wall, cub, cub->world.door_i[0], \
				cub->world.tab_anim_door[0]);
			else if (cub->map->map[(int)floor(ray->y)] \
					[(int)round(ray->x)] == 'd')
				put_wall_in3d(&wall, cub, \
					cub->world.door_i[cub->anim.door_count], \
					cub->world.tab_anim_door[cub->anim.door_count]);
			else
				put_wall_in3d(&wall, cub, cub->world.ea_i, cub->world.tab_ea);
		}
		else
		{
			if ((int)ray->x != 0 && \
				cub->map->map[(int)floor(ray->y)][(int)round(ray->x) \
				- 1] == 'D')
				put_wall_in3d(&wall, cub, cub->world.door_i[0], \
					cub->world.tab_anim_door[0]);
			else if ((int)ray->x != 0 && \
				cub->map->map[(int)floor(ray->y)][(int)round(ray->x) \
				- 1] == 'd')
				put_wall_in3d(&wall, cub, \
					cub->world.door_i[cub->anim.door_count], \
					cub->world.tab_anim_door[cub->anim.door_count]);
			else
				put_wall_in3d(&wall, cub, cub->world.we_i, cub->world.tab_we);
		}
	}
	else if ((int)round(ray->y * 100000) % 100000 == 0 && \
		(int)round(ray->x * 100000) % 100000 != 0)
	{
		wall.side = 0;
		if (ray->y > cub->p_y)
		{
			if (cub->map->map[(int)round(ray->y) + 1] && \
				cub->map->map[(int)round(ray->y)][(int)floor(ray->x)] == 'D')
				put_wall_in3d(&wall, cub, cub->world.door_i[0], \
					cub->world.tab_anim_door[0]);
			else if (cub->map->map[(int)round(ray->y) + 1] && \
				cub->map->map[(int)round(ray->y)][(int)floor(ray->x)] == 'd')
				put_wall_in3d(&wall, cub, \
					cub->world.door_i[cub->anim.door_count], \
					cub->world.tab_anim_door[cub->anim.door_count]);
			else
				put_wall_in3d(&wall, cub, cub->world.so_i, cub->world.tab_so);
		}
		else
		{
			if (ray->y > 1 && \
				cub->map->map[(int)round(ray->y) - 1][(int)floor(ray->x)] \
				== 'D')
				put_wall_in3d(&wall, cub, cub->world.door_i[0], \
					cub->world.tab_anim_door[0]);
			else if (ray->y > 1 && \
				cub->map->map[(int)round(ray->y) - 1][(int)floor(ray->x)] \
				== 'd')
				put_wall_in3d(&wall, cub, \
					cub->world.door_i[cub->anim.door_count], \
					cub->world.tab_anim_door[cub->anim.door_count]);
			else
				put_wall_in3d(&wall, cub, cub->world.no_i, cub->world.tab_no);
		}
	}
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
	maths_enemy(cub);
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
		if (cub->n_enemy == 1)
			put_enemy(cub, ray, i);
		if (cub->n_exit)
			put_exit(cub, ray, i);
		i++;
	}
	return (0);
}

int	lets_go_3d(t_cub *cub)
{
	init_world(cub);
	init_enemy(cub);
	init_blink(cub);
	init_death(cub);
	init_exit(cub);
	cub->world.background_i = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (mlx_image_to_window(cub->mlx, cub->world.background_i, 0, 0) == -1)
		exit (1);
	cub->world.exit = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (mlx_image_to_window(cub->mlx, cub->world.exit, 0, 0) == -1)
		exit (1);
	cub->world.npc = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (mlx_image_to_window(cub->mlx, cub->world.npc, 0, 0) == -1)
		exit (1);
	cub->world.fog = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (mlx_image_to_window(cub->mlx, cub->world.fog, 0, 0) == -1)
		exit (1);
	cub->world.hud = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (mlx_image_to_window(cub->mlx, cub->world.hud, 0, 0) == -1)
		exit (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:38:26 by amirloup          #+#    #+#             */
/*   Updated: 2024/07/22 12:06:31 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	maths_enemy_2(t_cub *cub)
{
	cub->enemy.max_rays = (int)(fabs(cub->enemy.theta1 - cub->enemy.theta2) / \
		(cub->fov / cub->n));
	cub->enemy.ratio_width = (float)cub->enemy.enemy_i[0]->width / \
		(float)cub->enemy.max_rays;
	cub->enemy.start = ((int)cub->enemy.ratio - HEIGHT) / 2;
	if (cub->enemy.start < 0)
		cub->enemy.start = 0;
}

void	maths_enemy(t_cub *cub)
{
	cub->enemy.d_x = cub->p_x - cub->e_x;
	cub->enemy.d_y = cub->p_y - cub->e_y;
	cub->enemy.dist = fabs(sqrt((cub->enemy.d_x * cub->enemy.d_x) + \
		(cub->enemy.d_y * cub->enemy.d_y)));
	cub->enemy.ratio = HEIGHT / cub->enemy.dist;
	cub->enemy.ratio_height = (float)cub->enemy.enemy_i[0]->height / \
		cub->enemy.ratio;
	if (cub->p_x >= cub->e_x && cub->p_y >= cub->e_y)
		cub->enemy.angle = PI + acosf(fabs(cub->enemy.d_x) / cub->enemy.dist);
	else if (cub->p_x <= cub->e_x && cub->p_y >= cub->e_y)
		cub->enemy.angle = 3 * PI / 2 + acosf(fabs(cub->enemy.d_y) / \
			cub->enemy.dist);
	else if (cub->p_x <= cub->e_x && cub->p_y <= cub->e_y)
		cub->enemy.angle = 2 * PI + acosf(fabs(cub->enemy.d_x) / \
			cub->enemy.dist);
	else if (cub->p_x >= cub->e_x && cub->p_y <= cub->e_y)
		cub->enemy.angle = PI / 2 + acosf(fabs(cub->enemy.d_y) / \
			cub->enemy.dist);
	if (cub->enemy.angle >= 2 * PI)
		cub->enemy.angle -= 2 * PI;
	if (cub->enemy.angle <= -2 * PI)
		cub->enemy.angle += 2 * PI;
	cub->enemy.theta1 = cub->enemy.angle - atanf(0.5 / cub->enemy.dist);
	cub->enemy.theta2 = cub->enemy.angle + atanf(0.5 / cub->enemy.dist);
	maths_enemy_2(cub);
}

void	clear_npc_layer(t_cub *cub, int x)
{
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		mlx_put_pixel(cub->world.npc, x, y, 0);
		y++;
	}
}

void	put_enemy_2(t_cub *cub, int x, int y)
{
	while (y < HEIGHT)
	{
		mlx_put_pixel(cub->world.npc, x, y, 0);
		y++;
	}
	cub->n_ray++;
	if (cub->n_ray >= cub->enemy.max_rays * 3)
		cub->n_ray = 0;
}

void	put_enemy(t_cub *cub, t_ray *ray, int x)
{
	int	y;

	cub->enemy.line_tab = cub->enemy.start * cub->enemy.ratio_height;
	if ((ray->hyp > cub->enemy.dist) && ((ray->angle >= cub->enemy.theta1 && \
		ray->angle <= cub->enemy.theta2) || (ray->angle >= cub->enemy.theta1 \
		- 2 * PI && ray->angle <= cub->enemy.theta2 - 2 * PI)))
	{
		y = 0;
		while (y < (HEIGHT - cub->enemy.ratio + 50) / 2)
		{
			mlx_put_pixel(cub->world.npc, x, y, 0);
			y++;
		}
		while ((int)floor(cub->enemy.line_tab) < \
			(int)cub->enemy.enemy_i[0]->height && y < HEIGHT)
		{
			mlx_put_pixel(cub->world.npc, x, y, \
				(int)cub->enemy.pix_enemy[(int)(floor)(cub->n_ray / 3 * \
				cub->enemy.ratio_width)][(int)floor(cub->enemy.line_tab)]);
			y++;
			cub->enemy.line_tab += cub->enemy.ratio_height;
		}
		put_enemy_2(cub, x, y);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:35:09 by amirloup          #+#    #+#             */
/*   Updated: 2024/07/22 12:08:28 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	maths_exit_2(t_cub *cub)
{
	cub->exit.max_rays = (int)(fabs(cub->exit.theta1 - cub->exit.theta2) / \
		(cub->fov / cub->n));
	cub->exit.ratio_width = (float)cub->exit.exit_i->width / \
		(float)cub->exit.max_rays;
	cub->exit.start = ((int)cub->exit.ratio - HEIGHT) / 2;
	if (cub->exit.start < 0)
		cub->exit.start = 0;
}

void	maths_exit(t_cub *cub)
{
	cub->exit.d_x = cub->p_x - cub->exit.e_x;
	cub->exit.d_y = cub->p_y - cub->exit.e_y;
	cub->exit.dist = fabs(sqrt((cub->exit.d_x * cub->exit.d_x) + \
		(cub->exit.d_y * cub->exit.d_y)));
	cub->exit.ratio = HEIGHT / cub->exit.dist;
	cub->exit.ratio_height = (float)cub->exit.exit_i->height / \
		cub->exit.ratio;
	if (cub->p_x >= cub->exit.e_x && cub->p_y >= cub->exit.e_y)
		cub->exit.angle = PI + acosf(fabs(cub->exit.d_x) / cub->exit.dist);
	else if (cub->p_x <= cub->exit.e_x && cub->p_y >= cub->exit.e_y)
		cub->exit.angle = 3 * PI / 2 + acosf(fabs(cub->exit.d_y) / \
			cub->exit.dist);
	else if (cub->p_x <= cub->exit.e_x && cub->p_y <= cub->exit.e_y)
		cub->exit.angle = 2 * PI + acosf(fabs(cub->exit.d_x) / \
			cub->exit.dist);
	else if (cub->p_x >= cub->exit.e_x && cub->p_y <= cub->exit.e_y)
		cub->exit.angle = PI / 2 + acosf(fabs(cub->exit.d_y) / \
			cub->exit.dist);
	if (cub->exit.angle >= 2 * PI)
		cub->exit.angle -= 2 * PI;
	if (cub->exit.angle <= -2 * PI)
		cub->exit.angle += 2 * PI;
	cub->exit.theta1 = cub->exit.angle - atanf(0.5 / cub->exit.dist);
	cub->exit.theta2 = cub->exit.angle + atanf(0.5 / cub->exit.dist);
	maths_exit_2(cub);
}

void	put_exit_2(t_cub *cub, int x, int y)
{
	while (y < HEIGHT)
	{
		mlx_put_pixel(cub->world.npc, x, y, 0);
		y++;
	}
	cub->exit.n_ray++;
	if (cub->exit.n_ray >= cub->exit.max_rays * 3)
		cub->exit.n_ray = 0;
}

void	put_exit(t_cub *cub, t_ray *ray, int x)
{
	int	y;

	clear_npc_layer(cub, x);
	cub->exit.line_tab = cub->exit.start * cub->exit.ratio_height;
	if ((ray->hyp > cub->exit.dist) && ((ray->angle >= cub->exit.theta1 && \
		ray->angle <= cub->exit.theta2) || (ray->angle >= cub->exit.theta1 \
		- 2 * PI && ray->angle <= cub->exit.theta2 - 2 * PI)))
	{
		y = 0;
		while (y < (HEIGHT - cub->exit.ratio + 50) / 2)
		{
			mlx_put_pixel(cub->world.npc, x, y, 0);
			y++;
		}
		while ((int)floor(cub->exit.line_tab) < \
			(int)cub->exit.exit_i->height && y < HEIGHT)
		{
			mlx_put_pixel(cub->world.npc, x, y, \
				(int)cub->exit.tab_exit[(int)(floor)(cub->exit.n_ray / 3 * \
				cub->exit.ratio_width)][(int)floor(cub->exit.line_tab)]);
			y++;
			cub->exit.line_tab += cub->exit.ratio_height;
		}
		put_exit_2(cub, x, y);
	}
}

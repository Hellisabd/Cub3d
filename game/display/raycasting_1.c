/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:23:30 by amirloup          #+#    #+#             */
/*   Updated: 2024/07/12 10:13:54 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	raycasting_4(t_cub *cub, int *i, int *j)
{
	if (cub->dist_x < 0 && cub->dist_y < 0)
		third_quadrant(cub, i, j);
	else if (cub->dist_x < 0 && cub->dist_y > 0)
		second_quadrant(cub, i, j);
	else if (cub->dist_x > 0 && cub->dist_y > 0)
		first_quadrant(cub, i, j);
	else if (cub->dist_x > 0 && cub->dist_y < 0)
		fourth_quadrant(cub, i, j);
}

void	raycasting_3(t_cub *cub)
{
	if ((cub->angle >= PI / 2 && cub->angle <= 3 * PI / 2) || \
		(cub->angle >= -3 * PI / 2 && cub->angle <= -PI / 2))
	{
		cub->dist_x = fabs(floor(cub->p_x)) - cub->p_x;
		if (cub->dist_x == 0.000000)
			cub->dist_x = -1;
	}
	else
	{
		cub->dist_x = fabs(ceil(cub->p_x)) - cub->p_x;
		if (cub->dist_x == 0.000000)
			cub->dist_x = 1;
	}
	cub->next_x = calc_ray_x(fabs(cub->dist_x), cub);
	cub->next_y = calc_ray_y(fabs(cub->dist_y), cub);
}

void	raycasting_2(t_cub *cub)
{
	if ((cub->angle >= 0 && cub->angle <= PI) || \
		(cub->angle >= -2 * PI && cub->angle <= -PI))
	{
		cub->dist_y = fabs(ceil(cub->p_y)) - cub->p_y;
		if (cub->dist_y == 0.000000)
			cub->dist_y = 1;
	}
	else
	{
		cub->dist_y = fabs(floor(cub->p_y)) - cub->p_y;
		if (cub->dist_y == 0.000000)
			cub->dist_y = -1;
	}
}

void	init_raycasting(t_cub *cub)
{
	if (cub->rot >= 2 * PI)
		cub->rot -= 2 * PI;
	if (cub->rot <= -2 * PI)
		cub ->rot += 2 * PI;
	cub->fov = PI * 66 / 180;
	cub->angle = -cub->fov / 2;
	cub->angle += cub->rot;
	cub->n = 1000.00001;
}

void	raycasting(t_cub *cub)
{
	int		i;
	int		j;

	init_raycasting(cub);
	while (cub->angle <= ((cub->fov / 2) + cub->rot))
	{
		i = floor(cub->p_y);
		j = floor(cub->p_x);
		raycasting_2(cub);
		raycasting_3(cub);
		while (cub->map->map[i][j] == '0' || cub->map->map[i][j] == \
			cub->map->player_char || cub->map->map[i][j] == 'o' \
			|| cub->map->map[i][j] == 'A' || cub->map->map[i][j] == 'X')
			raycasting_4(cub, &i, &j);
		cub->y = (cub->p_y) + sin(cub->angle) * fabs(cub->hyp);
		cub->x = (cub->p_x) + cos(cub->angle) * fabs(cub->hyp);
		ft_add_back_raycast(&cub->ray, cub, cub->x, cub->y);
		cub->angle += cub->fov / cub->n;
	}
	draw_walls(cub, cub->ray);
}

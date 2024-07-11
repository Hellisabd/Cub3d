/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:23:30 by amirloup          #+#    #+#             */
/*   Updated: 2024/07/11 15:28:27 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

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
	int		y;
	int		x;
	t_ray	*tmp;

	x = 0;
	y = 0;
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
	while (*ray)
	{
		drawline(*ray, mini_map, &cub->player, color);
		tmp = *ray;
		*ray = (*ray)->next;
		free(tmp);
	}
	ray = NULL;
}

void	raycasting(t_cub *cub)
{
	int		i;
	int		j;

	if (cub->rot >= 2 * PI)
		cub->rot -= 2 * PI;
	if (cub->rot <= -2 * PI)
		cub ->rot += 2 * PI;
	cub->fov = PI * 66 / 180;
	cub->angle = -cub->fov / 2;
	cub->angle += cub->rot;
	cub->n = 1000.00001;
	while (cub->angle <= ((cub->fov / 2) + cub->rot))
	{
		i = floor(cub->p_y);
		j = floor(cub->p_x);
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
		while (cub->map->map[i][j] == '0' || cub->map->map[i][j] == \
			cub->map->player_char || cub->map->map[i][j] == 'o' \
			|| cub->map->map[i][j] == 'A' || cub->map->map[i][j] == 'X')
		{
			if (cub->dist_x < 0 && cub->dist_y < 0)
			{
				if (fabs(cub->next_x) <= fabs(cub->next_y))
				{
					j--;
					cub->dist_x -= 1;
					cub->hyp = cub->next_x;
					cub->next_x = calc_ray_x((cub->dist_x), cub);
				}
				else
				{
					i--;
					cub->dist_y -= 1;
					cub->hyp = cub->next_y;
					cub->next_y = calc_ray_y((cub->dist_y), cub);
				}
			}
			else if (cub->dist_x < 0 && cub->dist_y > 0)
			{
				if (fabs(cub->next_x) <= fabs(cub->next_y))
				{
					j--;
					cub->dist_x -= 1;
					cub->hyp = cub->next_x;
					cub->next_x = calc_ray_x((cub->dist_x), cub);
				}
				else
				{
					i++;
					cub->dist_y += 1;
					cub->hyp = cub->next_y;
					cub->next_y = calc_ray_y((cub->dist_y), cub);
				}
			}
			else if (cub->dist_x > 0 && cub->dist_y > 0)
			{
				if (fabs(cub->next_x) <= fabs(cub->next_y))
				{
					j++;
					cub->dist_x += 1;
					cub->hyp = cub->next_x;
					cub->next_x = calc_ray_x((cub->dist_x), cub);
				}
				else
				{
					i++;
					cub->dist_y += 1;
					cub->hyp = cub->next_y;
					cub->next_y = calc_ray_y((cub->dist_y), cub);
				}
			}
			else if (cub->dist_x > 0 && cub->dist_y < 0)
			{
				if (fabs(cub->next_x) <= fabs(cub->next_y))
				{
					j++;
					cub->dist_x += 1;
					cub->hyp = cub->next_x;
					cub->next_x = calc_ray_x((cub->dist_x), cub);
				}
				else
				{
					i--;
					cub->dist_y -= 1;
					cub->hyp = cub->next_y;
					cub->next_y = calc_ray_y((cub->dist_y), cub);
				}
			}
		}
		cub->y = (cub->p_y) + sin(cub->angle) * fabs(cub->hyp);
		cub->x = (cub->p_x) + cos(cub->angle) * fabs(cub->hyp);
		ft_add_back_raycast(&cub->ray, cub, cub->x, cub->y);
		cub->angle += cub->fov / cub->n;
	}
	draw_walls(cub, cub->ray);
}

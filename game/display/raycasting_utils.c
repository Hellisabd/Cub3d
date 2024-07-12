/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:40:04 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/07/12 09:53:52 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

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

void	ft_add_back_raycast(t_ray **ray, t_cub *cub, float x, float y)
{
	t_ray	*tmp;
	t_ray	*new;

	new = malloc(sizeof(t_ray));
	if (!new)
		exit(EXIT_FAILURE);
	new->angle = cub->angle;
	new->hyp = fabs(cub->hyp);
	new->x = x;
	new->y = y;
	new->door = false;
	new->next = NULL;
	if (ray == NULL || *ray == NULL)
	{
		*ray = new;
		return ;
	}
	tmp = *ray;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new;
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

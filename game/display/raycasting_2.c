/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 10:01:47 by amirloup          #+#    #+#             */
/*   Updated: 2024/07/12 10:10:52 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	first_quadrant(t_cub *cub, int *i, int *j)
{
	if (fabs(cub->next_x) <= fabs(cub->next_y))
	{
		(*j)++;
		cub->dist_x += 1;
		cub->hyp = cub->next_x;
		cub->next_x = calc_ray_x((cub->dist_x), cub);
	}
	else
	{
		(*i)++;
		cub->dist_y += 1;
		cub->hyp = cub->next_y;
		cub->next_y = calc_ray_y((cub->dist_y), cub);
	}
}

void	second_quadrant(t_cub *cub, int *i, int *j)
{
	if (fabs(cub->next_x) <= fabs(cub->next_y))
	{
		(*j)--;
		cub->dist_x -= 1;
		cub->hyp = cub->next_x;
		cub->next_x = calc_ray_x((cub->dist_x), cub);
	}
	else
	{
		(*i)++;
		cub->dist_y += 1;
		cub->hyp = cub->next_y;
		cub->next_y = calc_ray_y((cub->dist_y), cub);
	}
}

void	third_quadrant(t_cub *cub, int *i, int *j)
{
	if (fabs(cub->next_x) <= fabs(cub->next_y))
	{
		(*j)--;
		cub->dist_x -= 1;
		cub->hyp = cub->next_x;
		cub->next_x = calc_ray_x((cub->dist_x), cub);
	}
	else
	{
		(*i)--;
		cub->dist_y -= 1;
		cub->hyp = cub->next_y;
		cub->next_y = calc_ray_y((cub->dist_y), cub);
	}
}

void	fourth_quadrant(t_cub *cub, int *i, int *j)
{
	if (fabs(cub->next_x) <= fabs(cub->next_y))
	{
		(*j)++;
		cub->dist_x += 1;
		cub->hyp = cub->next_x;
		cub->next_x = calc_ray_x((cub->dist_x), cub);
	}
	else
	{
		(*i)--;
		cub->dist_y -= 1;
		cub->hyp = cub->next_y;
		cub->next_y = calc_ray_y((cub->dist_y), cub);
	}
}

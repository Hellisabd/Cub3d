/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:27:02 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/07/08 11:27:25 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3D.h"

void	verticality(t_draw *draw, t_mini_map *mini_map, int color)
{
	if (draw->dy > 0)
	{
		while (draw->start_y != draw->end_y)
		{
			mlx_put_pixel(mini_map->background_i, draw->start_x, \
			draw->start_y, color);
			draw->start_y++;
		}
	}
	else
	{
		while (draw->start_y != draw->end_y)
		{
			mlx_put_pixel(mini_map->background_i, draw->start_x, \
			draw->start_y, color);
			draw->start_y--;
		}
	}
}

void	last_octan(t_draw draw, t_mini_map *mini_map, int color)
{
	draw.e = draw.dx;
	draw.dx *= 2;
	draw.dy *= 2;
	while (1)
	{
		mlx_put_pixel(mini_map->background_i, draw.start_x, draw.start_y, \
		color);
		draw.start_x++;
		if (draw.start_x == draw.end_x)
			break ;
		draw.e += draw.dy;
		if (draw.e < 0)
		{
			draw.start_y--;
			draw.e += draw.dx;
		}
	}
}

void	horizontal_right(t_draw draw, t_mini_map *mini_map, int color)
{
	while (draw.start_x != draw.end_x)
	{
		mlx_put_pixel(mini_map->background_i, draw.start_x, \
		draw.start_y, color);
		draw.start_x++;
	}
}

void	first_and_last_quadrant(t_draw draw, t_mini_map *mini_map, int color)
{
	if (draw.dy > 0)
	{
		if (draw.dx >= draw.dy)
		{
			first_octan(draw, mini_map, color);
		}
		else
			second_octant(draw, mini_map, color);
	}
	else
	{
		if (draw.dx >= -draw.dy)
		{
			last_octan(draw, mini_map, color);
		}
		else
			seventh_octan(draw, mini_map, color);
	}
}

void	second_and_third_quadrant(t_draw draw, t_mini_map *mini_map, int color)
{
	if (draw.dy > 0)
	{
		if (-draw.dx >= draw.dy)
		{
			fourth_octan(draw, mini_map, color);
		}
		else
			third_octan(draw, mini_map, color);
	}
	else
	{
		if (draw.dx <= draw.dy)
		{
			fifth_octan(draw, mini_map, color);
		}
		else
			sixth_octan(draw, mini_map, color);
	}
}

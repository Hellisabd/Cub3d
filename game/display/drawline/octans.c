/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octans.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:59:18 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/07/08 12:01:37 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3D.h"

void	sixth_octan(t_draw draw, t_mini_map *mini_map, int color)
{
	draw.e = draw.dy;
	draw.dy *= 2;
	draw.dx *= 2;
	while (1)
	{
		mlx_put_pixel(mini_map->background_i, draw.start_x, draw.start_y, \
		color);
		draw.start_y--;
		if (draw.start_y == draw.end_y)
			break ;
		draw.e = draw.e - draw.dx;
		if (draw.e >= 0)
		{
			draw.start_x--;
			draw.e = draw.e + draw.dy;
		}
	}
}

void	fifth_octan(t_draw draw, t_mini_map *mini_map, int color)
{
	draw.e = draw.dx;
	draw.dx = draw.dx * 2;
	draw.dy = draw.dy * 2;
	while (1)
	{
		mlx_put_pixel(mini_map->background_i, draw.start_x, draw.start_y, \
		color);
		draw.start_x--;
		if (draw.start_x == draw.end_x)
			break ;
		draw.e = draw.e - draw.dy;
		if (draw.e >= 0)
		{
			draw.start_y--;
			draw.e = draw.e + draw.dx;
		}
	}
}

void	third_octan(t_draw draw, t_mini_map *mini_map, int color)
{
	draw.e = draw.dy;
	draw.dy *= 2;
	draw.dx *= 2;
	while (1)
	{
		mlx_put_pixel(mini_map->background_i, draw.start_x, draw.start_y, \
		color);
		draw.start_y++;
		if (draw.start_y == draw.end_y)
			break ;
		draw.e = draw.e + draw.dx;
		if (draw.e <= 0)
		{
			draw.start_x--;
			draw.e = draw.e + draw.dy;
		}
	}
}

void	fourth_octan(t_draw draw, t_mini_map *mini_map, int color)
{
	draw.e += draw.dx;
	draw.dx = draw.e * 2;
	draw.dy = draw.dy * 2;
	while (1)
	{
		mlx_put_pixel(mini_map->background_i, draw.start_x, draw.start_y, \
		color);
		draw.start_x--;
		if (draw.start_x == draw.end_x)
			break ;
		draw.e += draw.dy;
		if (draw.e >= 0)
		{
			draw.start_y++;
			draw.e += draw.dx;
		}
	}
}

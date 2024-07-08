/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:59:13 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/07/08 12:00:29 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3D.h"

void	seventh_octan(t_draw draw, t_mini_map *mini_map, int color)
{
	draw.e = draw.dy;
	draw.dy = draw.e * 2;
	draw.dx = draw.dx * 2;
	while (1)
	{
		mlx_put_pixel(mini_map->background_i, draw.start_x, draw.start_y, \
		color);
		draw.start_y--;
		if (draw.start_y == draw.end_y)
			break ;
		draw.e += draw.dx;
		if (draw.e > 0)
		{
			draw.start_x++;
			draw.e += draw.dy;
		}
	}
}

void	second_octant(t_draw draw, t_mini_map *mini_map, int color)
{
	draw.e = draw.dy;
	draw.dy = draw.e * 2;
	draw.dx *= 2;
	while (1)
	{
		mlx_put_pixel(mini_map->background_i, draw.start_x, draw.start_y, \
		color);
		draw.start_y++;
		if (draw.start_y == draw.end_y)
			break ;
		draw.e = draw.e - draw.dx;
		if (draw.e < 0)
		{
			draw.start_x++;
			draw.e = draw.e + draw.dy;
		}
	}
}

void	first_octan(t_draw draw, t_mini_map *mini_map, int color)
{
	draw.e = draw.dx;
	draw.dx = draw.e * 2;
	draw.dy = draw.dy * 2;
	while (1)
	{
		mlx_put_pixel(mini_map->background_i, draw.start_x, draw.start_y, \
		color);
		draw.start_x++;
		if (draw.start_x == draw.end_x)
			break ;
		draw.e = draw.e - draw.dy;
		if (draw.e < 0)
		{
			draw.start_y++;
			draw.e = draw.e + draw.dx;
		}
	}
}

void	draw_line2(t_draw draw, t_mini_map *mini_map, int color)
{
	if (draw.dx > 0)
	{
		if (draw.dy != 0)
		{
			first_and_last_quadrant(draw, mini_map, color);
		}
		else
			horizontal_right(draw, mini_map, color);
	}
	else
	{
		if (draw.dy != 0)
		{
			second_and_third_quadrant(draw, mini_map, color);
		}
		else
		{
			while (draw.start_x != draw.end_x)
			{
				mlx_put_pixel(mini_map->background_i, draw.start_x, \
				draw.start_y, color);
				draw.start_x--;
			}
		}
	}
}

void	drawline(t_ray *ray, t_mini_map *mini_map, t_player *player, int color)
{
	t_draw	draw;

	draw.start_x = player->pos_x + mini_map->size_wall_x / 2;
	draw.start_y = player->pos_y + mini_map->size_wall_y / 2;
	draw.end_x = round((ray->x) * (float)mini_map->size_wall_x);
	draw.end_y = round((ray->y) * (float)mini_map->size_wall_y);
	draw.dy = draw.end_y - draw.start_y;
	draw.dx = draw.end_x - draw.start_x;
	draw.e = 0;
	if (draw.dx != 0)
	{
		draw_line2(draw, mini_map, color);
	}
	else
	{
		if (draw.dy != 0)
			verticality(&draw, mini_map, color);
	}
}

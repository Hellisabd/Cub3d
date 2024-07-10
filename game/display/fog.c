/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fog.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:34:32 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/07/10 15:33:29 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	calculation_for_the_fog(int x, int y, int *opacity)
{
	int	calc_x;
	int	calc_y;

	if (x % 4 == 0 || y % 4 == 0)
	{
		if (x >= WIDTH / 2)
		{
			calc_x = x - WIDTH / 2;
		}
		else
			calc_x = WIDTH / 2 - x;
		if (y > HEIGHT / 2)
			calc_y = y - HEIGHT / 2;
		else
			calc_y = HEIGHT / 2 - y;
		*opacity = sqrt(calc_x * calc_x + calc_y * calc_y);
		*opacity /= 3;
	}
	if (*opacity > 240)
		*opacity = 240;
	if (*opacity < 0)
		*opacity = 0;
	return (*opacity);
}

void	fog(t_cub *cub)
{
	int	x;
	int	y;
	int	opacity;

	x = 0;
	y = 0;
	opacity = 255;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			calculation_for_the_fog(x, y, &opacity);
			mlx_put_pixel(cub->world.fog, x, y, opacity);
			x++;
		}
		y++;
	}
	mlx_put_pixel(cub->world.fog, WIDTH / 2, HEIGHT / 2, H_PINK);
	mlx_put_pixel(cub->world.fog, WIDTH / 2, HEIGHT / 2 + 1, H_PINK);
	mlx_put_pixel(cub->world.fog, WIDTH / 2, HEIGHT / 2 - 1, H_PINK);
	mlx_put_pixel(cub->world.fog, WIDTH / 2 + 1, HEIGHT / 2, H_PINK);
	mlx_put_pixel(cub->world.fog, WIDTH / 2 - 1, HEIGHT / 2, H_PINK);
}

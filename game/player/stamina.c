/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stamina.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:46:25 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/07/10 17:16:06 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	stam_handling(t_cub *cub)
{
	cub->speed = 2;
	cub->sprint = true;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT_SHIFT) && cub->sprint == true)
	{
		cub->speed = 3;
		cub->stamina -= 2;
		if (cub->stamina < 2)
			cub->sprint = false;
	}
	else
		cub->sprint = false;
}

void	put_stamina(t_cub *cub)
{
	int	n;
	int	x;
	int	y;
	
	n = 200;
	y = 100;
	x = 100;
	while (n-- >= cub->stamina)
	{
		if (n == cub->stamina)
		{
			while (x++ < 700 - (6 * (100 - n)))
			{
				y = 100;
				while (y < 150)
					mlx_put_pixel(cub->world.hud, x, y++, H_YELLOW);
			}
			while (x++ < 700)
			{
				y = 100;
				while (y < 150)
					mlx_put_pixel(cub->world.hud, x, y++, 0);
			}
		}
	}
}

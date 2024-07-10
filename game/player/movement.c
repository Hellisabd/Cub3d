/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:25:22 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/07/10 13:13:48 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	rotations(double xpos, double ypos, void *param)
{
	t_cub	*cub;
	int		x;
	int		y;

	cub = param;
	x = (int)xpos;
	y = (int)ypos;
	mlx_get_mouse_pos(cub->mlx, &x, &y);
	if (x > WIDTH / 2)
		cub->rot += PI / 20;
	if (x < WIDTH / 2)
		cub->rot -= PI / 20;
	mlx_set_mouse_pos(cub->mlx, WIDTH / 2, HEIGHT / 2);
}

void	move_player(t_cub *cub, float dir)
{
	int			deplacement_x;
	int			deplacement_y;
	// static int	stamina = 100;

	cub->speed = cub->mini_map.size_wall_x / 8;
	if (cub->speed == 0)
		cub->speed = 1;
	if (cub->stamina > 100)
		cub->stamina = 100;
	if (cub->stamina == 100)
		cub->sprint = true;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT_SHIFT) && cub->sprint == true)
	{
		cub->speed = cub->mini_map.size_wall_x / 4;
		if (cub->speed == 0)
			cub->speed = 2;
		// debug_nbr(GREEN, NULL, stamina);
		cub->stamina -= 2;
		if (cub->stamina < 2)
			cub->sprint = false;
	}
	else
		cub->sprint = false;
	deplacement_x = (int)(round(cos(dir) * cub->speed));
	deplacement_y = (int)(round(sin(dir) * cub->speed));
	int next_pos_x;
	int next_pos_y;
	int old_pos_x;
	int old_pos_y;

	old_pos_x = (int)round((float)((cub->player.pos_x) / (float)cub->mini_map.size_wall_x));
	old_pos_y = (int)round((cub->player.pos_y) / (float)cub->mini_map.size_wall_y);
	if ((dir <= PI && dir > 0) || (dir <= -PI && dir >= -2 * PI))
	{
		if ((dir < PI / 2 && dir > 0) || (dir < -3 * PI / 2 && dir > -2 * PI))
		{
			if (deplacement_y != 0)
			{
				next_pos_x = ((int)round((float)((cub->player.pos_x) + deplacement_x) / (float)cub->mini_map.size_wall_x));
				next_pos_y = ((int)round(((cub->player.pos_y) + deplacement_y) / (float)cub->mini_map.size_wall_y));
			}
			else
			{
				next_pos_x = ((int)round((float)((cub->player.pos_x) + deplacement_x) / (float)cub->mini_map.size_wall_x));
				next_pos_y = ((int)floor(((cub->player.pos_y) + deplacement_y) / (float)cub->mini_map.size_wall_y));
			}
		}
		else
		{
			next_pos_x = ((int)round((float)((cub->player.pos_x) + deplacement_x) / (float)cub->mini_map.size_wall_x));
			next_pos_y = ((int)round(((cub->player.pos_y) + deplacement_y) / (float)cub->mini_map.size_wall_y));
		}
	}
	else
	{
		if ((dir > 3 * PI / 2 && dir <= PI * 2) || (dir >= -PI / 2 && dir <= 0))
		{
			next_pos_x = ((int)round((float)((cub->player.pos_x) + deplacement_x) / (float)cub->mini_map.size_wall_x));
			next_pos_y = ((int)round(((cub->player.pos_y) + deplacement_y) / (float)cub->mini_map.size_wall_y));
		}
		else
		{
			next_pos_x = ((int)round((float)((cub->player.pos_x) + deplacement_x) / (float)cub->mini_map.size_wall_x));
			next_pos_y = ((int)round(((cub->player.pos_y) + deplacement_y) / (float)cub->mini_map.size_wall_y));
		}
	}
	if (cub->map->map[next_pos_y][next_pos_x] == '1' || cub->map->map[next_pos_y][next_pos_x] == 'D' ||  cub->map->map[next_pos_y][next_pos_x] == 'd')
		return ;
	if (next_pos_x != old_pos_x && next_pos_y != old_pos_y)
	{
		if (cub->map->map[next_pos_y][old_pos_x] == '1' || cub->map->map[next_pos_y][old_pos_x] == 'D' ||  cub->map->map[next_pos_y][old_pos_x] == 'd')
			return ;
		if (cub->map->map[old_pos_y][next_pos_x] == '1' || cub->map->map[old_pos_y][next_pos_x] == 'D' ||  cub->map->map[old_pos_y][next_pos_x] == 'd')
			return ;
	}
	cub->player.pos_x += deplacement_x;
	// cub->mini_map.player_i->instances->x += deplacement_x;
	cub->player.pos_y += deplacement_y;
}
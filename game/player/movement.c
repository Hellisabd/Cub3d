/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:25:22 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/07/05 15:26:32 by bgrosjea         ###   ########.fr       */
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
	static int	stamina = 100;

	cub->speed = cub->mini_map.size_wall_x / 8;
	cub->stamina = stamina;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT_SHIFT) && stamina > 0)
	{
		cub->speed = cub->mini_map.size_wall_x / 4;
		if (cub->speed == 0)
			cub->speed = 2;
		// debug_nbr(GREEN, NULL, stamina);
		cub->stamina = stamina;
		stamina--;
	}
	if (!mlx_is_key_down(cub->mlx, MLX_KEY_LEFT_SHIFT) && stamina < 100)
	{
		cub->speed = cub->mini_map.size_wall_x / 8;
		if (cub->speed == 0)
			cub->speed = 1;
		if (stamina > 100)
			stamina = 100;
		// debug_nbr(BLUE, NULL, stamina);
		cub->stamina = stamina;
		stamina++;
	}
	deplacement_x = (int)(round(cos(dir) * cub->speed));
	deplacement_y = (int)(round(sin(dir) * cub->speed));
	// int next_pos_x;
	// int next_pos_y;
	// int old_pos_x;
	// int old_pos_y;

	// debug_nbr(RED, "next_pos_x :", (int)round((float)(cub->player.pos_x + deplacement_x) / (float)cub->mini_map.size_wall_x));
	if ((dir <= PI && dir > 0) || (dir <= -PI && dir >= -2 * PI))
	{
		if ((dir < PI / 2 && dir > 0) || (dir < -3 * PI / 2 && dir > -2 * PI))
		{
			// debug_char(BLUE, "bas_droite :", cub->map->map[(int)round(((cub->player.pos_y + cub->mini_map.size_wall_y / 4) + deplacement_y) / (float)cub->mini_map.size_wall_y)][((int)round((float)((cub->player.pos_x + cub->mini_map.size_wall_x / 4) + deplacement_x) / (float)cub->mini_map.size_wall_x))]);
			// debug_nbr(BLUE, "deplacement_y", deplacement_y);
			// debug_nbr(BLUE, "deplacement_x", deplacement_x);
			// debug_nbr(BLUE, "pos_x",((int)round((float)((cub->player.pos_x + cub->mini_map.size_wall_x / 4) + deplacement_x) / (float)cub->mini_map.size_wall_x)));
			// debug_nbr(BLUE, "pos_y",(int)round(((cub->player.pos_y + cub->mini_map.size_wall_y / 4) + deplacement_y) / (float)cub->mini_map.size_wall_y));
			if (deplacement_y != 0)
			{
				if (cub->map->map[(int)round(((cub->player.pos_y + cub->mini_map.size_wall_y / 4) + deplacement_y) / (float)cub->mini_map.size_wall_y)][((int)round((float)((cub->player.pos_x + cub->mini_map.size_wall_x / 4) + deplacement_x) / (float)cub->mini_map.size_wall_x))] == '1')
					return ;
				if (cub->map->map[(int)round(((cub->player.pos_y + cub->mini_map.size_wall_y / 4) + deplacement_y) / (float)cub->mini_map.size_wall_y)][((int)round((float)((cub->player.pos_x + cub->mini_map.size_wall_x / 4) + deplacement_x) / (float)cub->mini_map.size_wall_x))] == 'D')
					return ;
			}
			else
			{
				if (cub->map->map[(int)floor(((cub->player.pos_y + cub->mini_map.size_wall_y / 4) + deplacement_y) / (float)cub->mini_map.size_wall_y)][((int)round((float)((cub->player.pos_x + cub->mini_map.size_wall_x / 4) + deplacement_x) / (float)cub->mini_map.size_wall_x))] == '1')
					return ;
				if (cub->map->map[(int)floor(((cub->player.pos_y + cub->mini_map.size_wall_y / 4) + deplacement_y) / (float)cub->mini_map.size_wall_y)][((int)round((float)((cub->player.pos_x + cub->mini_map.size_wall_x / 4) + deplacement_x) / (float)cub->mini_map.size_wall_x))] == 'D')
					return ;
			}
		}
		else
		{
			// debug_char(GREEN, "bas_gauche :", cub->map->map[(int)round(((cub->player.pos_y + cub->mini_map.size_wall_y / 4) + deplacement_y) / (float)cub->mini_map.size_wall_y)][((int)round((float)((cub->player.pos_x - cub->mini_map.size_wall_x / 4) + deplacement_x) / (float)cub->mini_map.size_wall_x))]);
			// debug_nbr(GREEN, "deplacement_y", deplacement_y);
			// debug_nbr(GREEN, "deplacement_x", deplacement_x);
			// debug_nbr(GREEN, "pos_x",((int)round((float)((cub->player.pos_x + cub->mini_map.size_wall_x / 4) - deplacement_x) / (float)cub->mini_map.size_wall_x)));
			// debug_nbr(GREEN, "pos_y",(int)round(((cub->player.pos_y + cub->mini_map.size_wall_y / 4) + deplacement_y) / (float)cub->mini_map.size_wall_y));
			if (cub->map->map[(int)round(((cub->player.pos_y + cub->mini_map.size_wall_y / 4) + deplacement_y) / (float)cub->mini_map.size_wall_y)][((int)round((float)((cub->player.pos_x - cub->mini_map.size_wall_x / 4) + deplacement_x) / (float)cub->mini_map.size_wall_x))] == '1')
				return ;
			if (cub->map->map[(int)round(((cub->player.pos_y + cub->mini_map.size_wall_y / 4) + deplacement_y) / (float)cub->mini_map.size_wall_y)][((int)round((float)((cub->player.pos_x - cub->mini_map.size_wall_x / 4) + deplacement_x) / (float)cub->mini_map.size_wall_x))] == 'D')
				return ;
		}
	}
	else
	{
		if ((dir > 3 * PI / 2 && dir <= PI * 2) || (dir >= -PI / 2 && dir <= 0))
		{
			// debug_char(PURPLE, "haut droit", cub->map->map[(int)round(((cub->player.pos_y - cub->mini_map.size_wall_y / 4) + deplacement_y) / (float)cub->mini_map.size_wall_y)][((int)round((float)((cub->player.pos_x + cub->mini_map.size_wall_x / 4) + deplacement_x) / (float)cub->mini_map.size_wall_x))]);
			// debug_nbr(PURPLE, "deplacement_y", deplacement_y);
			// debug_nbr(PURPLE, "deplacement_x", deplacement_x);
			// debug_nbr(PURPLE, "pos_x",((int)round((float)((cub->player.pos_x + cub->mini_map.size_wall_x / 4) + deplacement_x) / (float)cub->mini_map.size_wall_x)));
			// debug_nbr(PURPLE, "pos_y",(int)round(((cub->player.pos_y - cub->mini_map.size_wall_y / 4) + deplacement_y) / (float)cub->mini_map.size_wall_y));
			if (cub->map->map[(int)round(((cub->player.pos_y - cub->mini_map.size_wall_y / 4) + deplacement_y) / (float)cub->mini_map.size_wall_y)][((int)round((float)((cub->player.pos_x + cub->mini_map.size_wall_x / 4) + deplacement_x) / (float)cub->mini_map.size_wall_x))] == '1')
				return ;
			if (cub->map->map[(int)round(((cub->player.pos_y - cub->mini_map.size_wall_y / 4) + deplacement_y) / (float)cub->mini_map.size_wall_y)][((int)round((float)((cub->player.pos_x + cub->mini_map.size_wall_x / 4) + deplacement_x) / (float)cub->mini_map.size_wall_x))] == 'D')
				return ;
		}
		else
		{
			// debug_char(RED, "haut gauche :", cub->map->map[(int)round(((cub->player.pos_y + cub->mini_map.size_wall_y / 4) - deplacement_y) / (float)cub->mini_map.size_wall_y)][((int)round((float)((cub->player.pos_x - cub->mini_map.size_wall_x / 4) - deplacement_x) / (float)cub->mini_map.size_wall_x))]);
			// debug_nbr(RED, "deplacement_y", deplacement_y);
			// debug_nbr(RED, "deplacement_x", deplacement_x);
			// debug_nbr(RED, "pos_x",((int)round((float)((cub->player.pos_x - cub->mini_map.size_wall_x / 4) + deplacement_x) / (float)cub->mini_map.size_wall_x)));
			// debug_nbr(RED, "pos_y",(int)round(((cub->player.pos_y - cub->mini_map.size_wall_y / 4) + deplacement_y) / (float)cub->mini_map.size_wall_y));
			if (cub->map->map[(int)round(((cub->player.pos_y - cub->mini_map.size_wall_y / 4) + deplacement_y) / (float)cub->mini_map.size_wall_y)][((int)round((float)((cub->player.pos_x - cub->mini_map.size_wall_x / 4) + deplacement_x) / (float)cub->mini_map.size_wall_x))] == '1')
				return ;
			if (cub->map->map[(int)round(((cub->player.pos_y - cub->mini_map.size_wall_y / 4) + deplacement_y) / (float)cub->mini_map.size_wall_y)][((int)round((float)((cub->player.pos_x - cub->mini_map.size_wall_x / 4) + deplacement_x) / (float)cub->mini_map.size_wall_x))] == 'D')
				return ;
		}
	}
	// if (cub->map->map[(int)round(((cub->player.pos_y - cub->mini_map.size_wall_y / 2) + deplacement_y) / (float)cub->mini_map.size_wall_y)][((int)round((float)((cub->player.pos_x - cub->mini_map.size_wall_x / 2) + deplacement_x) / (float)cub->mini_map.size_wall_x))] == '1')
	// 	return ;
	// else if (cub->map->map[(int)round(((cub->player.pos_y + cub->mini_map.size_wall_y / 2) + deplacement_y) / (float)cub->mini_map.size_wall_y)][((int)round((float)((cub->player.pos_x + cub->mini_map.size_wall_x / 2) + deplacement_x) / (float)cub->mini_map.size_wall_x))] == '1')
	// 	return ;
	// else if (cub->map->map[(int)round(((cub->player.pos_y - cub->mini_map.size_wall_y / 2) + deplacement_y) / (float)cub->mini_map.size_wall_y)][((int)round((float)((cub->player.pos_x + cub->mini_map.size_wall_x / 2) + deplacement_x) / (float)cub->mini_map.size_wall_x))] == '1')
	// 	return ;
	// else if (cub->map->map[(int)round(((cub->player.pos_y + cub->mini_map.size_wall_y / 2) + deplacement_y) / (float)cub->mini_map.size_wall_y)][((int)round((float)((cub->player.pos_x - cub->mini_map.size_wall_x / 2) + deplacement_x) / (float)cub->mini_map.size_wall_x))] == '1')
	// 	return ;
	cub->player.pos_x += deplacement_x;
	// cub->mini_map.player_i->instances->x += deplacement_x;
	cub->player.pos_y += deplacement_y;
	// cub->mini_map.player_i->instances->y += deplacement_y;
}
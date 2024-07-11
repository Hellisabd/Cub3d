/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_enemy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:48:36 by amirloup          #+#    #+#             */
/*   Updated: 2024/07/11 13:14:48 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

bool	enemy_can_move(t_cub *cub)
{
	if (cub->map->map[cub->enemy.next_pos_y][cub->enemy.next_pos_x] == '1'
		|| cub->map->map[cub->enemy.next_pos_y][cub->enemy.next_pos_x] == 'D'
		|| cub->map->map[cub->enemy.next_pos_y][cub->enemy.next_pos_x] == 'd')
		return (false);
	if (cub->enemy.next_pos_x != (int)floor(cub->e_x) && cub->enemy.next_pos_y \
		!= (int)floor(cub->e_y))
	{
		if (cub->map->map[(int)floor(cub->e_y)][cub->enemy.next_pos_x] == '1'
		|| cub->map->map[(int)floor(cub->e_y)][cub->enemy.next_pos_x] == 'D'
		|| cub->map->map[(int)floor(cub->e_y)][cub->enemy.next_pos_x] == 'd')
			return (false);
		if (cub->map->map[cub->enemy.next_pos_y][(int)floor(cub->e_x)] == '1'
		|| cub->map->map[cub->enemy.next_pos_y][(int)floor(cub->e_x)] == 'D'
		|| cub->map->map[cub->enemy.next_pos_y][(int)floor(cub->e_x)] == 'd')
			return (false);
	}
	return (true);
}

void	move_enemy(t_cub *cub)
{
	cub->enemy.deplacement_x = cos(cub->enemy.angle + PI);
	cub->enemy.deplacement_y = sin(cub->enemy.angle + PI);
	cub->enemy.next_pos_x = (int)floor(cub->e_x + cub->enemy.deplacement_x / 10);
	cub->enemy.next_pos_y = (int)floor(cub->e_y + cub->enemy.deplacement_y / 10);
	if (enemy_can_move(cub))
	{
		cub->e_x += cub->enemy.deplacement_x / 10;
		cub->e_y += cub->enemy.deplacement_y / 10;
	}
}

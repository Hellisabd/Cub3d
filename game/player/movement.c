/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:25:22 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/07/11 10:20:40 by amirloup         ###   ########.fr       */
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
		cub->rot += PI / 10;
	if (x < WIDTH / 2)
		cub->rot -= PI / 10;
	mlx_set_mouse_pos(cub->mlx, WIDTH / 2, HEIGHT / 2);
}

bool	can_move(t_cub *cub, t_deplacement *dep)
{
	if (cub->map->map[dep->next_pos_y][dep->next_pos_x] == '1' 
		|| cub->map->map[dep->next_pos_y][dep->next_pos_x] == 'D'
		||  cub->map->map[dep->next_pos_y][dep->next_pos_x] == 'd')
		return (false);
	if (dep->next_pos_x != (int)floor(cub->p_x) && dep->next_pos_y \
		!= (int)floor(cub->p_y))
	{
		if (cub->map->map[(int)floor(cub->p_y)][dep->next_pos_x] == '1' 
		|| cub->map->map[(int)floor(cub->p_y)][dep->next_pos_x] == 'D'
		||  cub->map->map[(int)floor(cub->p_y)][dep->next_pos_x] == 'd')
			return (false);
		if (cub->map->map[dep->next_pos_y][(int)floor(cub->p_x)] == '1' 
		|| cub->map->map[dep->next_pos_y][(int)floor(cub->p_x)] == 'D'
		||  cub->map->map[dep->next_pos_y][(int)floor(cub->p_x)] == 'd')
		return (false);
	}
	return (true);
}

void	move_player(t_cub *cub, float dir, t_deplacement *dep)
{
	stam_handling(cub);
	dep->deplacement_x = cos(dir) * cub->speed;
	dep->deplacement_y = sin(dir) * cub->speed;
	dep->next_pos_x = (int)floor(cub->p_x + dep->deplacement_x / 10);
	dep->next_pos_y = (int)floor(cub->p_y + dep->deplacement_y / 10);
	if (can_move(cub, dep))
	{
		cub->p_x += dep->deplacement_x / 10;
		cub->p_y += dep->deplacement_y / 10;
		cub->player.pos_x = (int)round((cub->p_x - 0.5) * cub->mini_map.size_wall_x);
		cub->player.pos_y = (int)round((cub->p_y - 0.5) * cub->mini_map.size_wall_y);
	}
}

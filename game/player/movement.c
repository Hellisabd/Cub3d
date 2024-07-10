/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:25:22 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/07/10 14:56:48 by bgrosjea         ###   ########.fr       */
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

void	move_player_up(t_deplacement *dep, t_cub *cub, int dir)
{
	if ((dir > 3 * PI / 2 && dir <= PI * 2) || (dir >= -PI / 2 && dir <= 0))
	{
		dep->next_pos_x = ((int)round((float)((cub->player.pos_x) \
		+ dep->deplacement_x) / (float)cub->mini_map.size_wall_x));
		dep->next_pos_y = ((int)round(((cub->player.pos_y) + \
		dep->deplacement_y) / (float)cub->mini_map.size_wall_y));
	}
	else
	{
		dep->next_pos_x = ((int)round((float)((cub->player.pos_x) + \
		dep->deplacement_x) / (float)cub->mini_map.size_wall_x));
		dep->next_pos_y = ((int)round(((cub->player.pos_y) + \
		dep->deplacement_y) / (float)cub->mini_map.size_wall_y));
	}
}

void	move_player_down(t_deplacement *dep, t_cub *cub, int dir)
{
	if ((dir < PI / 2 && dir > 0) || (dir < -3 * PI / 2 && dir > -2 * PI))
	{
		if (dep->deplacement_y != 0)
		{
			dep->next_pos_x = ((int)round((float)((cub->player.pos_x) + \
			dep->deplacement_x) / (float)cub->mini_map.size_wall_x));
			dep->next_pos_y = ((int)round(((cub->player.pos_y) + \
			dep->deplacement_y) / (float)cub->mini_map.size_wall_y));
		}
		else
		{
			dep->next_pos_x = ((int)round((float)((cub->player.pos_x) + \
			dep->deplacement_x) / (float)cub->mini_map.size_wall_x));
			dep->next_pos_y = ((int)floor(((cub->player.pos_y) + \
			dep->deplacement_y) / (float)cub->mini_map.size_wall_y));
		}
	}
	else
	{
		dep->next_pos_x = ((int)round((float)((cub->player.pos_x) + \
		dep->deplacement_x) / (float)cub->mini_map.size_wall_x));
		dep->next_pos_y = ((int)round(((cub->player.pos_y) + \
		dep->deplacement_y) / (float)cub->mini_map.size_wall_y));
	}
}

bool	can_move(t_cub *cub, t_deplacement dep)
{
	if (cub->map->map[dep.next_pos_y][dep.next_pos_x] == '1' 
		|| cub->map->map[dep.next_pos_y][dep.next_pos_x] == 'D'
		||  cub->map->map[dep.next_pos_y][dep.next_pos_x] == 'd')
		return (false);
	if (dep.next_pos_x != dep.old_pos_x && dep.next_pos_y != dep.old_pos_y)
	{
		if (cub->map->map[dep.next_pos_y][dep.old_pos_x] == '1'
			|| cub->map->map[dep.next_pos_y][dep.old_pos_x] == 'D'
			||  cub->map->map[dep.next_pos_y][dep.old_pos_x] == 'd')
			return (false);
		if (cub->map->map[dep.old_pos_y][dep.next_pos_x] == '1'
			|| cub->map->map[dep.old_pos_y][dep.next_pos_x] == 'D'
			||  cub->map->map[dep.old_pos_y][dep.next_pos_x] == 'd')
			return (false);
	}
	return (true);
}

void	move_player(t_cub *cub, float dir)
{
	t_deplacement dep;
	
	stam_handling(cub);
	dep.deplacement_x = (int)(round(cos(dir) * cub->speed));
	dep.deplacement_y = (int)(round(sin(dir) * cub->speed));
	dep.old_pos_x = (int)round((float)((cub->player.pos_x) / (float)cub->mini_map.size_wall_x));
	dep.old_pos_y = (int)round((cub->player.pos_y) / (float)cub->mini_map.size_wall_y);
	if ((dir <= PI && dir > 0) || (dir <= -PI && dir >= -2 * PI))
		move_player_down(&dep, cub, dir);
	else
		move_player_up(&dep, cub, dir);
	if (can_move(cub, dep))
	{
		cub->player.pos_x += dep.deplacement_x;
		cub->player.pos_y += dep.deplacement_y;
	}
}

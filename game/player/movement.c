/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:25:22 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/07/22 11:33:40 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	set_player_pos(t_cub *cub)
{
	int	i;
	int	pos_x;
	int	pos_y;
	int	j;

	i = -1;
	pos_y = 0;
	while (++i < cub->map->height)
	{
		pos_x = 0;
		j = 0;
		while (cub->map->map[i][j])
		{
			if (cub->map->map[i][j] == cub->map->player_char)
			{
				cub->p_x = j + 0.5;
				cub->p_y = i + 0.5;
				cub->player.pos_x = pos_x;
				cub->player.pos_y = pos_y;
			}
			pos_x += cub->mini_map.size_wall_x;
			j++;
		}
		pos_y += cub->mini_map.size_wall_y;
	}
}

void	rotations(double xpos, double ypos, void *param)
{
	t_cub	*cub;
	int		x;
	int		y;

	cub = param;
	x = (int)xpos;
	y = (int)ypos;
	if (cub->status == 1)
	{
		mlx_get_mouse_pos(cub->mlx, &x, &y);
		if (x != WIDTH / 2)
			cub->rot += (x - (WIDTH / 2)) * (2 * PI / WIDTH);
		mlx_set_mouse_pos(cub->mlx, WIDTH / 2, HEIGHT / 2);
	}
}

bool	can_move(t_cub *cub, t_deplacement *dep)
{
	if (cub->map->map[dep->next_pos_y][dep->next_pos_x] == '1'
		|| cub->map->map[dep->next_pos_y][dep->next_pos_x] == 'D'
		|| cub->map->map[dep->next_pos_y][dep->next_pos_x] == 'd')
		return (false);
	if (dep->next_pos_x != (int)floor(cub->p_x) && dep->next_pos_y \
		!= (int)floor(cub->p_y))
	{
		if (cub->map->map[(int)floor(cub->p_y)][dep->next_pos_x] == '1'
		|| cub->map->map[(int)floor(cub->p_y)][dep->next_pos_x] == 'D'
		|| cub->map->map[(int)floor(cub->p_y)][dep->next_pos_x] == 'd')
			return (false);
		if (cub->map->map[dep->next_pos_y][(int)floor(cub->p_x)] == '1'
		|| cub->map->map[dep->next_pos_y][(int)floor(cub->p_x)] == 'D'
		|| cub->map->map[dep->next_pos_y][(int)floor(cub->p_x)] == 'd')
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
		cub->player.pos_x = (int)round((cub->p_x - 0.5) * \
			cub->mini_map.size_wall_x);
		cub->player.pos_y = (int)round((cub->p_y - 0.5) * \
			cub->mini_map.size_wall_y);
	}
}

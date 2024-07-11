/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_setup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:25:24 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/07/11 11:04:45 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	move_left(t_cub *cub)
{
	move_player(cub, cub->player.dir_left, &cub->dep);
	moving_light(cub);
}

void	move_right(t_cub *cub)
{
	move_player(cub, cub->player.dir_right, &cub->dep);
	moving_light(cub);
}

void	move_down(t_cub *cub)
{
	move_player(cub, cub->player.dir_down, &cub->dep);
	moving_light(cub);
}

void	move_up(t_cub *cub)
{
	move_player(cub, cub->player.dir_up, &cub->dep);
	moving_light(cub);
}

void	move(t_cub *cub)
{
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
		move_up(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
		move_down(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
		move_left(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
		move_right(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
		cub->rot += PI / 10;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
		cub->rot -= PI / 10;
}

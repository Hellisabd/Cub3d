/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_setup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:25:24 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/07/10 13:01:14 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	move_left(t_cub *cub)
{
	move_player(cub, cub->player.dir_left);
}

void	move_right(t_cub *cub)
{
	move_player(cub, cub->player.dir_right);
}

void	move_down(t_cub *cub)
{
	move_player(cub, cub->player.dir_down);
}

void	move_up(t_cub *cub)
{
	move_player(cub, cub->player.dir_up);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 10:09:13 by amirloup          #+#    #+#             */
/*   Updated: 2024/07/11 10:30:37 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	init_death(t_cub *cub)
{
	cub->anim.death_t = mlx_load_png("assets/you_deyed.png");
	if (cub->anim.death_t == NULL)
		debug_str(RED, NULL, "failed to load textures");
	cub->anim.death_i = mlx_texture_to_image(cub->mlx, cub->anim.death_t);
	mlx_resize_image(cub->anim.death_i, WIDTH, HEIGHT);
	return (0);
}

void	check_death(t_cub *cub)
{
	if (cub->enemy.dist <= 1)
	{
		cub->alive = false;
		mlx_delete_image(cub->mlx, cub->world.fog);
		mlx_image_to_window(cub->mlx, cub->anim.death_i, 0, 0);
	}
}

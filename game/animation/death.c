/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 10:09:13 by amirloup          #+#    #+#             */
/*   Updated: 2024/07/24 11:51:58 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	init_death(t_cub *cub)
{
	cub->anim.death_t = mlx_load_png("assets/you_deyed.png");
	if (cub->anim.death_t == NULL)
		exit((print_error(LOADING), free_in_window(cub), EXIT_FAILURE));
	cub->anim.death_i = mlx_texture_to_image(cub->mlx, cub->anim.death_t);
	if (!cub->anim.death_i)
		exit((free_in_window(cub), 1));
	if (mlx_resize_image(cub->anim.death_i, WIDTH, HEIGHT) == false)
		exit((print_error(RESIZE), free_in_window(cub), EXIT_FAILURE));
	return (0);
}

void	check_death(t_cub *cub)
{
	if (cub->enemy.dist <= 1)
	{
		cub->alive = false;
		mlx_delete_image(cub->mlx, cub->world.fog);
		if (mlx_image_to_window(cub->mlx, cub->anim.death_i, 0, 0) == -1)
			exit((print_error(WINDOW), free_in_window(cub), EXIT_FAILURE));
	}
}

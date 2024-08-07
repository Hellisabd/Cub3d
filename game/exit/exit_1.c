/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:07:55 by amirloup          #+#    #+#             */
/*   Updated: 2024/07/12 11:47:28 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	init_exit(t_cub *cub)
{
	cub->exit.exit_t = mlx_load_png("assets/exit.png");
	if (cub->exit.exit_t == NULL)
		exit((print_error(LOADING), free_in_window(cub), EXIT_FAILURE));
	cub->exit.success_t = mlx_load_png("assets/success.png");
	if (cub->exit.success_t == NULL)
		exit((print_error(LOADING), free_in_window(cub), EXIT_FAILURE));
	cub->exit.exit_i = mlx_texture_to_image(cub->mlx, cub->exit.exit_t);
	cub->exit.success_i = mlx_texture_to_image(cub->mlx, cub->exit.success_t);
	if (mlx_resize_image(cub->exit.success_i, WIDTH, HEIGHT) == false)
		exit((print_error(RESIZE), free_in_window(cub), EXIT_FAILURE));
	cub->exit.tab_exit = image_to_tab(cub->exit.exit_i);
}

void	set_exit_pos(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < cub->map->height)
	{
		j = 0;
		while (cub->map->map[i][j])
		{
			if (cub->map->map[i][j] == 'X')
			{
				cub->exit.e_x = j + 0.5;
				cub->exit.e_y = i + 0.5;
			}
			j++;
		}
		i++;
	}
}

void	check_exit(t_cub *cub)
{
	if (cub->exit.dist <= 0.5)
	{
		cub->alive = false;
		mlx_delete_image(cub->mlx, cub->world.fog);
		if (mlx_image_to_window(cub->mlx, cub->exit.success_i, 0, 0) == -1)
			exit((print_error(WINDOW), free_in_window(cub), EXIT_FAILURE));
	}
}

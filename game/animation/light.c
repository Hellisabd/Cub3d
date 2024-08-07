/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:44:24 by amirloup          #+#    #+#             */
/*   Updated: 2024/07/12 11:45:33 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	init_light(t_cub *cub)
{
	cub->anim.light_t = mlx_load_png("assets/light.png");
	if (cub->anim.light_t == NULL)
		exit((print_error(LOADING), free_in_window(cub), EXIT_FAILURE));
	cub->anim.light_i = mlx_texture_to_image(cub->mlx, cub->anim.light_t);
	if (mlx_resize_image(cub->anim.light_i, WIDTH / 4, HEIGHT / 3) == false)
		exit((print_error(RESIZE), free_in_window(cub), EXIT_FAILURE));
	if (mlx_image_to_window(cub->mlx, cub->anim.light_i, WIDTH / 2 + \
		WIDTH / 10, HEIGHT - (HEIGHT / 3)) == -1)
		exit((print_error(WINDOW), free_in_window(cub), EXIT_FAILURE));
	return (0);
}

void	moving_light(t_cub *cub)
{
	int	n;

	if (cub->sprint == true)
		n = HEIGHT / 50;
	else if (cub->sprint == false)
		n = HEIGHT / 100;
	if (cub->anim.i_light == 0)
		cub->anim.light_i->instances[0].y += n;
	if (cub->anim.i_light == 1)
		cub->anim.light_i->instances[0].y += n;
	if (cub->anim.i_light == 2)
		cub->anim.light_i->instances[0].y -= n;
	if (cub->anim.i_light == 3)
	{
		cub->anim.light_i->instances[0].y -= n;
		cub->anim.i_light = -1;
	}
	cub->anim.i_light++;
}

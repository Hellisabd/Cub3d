/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:45:27 by amirloup          #+#    #+#             */
/*   Updated: 2024/07/24 11:45:49 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	init_mini_map_2(t_cub *cub, t_mini_map *mini_map)
{
	mini_map->background_i = mlx_texture_to_image(cub->mlx, \
		mini_map->background_t);
	mini_map->wall_i = mlx_texture_to_image(cub->mlx, mini_map->wall_t);
	mini_map->door_i = mlx_texture_to_image(cub->mlx, mini_map->door_t);
	if (mlx_resize_image(mini_map->wall_i, mini_map->size_wall_x, \
		mini_map->size_wall_y) == false)
		exit((print_error(RESIZE), free_in_window(cub), EXIT_FAILURE));
	if (mlx_resize_image(mini_map->door_i, mini_map->size_wall_x, \
		mini_map->size_wall_y) == false)
		exit((print_error(RESIZE), free_in_window(cub), EXIT_FAILURE));
	if (mlx_resize_image(mini_map->background_i, mini_map->width, \
		mini_map->height) == false)
		exit((print_error(RESIZE), free_in_window(cub), EXIT_FAILURE));
	return (0);
}

int	init_mini_map(t_cub *cub, t_mini_map *mini_map)
{
	mini_map->wall_t = mlx_load_png(WALL);
	if (mini_map->wall_t == NULL)
		exit((print_error(LOADING), free_in_window(cub), EXIT_FAILURE));
	mini_map->door_t = mlx_load_png(DOOR);
	if (mini_map->door_t == NULL)
		exit((print_error(LOADING), free_in_window(cub), EXIT_FAILURE));
	mini_map->background_t = mlx_load_png(BACKGROUND);
	if (mini_map->background_t == NULL)
		exit((print_error(LOADING), free_in_window(cub), EXIT_FAILURE));
	if (init_mini_map_2(cub, mini_map) == 0)
		return (0);
	return (0);
}

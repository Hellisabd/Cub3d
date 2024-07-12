/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_3D_world.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:16:11 by amirloup          #+#    #+#             */
/*   Updated: 2024/07/12 11:35:52 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	load_door(t_cub *cub)
{
	int		i;
	char	*str;
	char	*nbr_str;

	i = 1;
	cub->world.door_t = malloc(sizeof(mlx_texture_t *) * 24);
	cub->world.door_i = malloc(sizeof(mlx_image_t *) * 24);
	cub->world.tab_anim_door = malloc(sizeof(int **) * 24);
	while (i < 25)
	{
		nbr_str = ft_itoa(i);
		str = ft_strjoin_const("assets/door/evil_door_anim", nbr_str);
		str = ft_strjoin(str, ".png");
		free(nbr_str);
		cub->world.door_t[i - 1] = mlx_load_png(str);
		if (cub->world.door_t[i - 1] == NULL)
			exit((print_error(LOADING), free_in_window(cub), EXIT_FAILURE));
		cub->world.door_i[i - 1] = mlx_texture_to_image(cub->mlx, \
			cub->world.door_t[i - 1]);
		cub->world.tab_anim_door[i - 1] = \
			image_to_tab(cub->world.door_i[i - 1]);
		i++;
		free(str);
	}
}

int	init_world_2(t_cub *cub)
{
	cub->world.tab_tab_no[0] = image_to_tab(cub->world.no[0]);
	cub->world.tab_tab_so[0] = image_to_tab(cub->world.so[0]);
	cub->world.tab_tab_we[0] = image_to_tab(cub->world.we[0]);
	cub->world.tab_tab_ea[0] = image_to_tab(cub->world.ea[0]);
	cub->world.tab_no = cub->world.tab_tab_no[0];
	cub->world.tab_so = cub->world.tab_tab_so[0];
	cub->world.tab_we = cub->world.tab_tab_we[0];
	cub->world.tab_ea = cub->world.tab_tab_ea[0];
	cub->world.no_i = cub->world.no[0];
	cub->world.so_i = cub->world.so[0];
	cub->world.we_i = cub->world.we[0];
	cub->world.ea_i = cub->world.ea[0];
	return (0);
}

int	init_world(t_cub *cub)
{
	load_door(cub);
	cub->world.no_t[0] = mlx_load_png(cub->map->no);
	if (cub->world.no_t[0] == NULL)
		exit((print_error(LOADING), free_in_window(cub), EXIT_FAILURE));
	cub->world.so_t[0] = mlx_load_png(cub->map->so);
	if (cub->world.so_t[0] == NULL)
		exit((print_error(LOADING), free_in_window(cub), EXIT_FAILURE));
	cub->world.we_t[0] = mlx_load_png(cub->map->we);
	if (cub->world.we_t[0] == NULL)
		exit((print_error(LOADING), free_in_window(cub), EXIT_FAILURE));
	cub->world.ea_t[0] = mlx_load_png(cub->map->ea);
	if (cub->world.ea_t[0] == NULL)
		exit((print_error(LOADING), free_in_window(cub), EXIT_FAILURE));
	cub->world.no[0] = mlx_texture_to_image(cub->mlx, cub->world.no_t[0]);
	cub->world.so[0] = mlx_texture_to_image(cub->mlx, cub->world.so_t[0]);
	cub->world.we[0] = mlx_texture_to_image(cub->mlx, cub->world.we_t[0]);
	cub->world.ea[0] = mlx_texture_to_image(cub->mlx, cub->world.ea_t[0]);
	if (init_world_2(cub) != 0)
		return (1);
	return (0);
}

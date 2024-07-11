/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:41:30 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/07/11 16:42:31 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_var(t_map *map)
{
	map->length = NULL;
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->c = NULL;
	map->f = NULL;
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	cub.map = malloc(sizeof(t_map));
	if (argc == 1)
		return (print_error("Please load a .cub file!\n"), 1);
	if (argc > 2)
		return (print_error("Too many arguments!\n"), 1);
	if (argc == 2)
	{
		init_var(cub.map);
		open_map(cub.map, argv);
		if (-1 == parsing_map(cub.map, &cub))
			exit(EXIT_FAILURE);
		open_window(&cub);
		free_rays(cub.ray);
		free_in_window(&cub);
	}
}

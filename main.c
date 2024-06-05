/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:25:35 by amirloup          #+#    #+#             */
/*   Updated: 2024/06/05 16:12:24 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_map	map;

	if (argc == 1)
		return (printf("Error\nPlease load a .cub file!\n"), 1);
	if (argc == 2)
	{
		open_map(&map, argv);
		// parsing_map();
		free_and_destroy(&map);
	}
	if (argc > 2)
		return (printf("Error\nToo many arguments!\n"), 1);
}

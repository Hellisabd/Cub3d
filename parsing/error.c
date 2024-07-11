/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:26:31 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/07/11 13:22:07 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	print_error(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
}

size_t	count_c(t_map *map, char c)
{
	size_t	n;
	int		x;
	int		y;

	n = 0;
	y = 0;
	x = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->map[y][x] != '\0')
		{
			if (map->map[y][x] == c)
				n++;
			x++;
		}
		y++;
	}
	return (n);
}

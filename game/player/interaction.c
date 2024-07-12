/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:25:19 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/07/12 09:04:46 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	interaction(mlx_key_data_t key, void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (key.key == MLX_KEY_E && key.action == 1 && open_door(cub, 0, 0) == 1)
	{
		cub->anim.door_count = 0;
		cub->anim.door_opening = STARTING;
	}
	if (key.key == MLX_KEY_E && key.action == 1 && close_door(cub, 0, 0) == 1)
	{
		cub->anim.door_count = 23;
		cub->anim.door_closing = STARTING;
	}
}

int	close_door(t_cub *cub, int player_x, int player_y)
{
	player_y = cub->p_y;
	player_x = cub->p_x;
	if (cub->map->map[player_y][player_x + 1] == 'o')
	{
		cub->map->map[player_y][player_x] = cub->map->player_char;
		cub->map->map[player_y][player_x + 1] = 'd';
		return (1);
	}
	if (cub->map->map[player_y + 1][player_x] == 'o')
	{
		cub->map->map[player_y][player_x] = cub->map->player_char;
		cub->map->map[player_y + 1][player_x] = 'd';
		return (1);
	}
	if (player_y != 0 && cub->map->map[player_y - 1][player_x] == 'o')
	{
		cub->map->map[player_y][player_x] = cub->map->player_char;
		return (cub->map->map[player_y - 1][player_x] = 'd', 1);
	}
	if (player_x != 0 && cub->map->map[player_y][player_x - 1] == 'o')
	{
		cub->map->map[player_y][player_x] = cub->map->player_char;
		return (cub->map->map[player_y][player_x - 1] = 'd', 1);
	}
	return (0);
}

int	open_door(t_cub *cub, int player_x, int player_y)
{
	player_y = cub->p_y;
	player_x = cub->p_x;
	if (cub->map->map[player_y][player_x + 1] == 'D')
	{
		cub->map->map[player_y][player_x + 1] = 'd';
		return (1);
	}
	if (cub->map->map[player_y + 1][player_x] == 'D')
	{
		cub->map->map[player_y + 1][player_x] = 'd';
		return (1);
	}
	if (player_y != 0 && cub->map->map[player_y - 1][player_x] == 'D')
	{
		cub->map->map[player_y - 1][player_x] = 'd';
		return (1);
	}
	if (player_x != 0 && cub->map->map[player_y][player_x - 1] == 'D')
	{
		cub->map->map[player_y][player_x - 1] = 'd';
		return (1);
	}
	return (0);
}

void	check_doors(t_cub *cub)
{
	if (cub->anim.door_opening == STARTING)
	{
		cub->anim.door_count++;
		if (cub->anim.door_count > 23)
			cub->anim.door_opening = END;
	}
	if (cub->anim.door_opening == END)
	{
		mlx_delete_image(cub->mlx, cub->mini_map.background_i);
		map_to_window(cub, true);
		cub->anim.door_opening = NONE;
	}
	if (cub->anim.door_closing == STARTING)
	{
		cub->anim.door_count--;
		if (cub->anim.door_count < 0)
			cub->anim.door_closing = END;
	}
	if (cub->anim.door_closing == END)
	{
		mlx_delete_image(cub->mlx, cub->mini_map.background_i);
		map_to_window(cub, true);
		cub->anim.door_closing = NONE;
	}
}	

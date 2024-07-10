/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:25:19 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/07/10 13:05:21 by bgrosjea         ###   ########.fr       */
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
	player_y = cub->player.pos_y / cub->mini_map.size_wall_y;
	player_x = cub->player.pos_x / cub->mini_map.size_wall_x;
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

void	put_stamina(t_cub *cub)
{
	int	n;
	int	x;
	int	y;
	
	n = 200;
	y = 100;
	x = 100;
	debug_nbr(RED, "stam", cub->stamina);
	while (n-- >= cub->stamina)
	{
		if (n == cub->stamina)
		{
			while (x++ < 700 - (6 * (100 - n)))
			{
				y = 100;
				while (y < 150)
					mlx_put_pixel(cub->world.hud, x, y++, H_YELLOW);
			}
			while (x++ < 700)
			{
				y = 100;
				while (y < 150)
					mlx_put_pixel(cub->world.hud, x, y++, 0);
			}
		}
	}
}

int	open_door(t_cub *cub, int player_x, int player_y)
{
	player_y = cub->player.pos_y / cub->mini_map.size_wall_y;
	player_x = cub->player.pos_x / cub->mini_map.size_wall_x;
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

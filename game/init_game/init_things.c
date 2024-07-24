/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_things.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:15:21 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/07/24 11:42:31 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	init_struct_world(t_cub *cub)
{
	cub->world.background_i = NULL;
	cub->world.background_t = NULL;
	cub->world.door_i = NULL;
	cub->world.door_t = NULL;
	cub->world.ea_i = NULL;
	cub->world.no_i = NULL;
	cub->world.so_i = NULL;
	cub->world.we_i = NULL;
	cub->world.fog = NULL;
	cub->world.hud = NULL;
	cub->world.npc = NULL;
	cub->world.exit = NULL;
	cub->world.tab_anim_door = NULL;
	cub->world.tab_ea = NULL;
	cub->world.tab_no = NULL;
	cub->world.tab_so = NULL;
	cub->world.tab_we = NULL;
	cub->anim.light_i = NULL;
	cub->anim.light_t = NULL;
	cub->anim.death_i = NULL;
	cub->anim.death_t = NULL;
	cub->enemy.pix_enemy = NULL;
	cub->exit.exit_i = NULL;
}

void	init_other(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (i < 3)
		{
			cub->enemy.enemy_t[i] = NULL;
			cub->enemy.enemy_i[i] = NULL;
			cub->enemy.tab_enemy[i] = NULL;
		}
		cub->world.tab_tab_ea[i] = NULL;
		cub->world.tab_tab_so[i] = NULL;
		cub->world.tab_tab_no[i] = NULL;
		cub->world.tab_tab_we[i] = NULL;
		cub->world.no[i] = NULL;
		cub->world.so[i] = NULL;
		cub->world.we[i] = NULL;
		cub->world.ea[i] = NULL;
		cub->world.no_t[i] = NULL;
		cub->world.so_t[i] = NULL;
		cub->world.ea_t[i] = NULL;
		cub->world.we_t[i] = NULL;
		i++;
	}
}

void	init_all(t_cub *cub)
{
	cub->world.door_t = NULL;
	cub->world.door_i = NULL;
	cub->world.tab_anim_door = NULL;
	cub->map->map = NULL;
	cub->map->length = NULL;
	cub->mini_map.background_i = NULL;
	cub->mini_map.background_t = NULL;
	cub->mini_map.door_i = NULL;
	cub->mini_map.door_t = NULL;
	cub->mini_map.wall_i = NULL;
	cub->mini_map.wall_t = NULL;
	init_struct_world(cub);
	cub->exit.exit_t = NULL;
	cub->exit.tab_exit = NULL;
	cub->exit.success_i = NULL;
	cub->exit.success_t = NULL;
}

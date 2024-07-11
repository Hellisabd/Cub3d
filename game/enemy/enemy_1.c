/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:37:23 by amirloup          #+#    #+#             */
/*   Updated: 2024/07/11 11:39:06 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	init_enemy(t_cub *cub)
{
	cub->enemy.enemy_t[0] = mlx_load_png("assets/npc/enemy_1.png");
	if (cub->enemy.enemy_t[0] == NULL)
		debug_str(RED, NULL, "failed to load textures");
	cub->enemy.enemy_t[1] = mlx_load_png("assets/npc/enemy_2.png");
	if (cub->enemy.enemy_t[1] == NULL)
		debug_str(RED, NULL, "failed to load textures");
	cub->enemy.enemy_t[2] = mlx_load_png("assets/npc/enemy_3.png");
	if (cub->enemy.enemy_t[2] == NULL)
		debug_str(RED, NULL, "failed to load textures");
	cub->enemy.enemy_i[0] = mlx_texture_to_image(cub->mlx, \
		cub->enemy.enemy_t[0]);
	cub->enemy.enemy_i[1] = mlx_texture_to_image(cub->mlx, \
		cub->enemy.enemy_t[1]);
	cub->enemy.enemy_i[2] = mlx_texture_to_image(cub->mlx, \
		cub->enemy.enemy_t[2]);
	cub->enemy.tab_enemy[0] = image_to_tab(cub->enemy.enemy_i[0]);
	cub->enemy.tab_enemy[1] = image_to_tab(cub->enemy.enemy_i[1]);
	cub->enemy.tab_enemy[2] = image_to_tab(cub->enemy.enemy_i[2]);
	return (0);
}

void	anim_enemy2(t_cub *cub, int i)
{
	cub->enemy.enemy_im = cub->enemy.enemy_i[i];
	cub->enemy.pix_enemy = cub->enemy.tab_enemy[i];
}

void	anim_enemy(t_cub *cub)
{
	if (cub->anim.i_enemy == 0)
		anim_enemy2(cub, 0);
	if (cub->anim.i_enemy == 1)
		anim_enemy2(cub, 1);
	if (cub->anim.i_enemy == 2)
		anim_enemy2(cub, 2);
	if (cub->anim.i_enemy == 3)
		anim_enemy2(cub, 1);
	if (cub->anim.i_enemy == 4)
	{
		anim_enemy2(cub, 0);
		cub->anim.i_enemy = -1;
	}
	cub->anim.i_enemy++;
}

void	set_enemy_pos(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < cub->map->height)
	{
		j = 0;
		while (cub->map->map[i][j])
		{
			if (cub->map->map[i][j] == 'A')
			{
				cub->e_x = j + 0.5;
				cub->e_y = i + 0.5;
			}
			j++;
		}
		i++;
	}
}

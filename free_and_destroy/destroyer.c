/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroyer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:12:31 by amirloup          #+#    #+#             */
/*   Updated: 2024/07/24 11:43:37 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	destroyer_3(t_mini_map *mini, t_cub *cub)
{
	if (cub->n_enemy == 1)
	{
		mlx_delete_texture(cub->enemy.enemy_t[0]);
		mlx_delete_texture(cub->enemy.enemy_t[1]);
		mlx_delete_texture(cub->enemy.enemy_t[2]);
	}
	mlx_delete_texture(cub->anim.light_t);
	mlx_delete_texture(cub->anim.death_t);
	if (cub->n_exit == 1)
	{
		mlx_delete_texture(cub->exit.exit_t);
		mlx_delete_texture(cub->exit.success_t);
	}
	mlx_delete_texture(mini->wall_t);
	mlx_delete_texture(mini->door_t);
	mlx_delete_texture(mini->background_t);
	mlx_delete_texture(cub->world.black_t);
}

void	destroyer_2(t_cub *cub, int i)
{
	if (i < 4)
	{
		ft_free_tab_int(cub->world.tab_tab_no[i], 450);
		ft_free_tab_int(cub->world.tab_tab_so[i], 450);
		ft_free_tab_int(cub->world.tab_tab_ea[i], 450);
		ft_free_tab_int(cub->world.tab_tab_we[i], 450);
	}
	if (i < 3)
	{
		mlx_delete_texture(cub->world.no_t[i]);
		mlx_delete_texture(cub->world.so_t[i]);
		mlx_delete_texture(cub->world.ea_t[i]);
		mlx_delete_texture(cub->world.we_t[i]);
	}
}

void	destroyer(mlx_t *mlx, t_cub *cub)
{
	int	i;

	(void)mlx;
	i = 0;
	while (i < 24)
	{
		destroyer_2(cub, i);
		mlx_delete_texture(cub->world.door_t[i]);
		ft_free_tab_int(cub->world.tab_anim_door[i], 450);
		i++;
	}
	free(cub->world.tab_anim_door);
	free(cub->world.door_t);
	free(cub->world.door_i);
	if (cub->n_enemy == 1)
	{
		ft_free_tab_int(cub->enemy.tab_enemy[0], 1024);
		ft_free_tab_int(cub->enemy.tab_enemy[1], 1024);
		ft_free_tab_int(cub->enemy.tab_enemy[2], 1024);
	}
	if (cub->n_exit == 1)
		ft_free_tab_int(cub->exit.tab_exit, 484);
	destroyer_3(&cub->mini_map, cub);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroyer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:12:31 by amirloup          #+#    #+#             */
/*   Updated: 2024/07/22 15:27:55 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	destroyer_3(t_mini_map *mini, t_cub *cub)
{
	mlx_delete_texture(cub->enemy.enemy_t[0]);
	mlx_delete_texture(cub->enemy.enemy_t[1]);
	mlx_delete_texture(cub->enemy.enemy_t[2]);
	mlx_delete_texture(cub->anim.light_t);
	mlx_delete_texture(cub->anim.death_t);
	mlx_delete_texture(cub->exit.exit_t);
	mlx_delete_texture(cub->exit.success_t);
	mlx_delete_texture(mini->player_t);
	mlx_delete_texture(mini->wall_t);
	mlx_delete_texture(mini->door_t);
	mlx_delete_texture(mini->background_t);
	mlx_delete_texture(cub->world.black_t);
}

void	destroyer_2(mlx_t *mlx, t_cub *cub, int i)
{
	if (i < 4)
	{
		mlx_delete_image(mlx, cub->world.no[i]);
		mlx_delete_image(mlx, cub->world.so[i]);
		mlx_delete_image(mlx, cub->world.we[i]);
		mlx_delete_image(mlx, cub->world.ea[i]);
		ft_free_tab_int(cub->world.tab_tab_no[i]);
		ft_free_tab_int(cub->world.tab_tab_so[i]);
		ft_free_tab_int(cub->world.tab_tab_ea[i]);
		ft_free_tab_int(cub->world.tab_tab_we[i]);
		if (i != 3)
		{
			mlx_delete_texture(cub->world.no_t[i]);
			mlx_delete_texture(cub->world.so_t[i]);
			mlx_delete_texture(cub->world.ea_t[i]);
			mlx_delete_texture(cub->world.we_t[i]);
		}
	}
}

void	destroyer(mlx_t *mlx, t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 24)
	{
		destroyer_2(mlx, cub, i);
		mlx_delete_image(mlx, cub->world.door_i[i]);
		mlx_delete_texture(cub->world.door_t[i]);
		ft_free_tab_int(cub->world.tab_anim_door[i]);
		i++;
	}
	free(cub->world.tab_anim_door);
	free(cub->world.door_t);
	free(cub->world.door_i);
	ft_free_tab_int(cub->enemy.tab_enemy[0]);
	ft_free_tab_int(cub->enemy.tab_enemy[1]);
	ft_free_tab_int(cub->enemy.tab_enemy[2]);
	ft_free_tab_int(cub->exit.tab_exit);
	destroyer_3(&cub->mini_map, cub);
}

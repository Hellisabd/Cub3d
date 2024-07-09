/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:00:33 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/07/09 11:49:46 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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

void	destroyer(t_mini_map *mini, mlx_t *mlx, t_cub *cub)
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
	mlx_delete_texture(cub->enemy.enemy_t[0]);
	mlx_delete_texture(cub->enemy.enemy_t[1]);
	mlx_delete_texture(cub->enemy.enemy_t[2]);
	mlx_delete_texture(cub->anim.light_t);
	mlx_delete_image(mlx, cub->enemy.enemy_i[0]);
	mlx_delete_image(mlx, cub->enemy.enemy_i[1]);
	mlx_delete_image(mlx, cub->enemy.enemy_i[2]);
	ft_free_tab_int(cub->enemy.tab_enemy[0]);
	ft_free_tab_int(cub->enemy.tab_enemy[1]);
	ft_free_tab_int(cub->enemy.tab_enemy[2]);
	mlx_delete_image(mlx, mini->background_i);
	mlx_delete_image(mlx, mini->wall_i);
	mlx_delete_image(mlx, mini->player_i);
	mlx_delete_image(mlx, mini->door_i);
	mlx_delete_texture(mini->player_t);
	mlx_delete_texture(mini->wall_t);
	mlx_delete_texture(mini->door_t);
	mlx_delete_texture(mini->background_t);
	mlx_delete_texture(cub->cursor_t);
	mlx_delete_texture(cub->world.black_t);
}

void	free_map_stuff(t_map *map)
{
	if (map->no)
		free(map->no);
	if (map->so)
		free(map->so);
	if (map->we)
		free(map->we);
	if (map->ea)
		free(map->ea);
	if (map->f)
		free(map->f);
	if (map->c)
		free(map->c);
	if (map->length)
		free(map->length);
	if (map->map)
		ft_free_tab(map->map);
	free(map);
}

void	free_rays(t_ray *ray)
{
	t_ray	*tmp;

	while (ray)
	{
		tmp = ray;
		ray = ray->next;
		free(tmp);
	}
	ray = NULL;
}

void	free_in_window(t_cub *cub)
{
	free_map_stuff(cub->map);
	destroyer(&cub->mini_map, cub->mlx, cub);
}

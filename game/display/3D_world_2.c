/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3D_world_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 10:20:03 by amirloup          #+#    #+#             */
/*   Updated: 2024/07/12 10:44:00 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	disp_world_2(t_cub *cub, t_ray *ray, t_wall *wall)
{
	if ((int)round(ray->x * 100000) % 100000 == 0 && \
		(int)round(ray->y * 100000) % 100000 != 0)
	{
		wall->side = 1;
		if (ray->x > cub->p_x)
			east(cub, ray, wall);
		else
			west(cub, ray, wall);
	}
	else if ((int)round(ray->y * 100000) % 100000 == 0 && \
		(int)round(ray->x * 100000) % 100000 != 0)
	{
		wall->side = 0;
		if (ray->y > cub->p_y)
			south(cub, ray, wall);
		else
			north(cub, ray, wall);
	}
}

void	north(t_cub *cub, t_ray *ray, t_wall *wall)
{
	if (ray->y > 1 && \
		cub->map->map[(int)round(ray->y) - 1][(int)floor(ray->x)] \
		== 'D')
		put_wall_in3d(wall, cub, cub->world.door_i[0], \
			cub->world.tab_anim_door[0]);
	else if (ray->y > 1 && \
		cub->map->map[(int)round(ray->y) - 1][(int)floor(ray->x)] \
		== 'd')
		put_wall_in3d(wall, cub, \
			cub->world.door_i[cub->anim.door_count], \
			cub->world.tab_anim_door[cub->anim.door_count]);
	else
		put_wall_in3d(wall, cub, cub->world.no_i, cub->world.tab_no);
}

void	south(t_cub *cub, t_ray *ray, t_wall *wall)
{
	if (cub->map->map[(int)round(ray->y) + 1] && \
		cub->map->map[(int)round(ray->y)][(int)floor(ray->x)] == 'D')
		put_wall_in3d(wall, cub, cub->world.door_i[0], \
			cub->world.tab_anim_door[0]);
	else if (cub->map->map[(int)round(ray->y) + 1] && \
		cub->map->map[(int)round(ray->y)][(int)floor(ray->x)] == 'd')
		put_wall_in3d(wall, cub, \
			cub->world.door_i[cub->anim.door_count], \
			cub->world.tab_anim_door[cub->anim.door_count]);
	else
		put_wall_in3d(wall, cub, cub->world.so_i, cub->world.tab_so);
}

void	east(t_cub *cub, t_ray *ray, t_wall *wall)
{
	if (cub->map->map[(int)floor(ray->y)][(int)round(ray->x)] == 'D')
		put_wall_in3d(wall, cub, cub->world.door_i[0], \
		cub->world.tab_anim_door[0]);
	else if (cub->map->map[(int)floor(ray->y)] \
			[(int)round(ray->x)] == 'd')
		put_wall_in3d(wall, cub, \
			cub->world.door_i[cub->anim.door_count], \
			cub->world.tab_anim_door[cub->anim.door_count]);
	else
		put_wall_in3d(wall, cub, cub->world.ea_i, cub->world.tab_ea);
}

void	west(t_cub *cub, t_ray *ray, t_wall *wall)
{
	if ((int)ray->x != 0 && \
		cub->map->map[(int)floor(ray->y)][(int)round(ray->x) \
		- 1] == 'D')
		put_wall_in3d(wall, cub, cub->world.door_i[0], \
			cub->world.tab_anim_door[0]);
	else if ((int)ray->x != 0 && \
		cub->map->map[(int)floor(ray->y)][(int)round(ray->x) \
		- 1] == 'd')
		put_wall_in3d(wall, cub, \
			cub->world.door_i[cub->anim.door_count], \
			cub->world.tab_anim_door[cub->anim.door_count]);
	else
		put_wall_in3d(wall, cub, cub->world.we_i, cub->world.tab_we);
}

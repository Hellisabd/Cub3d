/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_no_so.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:01:02 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/07/05 18:01:08 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	blink_no2(t_cub *cub)
{
	if (cub->anim.i_no == 3)
	{
		cub->world.no_i = cub->world.no[3];
		cub->world.tab_no = cub->world.tab_tab_no[3];
	}
	if (cub->anim.i_no == 4)
	{
		cub->world.no_i = cub->world.no[2];
		cub->world.tab_no = cub->world.tab_tab_no[2];
	}
	if (cub->anim.i_no == 5)
	{
		cub->world.no_i = cub->world.no[1];
		cub->world.tab_no = cub->world.tab_tab_no[1];
	}
	if (cub->anim.i_no == 6)
	{
		cub->world.no_i = cub->world.no[0];
		cub->world.tab_no = cub->world.tab_tab_no[0];
		cub->anim.i_no = -1;
		cub->anim.b_no = false;
	}
}

void	blink_no(t_cub *cub)
{
	int	r;

	r = rand();
	if (r % 100 == 0 && cub->anim.b_no == false)
		cub->anim.b_no = true;
	if (cub->anim.b_no == true)
	{
		if (cub->anim.i_no == 0)
		{
			cub->world.no_i = cub->world.no[0];
			cub->world.tab_no = cub->world.tab_tab_no[0];
		}
		if (cub->anim.i_no == 1)
		{
			cub->world.no_i = cub->world.no[1];
			cub->world.tab_no = cub->world.tab_tab_no[1];
		}
		if (cub->anim.i_no == 2)
		{
			cub->world.no_i = cub->world.no[2];
			cub->world.tab_no = cub->world.tab_tab_no[2];
		}
		blink_no2(cub);
		cub->anim.i_no++;
	}
}

void	blink_so2(t_cub *cub)
{
	if (cub->anim.i_so == 3)
	{
		cub->world.so_i = cub->world.so[3];
		cub->world.tab_so = cub->world.tab_tab_so[3];
	}
	if (cub->anim.i_so == 4)
	{
		cub->world.so_i = cub->world.so[2];
		cub->world.tab_so = cub->world.tab_tab_so[2];
	}
	if (cub->anim.i_so == 5)
	{
		cub->world.so_i = cub->world.so[1];
		cub->world.tab_so = cub->world.tab_tab_so[1];
	}
	if (cub->anim.i_so == 6)
	{
		cub->world.so_i = cub->world.so[0];
		cub->world.tab_so = cub->world.tab_tab_so[0];
		cub->anim.i_so = -1;
		cub->anim.b_so = false;
	}
}

void	blink_so(t_cub *cub)
{
	int	r;

	r = rand();
	if (r % 100 == 0 && cub->anim.b_so == false)
		cub->anim.b_so = true;
	if (cub->anim.b_so == true)
	{
		if (cub->anim.i_so == 0)
		{
			cub->world.so_i = cub->world.so[0];
			cub->world.tab_so = cub->world.tab_tab_so[0];
		}
		if (cub->anim.i_so == 1)
		{
			cub->world.so_i = cub->world.so[1];
			cub->world.tab_so = cub->world.tab_tab_so[1];
		}
		if (cub->anim.i_so == 2)
		{
			cub->world.so_i = cub->world.so[2];
			cub->world.tab_so = cub->world.tab_tab_so[2];
		}
		blink_so2(cub);
		cub->anim.i_so++;
	}
}

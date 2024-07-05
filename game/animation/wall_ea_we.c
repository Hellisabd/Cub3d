/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_ea_we.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:00:51 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/07/05 18:00:56 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	blink_we2(t_cub *cub)
{
	if (cub->anim.i_we == 3)
	{
		cub->world.we_i = cub->world.we[3];
		cub->world.tab_we = cub->world.tab_tab_we[3];
	}
	if (cub->anim.i_we == 4)
	{
		cub->world.we_i = cub->world.we[2];
		cub->world.tab_we = cub->world.tab_tab_we[2];
	}
	if (cub->anim.i_we == 5)
	{
		cub->world.we_i = cub->world.we[1];
		cub->world.tab_we = cub->world.tab_tab_we[1];
	}
	if (cub->anim.i_we == 6)
	{
		cub->world.we_i = cub->world.we[0];
		cub->world.tab_we = cub->world.tab_tab_we[0];
		cub->anim.i_we = -1;
		cub->anim.b_we = false;
	}
}

void	blink_we(t_cub *cub)
{
	int	r;

	r = rand();
	if (r % 100 == 0 && cub->anim.b_we == false)
		cub->anim.b_we = true;
	if (cub->anim.b_we == true)
	{
		if (cub->anim.i_we == 0)
		{
			cub->world.we_i = cub->world.we[0];
			cub->world.tab_we = cub->world.tab_tab_we[0];
		}
		if (cub->anim.i_we == 1)
		{
			cub->world.we_i = cub->world.we[1];
			cub->world.tab_we = cub->world.tab_tab_we[1];
		}
		if (cub->anim.i_we == 2)
		{
			cub->world.we_i = cub->world.we[2];
			cub->world.tab_we = cub->world.tab_tab_we[2];
		}
		blink_we2(cub);
		cub->anim.i_we++;
	}
}

void	blink_ea2(t_cub *cub)
{
	if (cub->anim.i_ea == 3)
	{
		cub->world.ea_i = cub->world.ea[3];
		cub->world.tab_ea = cub->world.tab_tab_ea[3];
	}
	if (cub->anim.i_ea == 4)
	{
		cub->world.ea_i = cub->world.ea[2];
		cub->world.tab_ea = cub->world.tab_tab_ea[2];
	}
	if (cub->anim.i_ea == 5)
	{
		cub->world.ea_i = cub->world.ea[1];
		cub->world.tab_ea = cub->world.tab_tab_ea[1];
	}
	if (cub->anim.i_ea == 6)
	{
		cub->world.ea_i = cub->world.ea[0];
		cub->world.tab_ea = cub->world.tab_tab_ea[0];
		cub->anim.i_ea = -1;
		cub->anim.b_ea = false;
	}
}

void	blink_ea(t_cub *cub)
{
	int	r;

	r = rand();
	if (r % 100 == 0 && cub->anim.b_ea == false)
		cub->anim.b_ea = true;
	if (cub->anim.b_ea == true)
	{
		if (cub->anim.i_ea == 0)
		{
			cub->world.ea_i = cub->world.ea[0];
			cub->world.tab_ea = cub->world.tab_tab_ea[0];
		}
		if (cub->anim.i_ea == 1)
		{
			cub->world.ea_i = cub->world.ea[1];
			cub->world.tab_ea = cub->world.tab_tab_ea[1];
		}
		if (cub->anim.i_ea == 2)
		{
			cub->world.ea_i = cub->world.ea[2];
			cub->world.tab_ea = cub->world.tab_tab_ea[2];
		}
		blink_ea2(cub);
		cub->anim.i_ea++;
	}
}

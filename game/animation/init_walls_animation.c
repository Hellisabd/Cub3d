/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_walls_animation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:25:10 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/07/12 11:32:34 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	init_anim(t_cub *cub)
{
	cub->alive = true;
	cub->anim.time = 0;
	cub->anim.frame = 0;
	cub->anim.i_no = 0;
	cub->anim.i_so = 0;
	cub->anim.i_we = 0;
	cub->anim.i_ea = 0;
	cub->anim.i_enemy = 0;
	cub->anim.i_light = 0;
	cub->anim.b_no = false;
	cub->anim.b_so = false;
	cub->anim.b_we = false;
	cub->anim.b_ea = false;
	cub->anim.door_closing = NONE;
	cub->anim.door_opening = NONE;
	cub->anim.door_count = 0;
	cub->enemy.enemy_im = cub->enemy.enemy_i[0];
	cub->enemy.pix_enemy = cub->enemy.tab_enemy[0];
	init_light(cub);
}

void	init_blink3(t_cub *cub)
{
	cub->world.tab_tab_no[1] = image_to_tab(cub->world.no[1]);
	cub->world.tab_tab_no[2] = image_to_tab(cub->world.no[2]);
	cub->world.tab_tab_no[3] = image_to_tab(cub->world.no[3]);
	cub->world.tab_tab_so[1] = image_to_tab(cub->world.so[1]);
	cub->world.tab_tab_so[2] = image_to_tab(cub->world.so[2]);
	cub->world.tab_tab_so[3] = image_to_tab(cub->world.so[3]);
	cub->world.tab_tab_we[1] = image_to_tab(cub->world.we[1]);
	cub->world.tab_tab_we[2] = image_to_tab(cub->world.we[2]);
	cub->world.tab_tab_we[3] = image_to_tab(cub->world.we[3]);
	cub->world.tab_tab_ea[1] = image_to_tab(cub->world.ea[1]);
	cub->world.tab_tab_ea[2] = image_to_tab(cub->world.ea[2]);
	cub->world.tab_tab_ea[3] = image_to_tab(cub->world.ea[3]);
}

void	init_blink2(t_cub *cub)
{
	if (cub->world.no_t[1] == NULL)
		exit((print_error(LOADING), free_in_window(cub), EXIT_FAILURE));
	cub->world.ea_t[2] = mlx_load_png("assets/walls/green_red_eye_3.png");
	if (cub->world.no_t[2] == NULL)
		exit((print_error(LOADING), free_in_window(cub), EXIT_FAILURE));
	cub->world.no[1] = mlx_texture_to_image(cub->mlx, cub->world.no_t[1]);
	cub->world.no[2] = mlx_texture_to_image(cub->mlx, cub->world.no_t[2]);
	cub->world.no[3] = mlx_texture_to_image(cub->mlx, cub->world.black_t);
	cub->world.so[1] = mlx_texture_to_image(cub->mlx, cub->world.so_t[1]);
	cub->world.so[2] = mlx_texture_to_image(cub->mlx, cub->world.so_t[2]);
	cub->world.so[3] = mlx_texture_to_image(cub->mlx, cub->world.black_t);
	cub->world.we[1] = mlx_texture_to_image(cub->mlx, cub->world.we_t[1]);
	cub->world.we[2] = mlx_texture_to_image(cub->mlx, cub->world.we_t[2]);
	cub->world.we[3] = mlx_texture_to_image(cub->mlx, cub->world.black_t);
	cub->world.ea[1] = mlx_texture_to_image(cub->mlx, cub->world.ea_t[1]);
	cub->world.ea[2] = mlx_texture_to_image(cub->mlx, cub->world.ea_t[2]);
	cub->world.ea[3] = mlx_texture_to_image(cub->mlx, cub->world.black_t);
}

int	init_blink(t_cub *cub)
{
	cub->world.black_t = mlx_load_png("assets/walls/black.png");
	if (cub->world.black_t == NULL)
		exit((print_error(LOADING), free_in_window(cub), EXIT_FAILURE));
	cub->world.no_t[1] = mlx_load_png("assets/walls/red_eye_2.png");
	if (cub->world.no_t[1] == NULL)
		exit((print_error(LOADING), free_in_window(cub), EXIT_FAILURE));
	cub->world.no_t[2] = mlx_load_png("assets/walls/red_eye_3.png");
	if (cub->world.no_t[2] == NULL)
		exit((print_error(LOADING), free_in_window(cub), EXIT_FAILURE));
	cub->world.so_t[1] = mlx_load_png("assets/walls/blue_eye_2.png");
	if (cub->world.so_t[1] == NULL)
		exit((print_error(LOADING), free_in_window(cub), EXIT_FAILURE));
	cub->world.so_t[2] = mlx_load_png("assets/walls/blue_eye_3.png");
	if (cub->world.so_t[2] == NULL)
		exit((print_error(LOADING), free_in_window(cub), EXIT_FAILURE));
	cub->world.we_t[1] = mlx_load_png("assets/walls/green_red_eye_2.png");
	if (cub->world.we_t[1] == NULL)
		exit((print_error(LOADING), free_in_window(cub), EXIT_FAILURE));
	cub->world.we_t[2] = mlx_load_png("assets/walls/green_red_eye_3.png");
	if (cub->world.we_t[2] == NULL)
		exit((print_error(LOADING), free_in_window(cub), EXIT_FAILURE));
	cub->world.ea_t[1] = mlx_load_png("assets/walls/green_eye_2.png");
	init_blink3((init_blink2(cub), cub));
	return (0);
}

void	blink(t_cub *cub)
{
	blink_no(cub);
	blink_so(cub);
	blink_we(cub);
	blink_ea(cub);
}

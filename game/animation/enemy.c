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
	cub->enemy.enemy_i[0] = mlx_texture_to_image(cub->mlx, cub->enemy.enemy_t[0]);
	cub->enemy.enemy_i[1] = mlx_texture_to_image(cub->mlx, cub->enemy.enemy_t[1]);
	cub->enemy.enemy_i[2] = mlx_texture_to_image(cub->mlx, cub->enemy.enemy_t[2]);
	cub->enemy.tab_enemy[0] = image_to_tab(cub->enemy.enemy_i[0]);
	cub->enemy.tab_enemy[1] = image_to_tab(cub->enemy.enemy_i[1]);
	cub->enemy.tab_enemy[2] = image_to_tab(cub->enemy.enemy_i[2]);
	return (0);
}

void	anim_enemy(t_cub *cub)
{
	if (cub->anim.i_enemy == 0)
	{
		cub->enemy.enemy_im = cub->enemy.enemy_i[0];
		cub->enemy.pix_enemy = cub->enemy.tab_enemy[0];
	}
	if (cub->anim.i_enemy == 1)
	{
		cub->enemy.enemy_im = cub->enemy.enemy_i[1];
		cub->enemy.pix_enemy = cub->enemy.tab_enemy[1];
	}
	if (cub->anim.i_enemy == 2)
	{
		cub->enemy.enemy_im = cub->enemy.enemy_i[2];
		cub->enemy.pix_enemy = cub->enemy.tab_enemy[2];
	}
	if (cub->anim.i_enemy == 3)
	{
		cub->enemy.enemy_im = cub->enemy.enemy_i[1];
		cub->enemy.pix_enemy = cub->enemy.tab_enemy[1];
	}
	if (cub->anim.i_enemy == 4)
	{
		cub->enemy.enemy_im = cub->enemy.enemy_i[0];
		cub->enemy.pix_enemy = cub->enemy.tab_enemy[0];
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

void put_enemy(t_cub *cub, t_ray *ray, int x)
{
	int	  	y;
	float	ratio;
	float	theta1;
	float	theta2;
	float	ratio_height;
	float	ratio_width;
	float	line_tab;
	int		start;
	int		max_rays;

	y = 0;
	while (y < HEIGHT)
	{
		mlx_put_pixel(cub->world.npc, x, y, 0);
		y++;
	}
	cub->enemy.d_x = cub->p_x - cub->e_x;
	cub->enemy.d_y = cub->p_y - cub->e_y;
	cub->enemy.dist = fabs(sqrt((cub->enemy.d_x * cub->enemy.d_x) + (cub->enemy.d_y * cub->enemy.d_y)));
	ratio = HEIGHT / cub->enemy.dist;
	ratio_height = (float)cub->enemy.enemy_i[0]->height / ratio;
	if (cub->p_x >= cub->e_x && cub->p_y >= cub->e_y)
		cub->enemy.angle = PI + acosf(fabs(cub->enemy.d_x) / cub->enemy.dist);
	else if (cub->p_x <= cub->e_x && cub->p_y >= cub->e_y)
		cub->enemy.angle = 3 * PI / 2 + acosf(fabs(cub->enemy.d_y) / cub->enemy.dist);
	else if (cub->p_x <= cub->e_x && cub->p_y <= cub->e_y)
		cub->enemy.angle = 2 * PI + acosf(fabs(cub->enemy.d_x) / cub->enemy.dist);
	else if (cub->p_x >= cub->e_x && cub->p_y <= cub->e_y)
		cub->enemy.angle = PI / 2 + acosf(fabs(cub->enemy.d_y) / cub->enemy.dist);
	if (cub->enemy.angle >= 2 * PI)
		cub->enemy.angle -= 2 * PI;
	if (cub->enemy.angle <= -2 * PI)
		cub->enemy.angle += 2 * PI;
	theta1 = cub->enemy.angle - atanf(0.5 / cub->enemy.dist);
	theta2 = cub->enemy.angle + atanf(0.5 / cub->enemy.dist);
	max_rays = (int)(fabs(theta1 - theta2)/ (cub->fov / cub->n));
	ratio_width = (float)cub->enemy.enemy_i[0]->width / (float)max_rays;

	start = ((int)ratio - HEIGHT) / 2;
	if (start < 0)
		start = 0;
	line_tab = start * ratio_height;
	if ((ray->hyp > cub->enemy.dist) && ((ray->angle >=theta1 && ray->angle <= theta2) || (ray->angle >= theta1 - 2 * PI && ray->angle <= theta2 - 2 * PI)))
	{
		y = 0;
		while (y < (HEIGHT - ratio + 50) / 2)
		{
			mlx_put_pixel(cub->world.npc, x, y, 0);
			y++;
		}
		while ((int)floor(line_tab) < (int)cub->enemy.enemy_i[0]->height && y < HEIGHT)
		{
			mlx_put_pixel(cub->world.npc, x, y, (int)cub->enemy.pix_enemy[(int)(floor)(cub->n_ray / 3 * ratio_width)][(int)floor(line_tab)]);
			y++;
			line_tab += ratio_height;
		}
		while (y < HEIGHT)
		{
			mlx_put_pixel(cub->world.npc, x, y, 0);
			y++;
		}
		cub->n_ray++;
		if (cub->n_ray >= max_rays * 3)
			cub->n_ray = 0;
	}
}
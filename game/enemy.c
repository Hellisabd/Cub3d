#include "../cub3D.h"

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

void	set_enemy_pos(t_cub *cub)
{
	int	i;
	int pos_x;
	int pos_y;
	int	j;

	i = 0;
	pos_y = 0;
	while (i < cub->map->height)
	{
		pos_x = 0;
		j = 0;
		while (cub->map->map[i][j])
		{
			if (cub->map->map[i][j] == 'A')
			{
				cub->e_x = j + 0.5;
				cub->e_y = i + 0.5;
				cub->enemy.pos_x = pos_x;
				cub->enemy.pos_y = pos_y;
			}
			pos_x += cub->mini_map.size_wall_x;
			j++;
		}
		pos_y += cub->mini_map.size_wall_y;
		i++;
	}
}

void put_enemy(t_cub *cub, t_ray *ray, int x)
{
	float	d_x;
	float	d_y;
	float	dist;
	int		y; 
	int		height;

	(void)ray;
	(void)x;
	d_x = cub->e_x - cub->p_x;
	d_y = cub->e_y - cub->p_y;
	dist = fabs(sqrt((d_x * d_x) + (d_y * d_y)));
	height = (int)(HEIGHT / dist);
	
	y = (HEIGHT - height) / 2;
	
	debug_float(GREEN, "px:", cub->p_x);
	debug_float(GREEN, "py:", cub->p_y);
	debug_float(RED, "ex:", cub->e_x);
	debug_float(RED, "ey:", cub->e_y);
	debug_float(BLUE, "dist: ", dist);
	debug_nbr(RED, "height: ", height);
	printf("\n");
	
	
	
	
	
	
	
	
	// height = (int)(HEIGHT / dist);
	// ratio_height = (float)cub->enemy.enemy_i[0]->height / (float)height;
	// 	start = (height - HEIGHT) / 2;
	// if (start < 0)
	// 	start = 0;
	// line_tab = start * ratio_height;
	// column_tab = (int)(ratio_height * cub->enemy.enemy_i[0]->width);
	// if (column_tab < 0)
	// 	column_tab = 0;
	// y = (HEIGHT - height) / 2;
	// if (x >= (WIDTH / 2) - (WIDTH * ratio) && x <= (WIDTH / 2) + (WIDTH * ratio))
	// {
	// 	while ((int)floor(line_tab) < (int)cub->enemy.enemy_i[0]->height && y < HEIGHT)
	// 	{
	// 		mlx_put_pixel(cub->world.npc, x, y, (int)cub->enemy.tab_enemy[0][column_tab][(int)floor(line_tab)]);
	// 		y++;
	// 		line_tab += ratio_height;
	// 	}
	// }
	// else
	// {
	// 	while (y <= HEIGHT)
	// 	{
	// 		mlx_put_pixel(cub->world.npc, x, y, 0);
	// 		y++;
	// 	}
	// };
}

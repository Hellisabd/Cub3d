#include "../cub3D.h"

int	init_enemy(t_cub *cub)
{
	cub->enemy.enemy_t[0] = mlx_load_png("assets/npc/enemy_1.png");
	if (cub->enemy.enemy_t[0] == NULL)
		debug_str(RED, NULL, "failed to load textures");
	cub->enemy.enemy_t[1] = mlx_load_png("assets/npc/enemy_2.png");
	if (cub->enemy.enemy_t[1] == NULL)
		debug_str(RED, NULL, "failed to load textures");
	cub->enemy.enemy_i[0] = mlx_texture_to_image(cub->mlx, cub->enemy.enemy_t[0]);
	cub->enemy.enemy_i[1] = mlx_texture_to_image(cub->mlx, cub->enemy.enemy_t[1]);
	cub->enemy.tab_enemy[0] = image_to_tab(cub->enemy.enemy_i[0]);
	cub->enemy.tab_enemy[1] = image_to_tab(cub->enemy.enemy_i[1]);
	return (0);
}

void put_enemy(t_cub *cub, t_ray *ray, int x)
{
	int		y;
	int		height;
	// float	ratio_width;
	float	ratio_height;
	static int column_tab = 0;
	float line_tab;
	int start;

	height = (int)(HEIGHT / ray->hyp_e);
	ratio_height = (float)cub->enemy.enemy_i[0]->height / (float)height;
	// ratio_width = (float)cub->enemy.enemy_i[0]->width / (float)width;
	start = (height - HEIGHT) / 2;
	if (start < 0)
		start = 0;
	line_tab = start * ratio_height;
	column_tab++; /* = (int)(ratio_height * cub->enemy.enemy_i[0]->width); */
	if (column_tab < 0)
		column_tab = 0;
	y = (HEIGHT - height) / 2;
	while ((int)floor(line_tab) < (int)cub->enemy.enemy_i[0]->height && y < HEIGHT)
	{
		mlx_put_pixel(cub->world.npc, x, y, (int)cub->enemy.tab_enemy[0][column_tab][(int)floor(line_tab)]);
		y++;
		line_tab += ratio_height;
	}
}

void	blank_npc(t_cub *cub, int x)
{
	int	y;

	y = 0;
	while (y <= HEIGHT)
	{
		mlx_put_pixel(cub->world.npc, x, y, 0);
		y++;
	}
}

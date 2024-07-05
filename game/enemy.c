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
    float   d_x;
    float   d_y;
    float   dist;
    float   enemy_angle;
    float   relative_angle;
    int     y;
    int     height;
    float   ratio_height;
    float   ratio_width;
    int     column_tab;
    float   line_tab;
    int     start;
    int     enemy_screen_x;

	(void)ray;
    // Calculer la distance entre l'ennemi et le joueur
    d_x = cub->e_x - cub->p_x;
    d_y = cub->e_y - cub->p_y;
    dist = fabs(sqrt((d_x * d_x) + (d_y * d_y)));
    height = (int)(HEIGHT / dist);

    // Calculer l'angle entre l'ennemi et le joueur
    enemy_angle = atan2(-d_y, d_x);
    relative_angle = enemy_angle - cub->rot;
    // if (relative_angle < 0)
    //     relative_angle += 2 * PI;
    // else if (relative_angle >= 2 * PI)
    //     relative_angle -= 2 * PI;

    // Calculer les ratios de largeur et de hauteur
    ratio_height = (float)cub->enemy.enemy_i[0]->height / (float)height;
    ratio_width = relative_angle / 2 * PI;

    // Calculer la position horizontale de l'ennemi à l'écran
    enemy_screen_x = (int)((WIDTH / 2) * (1 + tan(relative_angle)));

    start = (height - HEIGHT) / 2;
    if (start < 0)
        start = 0;
    line_tab = start * ratio_height;

    column_tab = (int)(ratio_width * cub->enemy.enemy_i[0]->width) - 1;
    if (column_tab < 0)
        column_tab = 0;
    if (column_tab >= (int)cub->enemy.enemy_i[0]->width)
        column_tab = (int)cub->enemy.enemy_i[0]->width - 1;

    y = 0;
    while (y < (HEIGHT - height) / 2)
    {
        mlx_put_pixel(cub->world.npc, x, y, 0);
        y++;
    }

    // Afficher les pixels de l'ennemi sur la colonne x
    if (x >= enemy_screen_x - (height / 2) && x <= enemy_screen_x + (height / 2))
    {
        while ((int)floor(line_tab) < (int)cub->enemy.enemy_i[0]->height && y < HEIGHT)
        {
            int color = cub->enemy.tab_enemy[0][column_tab][(int)floor(line_tab)];
            mlx_put_pixel(cub->world.npc, x, y, color);
            y++;
            line_tab += ratio_height;
        }
    }
    while (y < HEIGHT)
    {
        mlx_put_pixel(cub->world.npc, x, y, 0);
        y++;
    }
}

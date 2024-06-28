#include "../cub3D.h"

int	init_world(t_cub *cub)
{
	cub->world.no_t = mlx_load_png(cub->map->no);
	if (cub->world.no_t == NULL)
		debug_str(RED, NULL, "failed to load textures");
	cub->world.so_t = mlx_load_png(cub->map->so);
	if (cub->world.so_t == NULL)
		debug_str(RED, NULL, "failed to load textures");
	cub->world.we_t = mlx_load_png(cub->map->we);
	if (cub->world.we_t == NULL)
		debug_str(RED, NULL, "failed to load textures");
	cub->world.ea_t = mlx_load_png(cub->map->ea);
	if (cub->world.ea_t == NULL)
		debug_str(RED, NULL, "failed to load textures");
	cub->world.no_i = mlx_texture_to_image(cub->mlx, cub->world.no_t);
	cub->world.so_i = mlx_texture_to_image(cub->mlx, cub->world.so_t);
	cub->world.we_i = mlx_texture_to_image(cub->mlx, cub->world.we_t);
	cub->world.ea_i = mlx_texture_to_image(cub->mlx, cub->world.ea_t);
	cub->world.tab_no = image_to_tab(cub->world.no_i);
	cub->world.tab_so = image_to_tab(cub->world.so_i);
	cub->world.tab_we = image_to_tab(cub->world.we_i);
	cub->world.tab_ea = image_to_tab(cub->world.ea_i);
	return (0);
}

void put_wall_in3d(t_wall *wall, t_cub *cub, mlx_image_t *image, int **pixel_tab)
{
	int column_tab;
	float line_tab;

	if (pixel_tab == cub->world.tab_ea || pixel_tab == cub->world.tab_we)
		wall->ratio_width = wall->ray->y - floor(wall->ray->y);
	else
		wall->ratio_width = wall->ray->x - floor(wall->ray->x);
	wall->ratio_height = (float)image->height / (float)wall->img_height;
	line_tab = 0;
	column_tab = (int)(wall->ratio_width * image->width);
		// debug_nbr(RED, "wall->x :", wall->x);
		// debug_nbr(RED, "wall->y :", wall->y);
	while ((int)floor(line_tab) < (int)image->height && wall->y < HEIGHT)
	{
		mlx_put_pixel(cub->world.background_i, wall->x, wall->y, (int)pixel_tab[column_tab][(int)floor(line_tab)]);
		wall->y++;
		line_tab += wall->ratio_height;
	}
}

void	disp_world(t_cub *cub, t_ray *ray, int x)
{
	t_wall	wall;

	wall.dist_max = 7;
	wall.y = 0;
	wall.ray = ray;
	wall.ratio = ray->hyp * cos(ray->angle - cub->rot) / wall.dist_max;
	wall.img_height = (int)(HEIGHT * (1 - wall.ratio));
	wall.x = x;
	while (wall.y <= (int)(HEIGHT / 2 * (wall.ratio / 2)))
	{
		mlx_put_pixel(cub->world.background_i, x, wall.y, cub->map->c_h);
		wall.y++;
	}
	// if ((int)round(ray->x *100000) % 100000 == 0 && (int)round(ray->y *100000) % 100000 == 0)
	// {
	// 	ray->x += 0.01;
	// 	ray->y += 0.01;
	// }
	if ((int)round(ray->x *100000) % 100000 == 0 && (int)round(ray->y *100000) % 100000 != 0)
	{
		if (ray->x > cub->p_x)
			put_wall_in3d(&wall, cub, cub->world.ea_i, cub->world.tab_ea);
		else
			put_wall_in3d(&wall, cub, cub->world.we_i, cub->world.tab_we);
	}
	else if ((int)round(ray->y *100000) % 100000 == 0 && (int)round(ray->x *100000) % 100000 != 0)
	{
		// debug_str()
		if (ray->y > cub->p_y)
			put_wall_in3d(&wall, cub, cub->world.so_i, cub->world.tab_so);
		else
			put_wall_in3d(&wall, cub, cub->world.no_i, cub->world.tab_no);
	}
	else
		debug_str(RED, "PROUT\n", NULL);
	while (wall.y < HEIGHT)
	{
		mlx_put_pixel(cub->world.background_i, x, wall.y, cub->map->f_h);
		wall.y++;
	}
	// wall.y = 0;
	// while (wall.y < HEIGHT)
	// {
	// 	mlx_put_pixel(cub->world.fog, x, wall.y, 0x0000000DD);
	// 	wall.y++;
	// }
}

int	draw_walls(t_cub *cub, t_ray *ray)
{
	int	ratio;
	int	i;

	i = 0;
	ratio = WIDTH / cub->n;
	while (i < WIDTH && ray)
	{
		if (i % ratio == 0)
		{
			ray = ray->next;
			if (!ray)
				break ;
		}
		disp_world(cub, ray, i);
		i++;
	}
	return (0);
}

int	lets_go_3d(t_cub *cub)
{
	init_world(cub);
	cub->world.background_i = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (mlx_image_to_window(cub->mlx, cub->world.background_i, 0, 0) == -1)
		exit (1);
	// cub->world.fog = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	// if (mlx_image_to_window(cub->mlx, cub->world.fog, 0, 0) == -1)
	// 	exit (1);
	return (0);
}

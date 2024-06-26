#include "../cub3D.h"

int	init_world(t_cub *cub)
{
	cub->world.background_t = mlx_load_png("assets/invisible_background.png");
	if (cub->world.background_t == NULL)
		debug_str(RED, NULL, "failed to load textures");
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
	cub->world.background_i = mlx_texture_to_image(cub->mlx, cub->world.background_t);
	cub->world.no_i = mlx_texture_to_image(cub->mlx, cub->world.no_t);
	cub->world.so_i = mlx_texture_to_image(cub->mlx, cub->world.so_t);
	cub->world.we_i = mlx_texture_to_image(cub->mlx, cub->world.we_t);
	cub->world.ea_i = mlx_texture_to_image(cub->mlx, cub->world.ea_t);
	mlx_resize_image(cub->world.background_i, WIDTH, HEIGHT);
	return (0);
}

void	disp_world(t_cub *cub, t_ray *ray, int x)
{
	int dy;
	int y;
	float	dist_max;
	float	ratio;

	dist_max = 20;
	// printf("->ray-> y : %f\n", ray->y);
	int end_y = HEIGHT;

	y = 0;
	dy = end_y - y;
	ratio = ray->hyp / dist_max;
	// debug_float(BLUE, "ratio : ", ratio);
	// debug_float(RED, "up: ", HEIGHT * (1 - ratio) / 2);
	// debug_float(RED, "down: ", HEIGHT * ratio);
	while (y <= (int)(HEIGHT / 2 * (ratio / 2)))
	{
		mlx_put_pixel(cub->world.background_i, x, y, cub->map->c_h);
		y++;
	}
	while (y <= (int)(HEIGHT * (1 - ratio + (ratio / 2))))
	{
		if ((int)round(ray->x *1000) % 1000 == 0)
		{
			if (ray->x > cub->p_x)
				mlx_put_pixel(cub->world.background_i, x, y, H_BLUE);
			else
				mlx_put_pixel(cub->world.background_i, x, y, H_GREEN);
		}
		if ((int)round(ray->y *1000) % 1000 == 0)
		{
			if (ray->y > cub->p_y)
				mlx_put_pixel(cub->world.background_i, x, y, H_RED);
			else
				mlx_put_pixel(cub->world.background_i, x, y, H_PINK);
		}
		y++;
	}
	while (y < end_y)
	{
		mlx_put_pixel(cub->world.background_i, x, y, cub->map->f_h);
		y++;
	}
}

int	draw_walls(t_cub *cub, t_ray *ray)
{
	int	ratio;
	int	rayon;
	int	i;

	i = 0;
	rayon = 0;
	ratio = WIDTH / cub->n;
	while (i < WIDTH && ray)
	{
		if (i % ratio == 0)
		{
			rayon++;
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
	if (mlx_image_to_window(cub->mlx, cub->world.background_i, 0, 0) == -1)
		exit (1);
	// draw_walls(cub, cub->ray);
	return (0);
}

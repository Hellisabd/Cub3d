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
	cub->world.tab_no = image_to_tab(cub->world.no_i);
	cub->world.tab_so = image_to_tab(cub->world.so_i);
	cub->world.tab_we = image_to_tab(cub->world.we_i);
	cub->world.tab_ea = image_to_tab(cub->world.ea_i);
	return (0);
}

void put_wall_in3d(t_wall *wall, t_cub *cub, mlx_image_t *image, int **pixel_tab)
{
	int column;
	int line;


	wall->ratio_width = wall->ray->y - floor(wall->ray->y);
	wall->ratio_height = image->height / wall->img_height;
	line = 0;
	column = (int)(wall->ratio_width * image->width);
	while (line < (int)image->height)
		mlx_put_pixel(cub->world.background_i, wall->x, wall->y++, pixel_tab[column][line++]);
}

void	disp_world(t_cub *cub, t_ray *ray, int x)
{
	t_wall	wall;

	wall.dist_max = 20;
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
	if ((int)round(ray->x *1000) % 1000 == 0)
	{
		if (ray->x > cub->p_x)
			put_wall_in3d(&wall, cub, cub->world.ea_i, cub->world.tab_ea);
		else
			put_wall_in3d(&wall, cub, cub->world.we_i, cub->world.tab_we);
	}
	if ((int)round(ray->y *1000) % 1000 == 0)
	{
		if (ray->y > cub->p_y)
			put_wall_in3d(&wall, cub, cub->world.so_i, cub->world.tab_so);
		else
			put_wall_in3d(&wall, cub, cub->world.no_i, cub->world.tab_no);
	}
	while (wall.y < HEIGHT)
	{
		mlx_put_pixel(cub->world.background_i, x, wall.y, cub->map->f_h);
		wall.y++;
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
	return (0);
}

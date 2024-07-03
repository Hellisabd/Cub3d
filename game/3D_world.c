#include "../cub3D.h"

void	load_door(t_cub *cub)
{
	int i;
	char *str;

	i = 1;
	cub->world.door_t = malloc(sizeof(mlx_texture_t *) * 24);
	cub->world.door_i = malloc(sizeof(mlx_image_t *) * 24);
	cub->world.tab_anim_door = malloc(sizeof(int **) * 24);
	while (i < 25)
	{
		str = ft_strjoin_const("assets/door/evil_door_anim", ft_itoa(i));
		str = ft_strjoin(str, ".png");
		cub->world.door_t[i - 1] = mlx_load_png(str);
		cub->world.door_i[i - 1] = mlx_texture_to_image(cub->mlx, cub->world.door_t[i - 1]);
		cub->world.tab_anim_door[i - 1] = image_to_tab(cub->world.door_i[i - 1]);
		i++;
		free(str);
	}
}

int	init_world(t_cub *cub)
{
	load_door(cub);
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
	int start;

	if (wall->side == 1)
		wall->ratio_width = wall->ray->y - floor(wall->ray->y);
	else
		wall->ratio_width = wall->ray->x - floor(wall->ray->x);
	wall->ratio_height = (float)image->height / (float)wall->img_height;
	start = (wall->img_height - HEIGHT) / 2;
	if (start < 0)
		start = 0;
	line_tab = start * wall->ratio_height;
	column_tab = (int)(wall->ratio_width * image->width) - 1;
	if (column_tab < 0)
		column_tab = 0;
		// debug_nbr(RED, "wall->x :", wall->x);
		// debug_nbr(RED, "wall->y :", wall->y);
	while ((int)floor(line_tab) < (int)image->height && wall->y < HEIGHT)
	{
		// debug_nbr(BLUE, "x :", wall->x);
		// debug_nbr(BLUE, "y :", wall->y);
		// debug_nbr(BLUE, "column :", column_tab);
		// debug_nbr(BLUE, "line :", line_tab);
		mlx_put_pixel(cub->world.background_i, wall->x, wall->y, (int)pixel_tab[column_tab][(int)floor(line_tab)]);
		wall->y++;
		line_tab += wall->ratio_height;
	}
}

void	disp_world(t_cub *cub, t_ray *ray, int x)
{
	t_wall	wall;

	wall.y = 0;
	wall.ray = ray;
	wall.img_height = (int)(HEIGHT / ray->hyp * cos(ray->angle - cub->rot));
	wall.x = x;
	// debug_nbr(RED, "y:", (int)floor(ray->y));
	// debug_nbr(RED, "x:", (int)(ray->x));
	// if (cub->map->map[(int)floor(ray->y)][(int)floor(ray->x)] == 'D')
	// 	ray->door = true;
	while (wall.y <= (HEIGHT - wall.img_height) / 2)
	{
		mlx_put_pixel(cub->world.background_i, x, wall.y, cub->map->c_h);
		wall.y++;
	}
	if (ray->door)
	{
		put_wall_in3d(&wall, cub, cub->world.door_i[0], cub->world.tab_anim_door[0]);
		ray->door = false;
	}
	if ((int)round(ray->x * 100000) % 100000 == 0 && (int)round(ray->y *100000) % 100000 != 0)
	{
		wall.side = 1;
		if (ray->x > cub->p_x)
		{
			// debug_char(BLUE, "char in :", cub->map->map[(int)floor(ray->y)][(int)(ray->x)]);
			// debug_nbr(RED, "y:", (int)floor(ray->y));
			// debug_nbr(RED, "x:", (int)(ray->x));
			if (cub->map->map[(int)floor(ray->y)][(int)(ray->x)] == 'D')
				put_wall_in3d(&wall, cub, cub->world.door_i[0], cub->world.tab_anim_door[0]);
			else
				put_wall_in3d(&wall, cub, cub->world.ea_i, cub->world.tab_ea);
		}
		else
		{
			if ((int)ray->x != 0 && cub->map->map[(int)floor(ray->y)][(int)(ray->x) - 1] == 'D')
			{
				// debug_char(BLUE, "char in :", cub->map->map[(int)floor(ray->y)][(int)(ray->x) - 1]);
				// debug_nbr(RED, "y:", (int)floor(ray->y));
				// debug_nbr(RED, "x:", (int)(ray->x - 1));
				put_wall_in3d(&wall, cub, cub->world.door_i[1], cub->world.tab_anim_door[1]);
			}
			else
				put_wall_in3d(&wall, cub, cub->world.we_i, cub->world.tab_we);
		}
	}
	else if ((int)round(ray->y *100000) % 100000 == 0 && (int)round(ray->x *100000) % 100000 != 0)
	{
		wall.side = 0;
		// debug_str()
		if (ray->y > cub->p_y)
		{
			// debug_char(BLUE, "char in :", cub->map->map[(int)(ray->y)][(int)floor(ray->x)]);
			// debug_nbr(RED, "y:", (int)(ray->y));
			// debug_nbr(RED, "x:", (int)floor(ray->x));
			if (cub->map->map[(int)round(ray->y) + 1] && cub->map->map[(int)round(ray->y)][(int)floor(ray->x)] == 'D')
				put_wall_in3d(&wall, cub, cub->world.door_i[0], cub->world.tab_anim_door[0]);
			else
				put_wall_in3d(&wall, cub, cub->world.so_i, cub->world.tab_so);
		}
		else
		{
			// if ((int)(ray->y) != 0)
			// 	debug_char(BLUE, "char in :", cub->map->map[(int)(ray->y) - 1][(int)floor(ray->x)]);
			// debug_nbr(RED, "y:", (int)(ray->y) - 1);
			// debug_float(RED, "y:", ray->y);
			// debug_nbr(RED, "x:", (int)floor(ray->x));
			if (ray->y > 1 && cub->map->map[(int)(ray->y) - 1][(int)floor(ray->x)] == 'D')
				put_wall_in3d(&wall, cub, cub->world.door_i[0], cub->world.tab_anim_door[0]);
			else
				put_wall_in3d(&wall, cub, cub->world.no_i, cub->world.tab_no);
		}
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
	cub->world.fog = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (mlx_image_to_window(cub->mlx, cub->world.fog, 0, 0) == -1)
		exit (1);
	cub->world.hud = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (mlx_image_to_window(cub->mlx, cub->world.hud, 0, 0) == -1)
		exit (1);
	return (0);	
}

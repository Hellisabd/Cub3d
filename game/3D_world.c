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

int	lets_go_3D(t_cub *cub)
{
	init_world(cub);
	if (mlx_image_to_window(cub->mlx, cub->world.background_i, 0, 0) == -1)
		exit (1);
	return (0);
}

#include "../../cub3D.h"

int	init_light(t_cub *cub)
{
	cub->anim.light_t = mlx_load_png("assets/light.png");
	if (cub->anim.light_t == NULL)
		debug_str(RED, NULL, "failed to load textures");
	cub->anim.light_i = mlx_texture_to_image(cub->mlx, cub->anim.light_t);
	mlx_resize_image(cub->anim.light_i, WIDTH / 4, HEIGHT / 3);
	mlx_image_to_window(cub->mlx, cub->anim.light_i, WIDTH / 2 + WIDTH / 10, HEIGHT - (HEIGHT / 3));
	return (0);
}
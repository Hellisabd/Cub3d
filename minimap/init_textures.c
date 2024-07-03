#include "../cub3D.h"

int init_mini_map(t_cub *cub, t_mini_map *mini_map)
{
	mini_map->wall_t = mlx_load_png(WALL);
	mini_map->door_t = mlx_load_png(DOOR);
	if (mini_map->wall_t == NULL)
		debug_str(RED, NULL, "failed to load textures");
	mini_map->player_t = mlx_load_png(PLAYER_T);
	if (mini_map->player_t == NULL)
		debug_str(RED, NULL, "failed to load textures");
	mini_map->background_t = mlx_load_png(BACKGROUND);
	if (mini_map->background_t == NULL)
		debug_str(RED, NULL, "failed to load textures");
	mini_map->background_i = mlx_texture_to_image(cub->mlx, mini_map->background_t);
	mini_map->player_i = mlx_texture_to_image(cub->mlx, mini_map->player_t);
	mini_map->wall_i = mlx_texture_to_image(cub->mlx, mini_map->wall_t);
	mini_map->door_i = mlx_texture_to_image(cub->mlx, mini_map->door_t);
	mlx_resize_image(mini_map->player_i, mini_map->size_wall_x, mini_map->size_wall_y);
	mlx_resize_image(mini_map->wall_i, mini_map->size_wall_x, mini_map->size_wall_y);
	mlx_resize_image(mini_map->door_i, mini_map->size_wall_x, mini_map->size_wall_y);
	mlx_resize_image(mini_map->background_i, mini_map->width, mini_map->height);
	return (0);
}

#include "../cub3D.h"

void	destroyer(t_mini_map *mini, mlx_t *mlx)
{
	mlx_delete_image(mlx, mini->background_i);
	mlx_delete_image(mlx, mini->wall_i);
	mlx_delete_image(mlx, mini->player_i);
	mlx_delete_texture(mini->player_t);
	mlx_delete_texture(mini->wall_t);
	mlx_delete_texture(mini->background_t);
}

void	free_and_destroy(t_map *map)
{
	if (map->no)
		free(map->no);
	if (map->so)
		free(map->so);
	if (map->we)
		free(map->we);
	if (map->ea)
		free(map->ea);
	if (map->f)
		free(map->f);
	if (map->c)
		free(map->c);
	if (map->length)
		free(map->length);
	if (map->map)
		ft_free_tab(map->map);
	free(map);
}

void	free_in_window(t_cub *cub)
{
	free_and_destroy(cub->map);
	destroyer(&cub->mini_map, cub->mlx);
}
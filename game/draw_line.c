#include "../cub3D.h"

void	drawline(t_ray *ray, t_mini_map *mini_map, t_player *player)
{
	int dy;
	int dx;
	int e;
	int start_x = player->pos_x;
	int start_y = player->pos_y;
	int end_x = round(ray->x);
	int end_y = round(ray->y);
	dy = end_y - start_y;
	dx = end_x - start_x;
	e = 0;

	if (dx != 0)
	{
		if (dx > 0)
		{
			if (dy != 0)
			{
				if (dy > 0)
				{
					if (dx >= dy)// vecteur diagonal ou oblique proche de l’horizontale, dans le 1er octant
					{
						e = dx;
						dx = e * 2;
						dy = dy * 2;
						while (1)
						{
							mlx_put_pixel(mini_map->background_i, start_x, start_y, 0x00FF00FF);
							start_x++;
							if (start_x == end_x)
								break ;
							e = e - dy;
							if (e < 0)
							{
								start_y++;
								e = e + dx;
							}
						}
					}
					else // vecteur oblique proche de la verticale, dans le 2d octant
					{
						e = dy;
						dy = e * 2;
						dx *= 2;
						while (1)
						{
							mlx_put_pixel(mini_map->background_i, start_x, start_y, 0x00FF00FF);
							start_y++;
							if (start_y == end_y)
								break ;
							e = e - dx;
							if (e < 0)
							{
								start_x++;
								e = e + dy;
							}
						}
					}
				}
				else// vecteur oblique dans le 4e quadrant
				{
					if (dx>= -dy)// vecteur diagonal ou oblique proche de l’horizontale, dans le 8e octant
					{
						e = dx;
						dx *= 2;
						dy *= 2;
						while (1)
						{
							mlx_put_pixel(mini_map->background_i, start_x, start_y, 0x00FF00FF);
							start_x++;
							if (start_x == end_x)
								break ;
							e += dy;
							if (e < 0)
							{
								start_y++;
								e += dx;
							}
						}
					}
					else// vecteur oblique proche de la verticale, dans le 7e octant
					{
						e = dy;
						dy = e * 2;
						dx = dx *2;
						while (1)
						{
							mlx_put_pixel(mini_map->background_i, start_x, start_y, 0x00FF00FF);
							start_y--;
							if (start_y == end_y)
								break ;
							e += dx;
							if (e > 0)
							{
								start_x++;
								e += dy;
							}
						}
					}
				}
			}
			else// vecteur horizontal vers la droite
			{
				while (start_x != end_x)
				{
					mlx_put_pixel(mini_map->background_i, start_x, start_y, 0x00FF00FF);
					start_x++;
				}
			}
		}
		else
		{
			if (dy != 0)
			{
				if (dy > 0)// vecteur oblique dans le 2d quadrant
				{
					if (-dx >= dy)// vecteur diagonal ou oblique proche de l’horizontale, dans le 4e octant
					{
						e += dx;
						dx = e * 2;
						dy = dy * 2;
						while (1)
						{
							mlx_put_pixel(mini_map->background_i, start_x, start_y, 0x00FF00FF);
							start_x--;
							if (start_x == end_x)
								break ;
							e += dy;
							if (e >= 0)
							{
								start_y++;
								e += dx;
							}
						}
					}
					else// vecteur oblique proche de la verticale, dans le 3e octant
					{
						e = dy;
						dy *= 2;
						dx *= 2;
						while (1)
						{
							mlx_put_pixel(mini_map->background_i, start_x, start_y, 0x00FF00FF);
							start_y++;
							if (start_y == end_y)
								break ;
							e = e + dx;
							if (e <= 0)
							{
								start_x--;
								e = e + dy;
							}
						}
					}
				}
				else// vecteur oblique dans le 3e quadrant
				{
					if (dx <= dy)// vecteur diagonal ou oblique proche de l’horizontale, dans le 5e octant
					{
						e = dx;
						dx = dx * 2;
						dy = dy * 2;
						while (1)
						{
							debug_nbr(RED, "start_x :", start_x);
							mlx_put_pixel(mini_map->background_i, start_x, start_y, 0x00FF00FF);
							start_x--;
							if (start_x == end_x)
								break ;
							e = e - dy;
							if (e >= 0)
							{
								start_y--;
								e = e + dx;
							}
						}
					}
					else// vecteur oblique proche de la verticale, dans le 6e octant
					{
						e = dy;
						dy *= 2;
						dx *= 2;
						while (1)
						{
							mlx_put_pixel(mini_map->background_i, start_x, start_y, 0x00FF00FF);
							start_y--;
							if (start_y == end_y)
								break ;
							e = e - dx;
							if (e >= 0)
							{
								start_x--;
								e = e + dy;
							}
						}
					}
				}
			}
			else // vecteur horizontal vers la gauche
			{
				while (start_x != end_x)
				{
					mlx_put_pixel(mini_map->background_i, start_x, start_y, 0x00FF00FF);
					start_x--;
				}
			}
		}
	}
	else
	{
		if (dy != 0)
		{
			if (dy > 0)// vecteur vertical croissant
			{
				while (start_y != end_y)
				{
					mlx_put_pixel(mini_map->background_i, start_x, start_y, 0x00FF00FF);
					start_y++;
				}
			}
			else// vecteur vertical décroissant
			{
				while (start_y != end_y)
				{
					mlx_put_pixel(mini_map->background_i, start_x, start_y, 0x00FF00FF);
					start_y--;
				}
			}
		}
	}
}
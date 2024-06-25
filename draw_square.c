#include "cub3D.h"

int draw_square(int x, int y, int length, int height, t_world *world)
{
	int start_x;
	int start_y = y;
	while (y < y + length)
	{
		start_x = x;
		while (start_x < x + length)
		{
			mlx_put_pixel(world->background_i, start_x, start_y, H_BLUE);
			start_x++;
		}
		start_y++;
	}

}
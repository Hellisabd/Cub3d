#include "../cub3D.h"

void	print_map(t_cub *cub)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < (size_t)cub->map->height)
	{
		j = 0;
		while (j < ft_strlen(cub->map->map[i]))
		{
			if (cub->map->map[i][j] == '1')
				printf("%s%c%s", RED, cub->map->map[i][j], NC);
			else if (cub->map->map[i][j] == '0')
				printf("%s%c%s", BLUE, cub->map->map[i][j], NC);
			else
				printf("%s%c%s", GREEN, cub->map->map[i][j], NC);
			j++;
		}
		i++;
	}
	printf("\n");
}

void	set_player_pos(t_cub *cub)
{
	int	i;
	int	j;

	i = 1;
	while (i < cub->map->height)
	{
		j = 0;
		while (cub->map->map[i][j])
		{
			if (cub->map->map[i][j] == 'N' || cub->map->map[i][j] == 'S'
				|| cub->map->map[i][j] == 'E' || cub->map->map[i][j] == 'W')
			{
				cub->p_x = j + 0.5;
				cub->p_y = i + 0.5;
			}
			j++;
		}
		i++;
	}
}

float	calc_ray_y(float dist_y, t_cub *cub)
{
	float	next;


	next = dist_y / cos(cub->angle);
	return (next);
}

float	calc_ray_x(float dist_x, t_cub *cub)
{
	float	next;
	
	next = dist_x / sin(cub->angle);
	return (next);
}

void	raycasting(t_cub *cub)
{
	float		x;
	float		y;
	int			i;
	int			j;
	float dist_y;
	float dist_x;
	// bool		reset_y;
	float		next_x;
	float		next_y;
	// int		reset_x;

	set_player_pos(cub);
	cub->fov = PI * 11 / 30;
	cub->angle = -cub->fov / 2;
	// cub->angle = PI / 2;
	while (cub->angle < cub->fov / 2)
	{
		// reset_y = false;
		x = cub->p_x;
		y = cub->p_y;
		// cub->fov = 3.1416;
		// printf("x: %f\n", x);
		// printf("y: %f\n", y);
		i = floor(y);
		j = floor(x);
		// printf("i: %i\n", i);
		// printf("j: %i\n", j);
		if (cub->dir_x < 0)
			dist_x = x - fabs(floor(x));
		else
			dist_x = x - fabs(ceil(x));
		if (cub->dir_y < 0)
			dist_y = y - fabs(floor(y));
		else
			dist_y = y - fabs(ceil(y));
		next_x =  calc_ray_x(dist_x, cub);
		next_y =  calc_ray_y(dist_y, cub);

		// debug_float(YELLOW, "next_x :", next_x);
		// debug_float(YELLOW, "next_y :", next_y);
		// printf("next_y : %f\n", next_y);
		// debug_float(RED, "angle :", cub->angle);
		while (cub->map->map[i][j] == '0' || cub->map->map[i][j] == cub->map->d || cub->map->map[i][j] == 'P')
		{
			debug_float(RED, "next_y :", fabs(next_y));
			debug_float(PURPLE, "y :", y);
			debug_float(BLUE, "next_x :",fabs( next_x));
			debug_float(GREEN, "x :", x);
			if (next_y < 0 && fabs(next_x) >= fabs(next_y))
			{
				cub->map->map[i][j] = 'P';
				// printf("i: %d | j: %d\n", i , j);
				i--;
				dist_y -= 1;
				next_y =  calc_ray_y(dist_y, cub);
				// y += next_y;
			}
			else if (next_y > 0 && fabs(next_x) >= fabs(next_y))
			{
				cub->map->map[i][j] = 'P';
				// printf("i: %d | j: %d\n", i , j);
				i++;
				dist_y += 1;
				next_y =  calc_ray_y(dist_y, cub);
				// y += next_y;
			}
			else if (next_x < 0 && fabs(next_y) >= fabs(next_x))
			{
				cub->map->map[i][j] = 'P';
				// printf("i: %d | j: %d\n", i , j);
				j--;
				// x += next_x;
				dist_x -= 1;
				next_x =  calc_ray_x(dist_x, cub);
			}
			else if (next_x > 0 && fabs(next_y) >= fabs(next_x))
			{
				cub->map->map[i][j] = 'P';
				// printf("i: %d | j: %d\n", i , j);
				j++;
				dist_y += 1;
				next_y =  calc_ray_x(dist_x, cub);
				// x += next_x;
			}
			// if (fabs(next_x) >= fabs(next_y))
			// 	x += next_x;
			// else if (fabs(next_y) >= fabs(next_x))
			// 	y += next_y;
			// debug_str(YELLOW, NULL, "JE PASSE");
		}
		// printf("x: %f\n", x);
		// printf("y: %f\n", y);
		cub->angle += PI / 200;
	}
	// printf("dir_y %f\ndir_x : %f\n", cub->dir_y, cub->dir_x);
	print_map(cub);
}

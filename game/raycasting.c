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

float	calc_ray_x(float x, float y, t_cub *cub)
{
	float	next;

	y = 0;
	next = tan(cub->fov / 2) * x;
	if (cub->dir_x < 0)
		next *= -1;
	return (next);
}

float	calc_ray_y(float x, float y, t_cub *cub)
{
	float	next;
	
	x = 0;
	next = tan(cub->fov / 2) * y;
	if (cub->dir_y < 0)
		next *= -1;
	return (next);
}

void	raycasting(t_cub *cub)
{
	float		x;
	float		y;
	int			i;
	int			j;
	bool		reset_y;
	float		next_x;
	float		next_y;
	// int		reset_x;

	set_player_pos(cub);
	reset_y = false;
	x = cub->p_x;
	y = cub->p_y;
	cub->fov = 3.1416;
	// cub->fov = PI * 11 / 30;
	printf("x: %f\n", x);
	printf("y: %f\n", y);
	i = floor(y);
	j = floor(x);
	printf("i: %i\n", i);
	printf("j: %i\n", j);
	next_x = x - fabs(round(x));
	next_y = y - fabs(round(y));
	debug_float(YELLOW, "next_x :", next_x);
	debug_float(YELLOW, "next_y :", next_y);
	printf("next_y : %f\n", next_y);
	while (cub->map->map[i][j] == '0' || cub->map->map[i][j] == cub->map->d || cub->map->map[i][j] == 'P')
	{
		debug_float(RED, "next_y :", next_y);
		debug_float(PURPLE, "y :", y);
		debug_float(BLUE, "next_x :", next_x);
		debug_float(GREEN, "x :", x);
		if (cub->dir_y < 0 && fabs(next_x) >= fabs(next_y))
		{
			cub->map->map[i][j] = 'P';
			i--;
			next_y +=  calc_ray_y(x + next_x, y, cub);
			// y += next_y;
		}
		else if (fabs(next_x) >= fabs(next_y))
		{
			cub->map->map[i][j] = 'P';
			i++;
			next_y +=  calc_ray_y(x + next_x, y, cub);
			// y += next_y;
		}
		else if (cub->dir_x < 0 && fabs(next_y) >= fabs(next_x))
		{
			cub->map->map[i][j] = 'P';
			j--;
			// x += next_x;
			next_x +=  calc_ray_x(x, y + next_y, cub);
		}
		else if (fabs(next_y) >= fabs(next_x))
		{
			cub->map->map[i][j] = 'P';
			j++;
			next_x +=  calc_ray_x(x , y + next_y, cub);
			// x += next_x;
		}
		// if (fabs(next_x) >= fabs(next_y))
		// 	x += next_x;
		// else if (fabs(next_y) >= fabs(next_x))
		// 	y += next_y;
		debug_str(YELLOW, NULL, "JE PASSE");
	}
	printf("x: %f\n", x);
	printf("y: %f\n", y);
	printf("dir_y %f\ndir_x : %f\n", cub->dir_y, cub->dir_x);
	print_map(cub);
}

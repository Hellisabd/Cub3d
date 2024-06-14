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
			else if (cub->map->map[i][j] == 'P')
				printf("%s%c%s", GREEN, cub->map->map[i][j], NC);
			else 
				printf("%s%c%s", YELLOW, cub->map->map[i][j], NC);
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
	int		i;
	int		j;

	cub->ray = malloc(sizeof(t_ray *));
	if (!cub->ray)
		return ;
	*(cub->ray) = NULL;
	set_player_pos(cub);
	cub->fov = PI * 66 / 180;
	cub->angle = -cub->fov / 2;
	cub->n = 33;
	while (cub->angle < cub->fov / 2)
	{
		i = floor(cub->p_y);
		j = floor(cub->p_x);
		if (cub->dir_x < 0)
			cub->dist_x = cub->p_x - fabs(floor(cub->p_x));
		else
			cub->dist_x = cub->p_x - fabs(ceil(cub->p_x));
		if (cub->dir_y < 0)
			cub->dist_y = cub->p_y - fabs(floor(cub->p_y));
		else
			cub->dist_y = cub->p_y - fabs(ceil(cub->p_y));
		cub->next_x =  calc_ray_x(cub->dist_x, cub);		
		cub->next_y =  calc_ray_y(cub->dist_y, cub);
		while (cub->map->map[i][j] == '0' || cub->map->map[i][j] == cub->map->d || cub->map->map[i][j] == 'P' || cub->map->map[i][j] == 'Q')
		{
			
			if (cub->dist_y < 0 && fabs(cub->next_x) >= fabs(cub->next_y))
			{
				if (cub->angle < 0)
					cub->map->map[i][j] = 'P';
				else
					cub->map->map[i][j] = 'Q';
				i--;
				cub->dist_y -= 1;
				cub->hyp = cub->next_y;
				cub->next_y =  calc_ray_y(cub->dist_y, cub);
			}
			else if (cub->dist_y > 0 && fabs(cub->next_x) >= fabs(cub->next_y))
			{
				if (cub->angle < 0)
					cub->map->map[i][j] = 'P';
				else
					cub->map->map[i][j] = 'Q';
				i++;
				cub->dist_y += 1;
				cub->hyp = cub->next_y;
				cub->next_y =  calc_ray_y(cub->dist_y, cub);
			}
			else if (cub->dist_x < 0 && fabs(cub->next_y) >= fabs(cub->next_x))
			{
				if (cub->angle < 0)
					cub->map->map[i][j] = 'P';
				else
					cub->map->map[i][j] = 'Q';
				if (cub->angle < 0)
				{
					j--;
					cub->dist_x -= 1;
					cub->next_x =  calc_ray_x(cub->dist_x, cub);
				}
				else
				{
					j++;
					cub->dist_x -= 1;
					cub->hyp = cub->next_x;
					cub->next_x =  -calc_ray_x(cub->dist_x, cub);
				}
			}
			else if (cub->dist_x > 0 && fabs(cub->next_y) >= fabs(cub->next_x))
			{
				if (cub->angle < 0)
					cub->map->map[i][j] = 'P';
				else
					cub->map->map[i][j] = 'Q';
				if (cub->angle < 0)
				{
					j++;
					cub->dist_x += 1;
					cub->next_x =  calc_ray_x(cub->dist_x, cub);
				}
				else
				{
					j--;
					cub->dist_x += 1;
					cub->hyp = cub->next_x;
					cub->next_x =  -calc_ray_x(cub->dist_x, cub);
				}
			}
		}
		ft_add_back_raycast(cub->ray, cub->angle, cub->hyp);
		cub->angle += cub->fov / cub->n;
	}
	print_map(cub);
	printlist(*(cub->ray));
}

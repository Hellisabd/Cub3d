#include "../cub3D.h"

void	ft_add_back_raycast(t_ray **ray, t_cub *cub, float x, float y)
{
	t_ray	*tmp;
	t_ray	*new;

	new = malloc(sizeof(t_ray));
	if (!new)
		exit(EXIT_FAILURE);
	new->angle = cub->angle;
	new->hyp = fabs(cub->hyp);
	new->x = cub->x;
	new->y = cub->y;
	new->door = false;
	new->enemy = false;
	new->next = NULL;
	if (cub->ene == true)
	{
		new->enemy = true;
		new->hyp_e = cub->hyp_e;
		new->x_e = x;
		new->y_e = y;
	}
	if (ray == NULL || *ray == NULL)
	{
		*ray = new;
		return ;
	}
	tmp = *ray;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	printlist(t_ray *node, char *color)
{
	int	i;
	
	i = 0;
	while (node != NULL)
	{
		// printf("%s%d: angle: %f | dist: %f | x: %f | y: %f | x_e: %f | y_e: %f%s\n", color, i, node->angle, node->hyp, node->x, node->y, node->x_e, node->y_e, NC);
		printf("%sb: %i | hyp: %f%s\n", color, node->enemy, node->hyp_e, NC);
		i++;
		node = node->next;
	}
}

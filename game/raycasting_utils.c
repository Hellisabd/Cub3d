#include "../cub3D.h"

void	ft_add_back_raycast(t_ray **ray, t_cub *cub, float x, float y)
{
	t_ray	*tmp;
	t_ray	*new;

	new = malloc(sizeof(t_ray));
	if (!new)
		exit(EXIT_FAILURE);
	new->angle = cub->angle;
	new->hyp = cub->hyp;
	new->x = x;
	new->y = y;
	new->next = NULL;
	if (ray == NULL || *ray == NULL)
	{
		if (ray)
			*ray = new;
		return ;
	}
	tmp = *ray;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	printlist(t_ray *node, char *color)
{
	while (node != NULL)
	{
		printf("%sangle: %f | dist: %f | x: %f | y: %f%s\n", color, node->angle, node->hyp, node->x, node->y, NC);
		node = node->next;
	}
}

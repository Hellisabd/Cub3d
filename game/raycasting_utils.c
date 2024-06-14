#include "../cub3D.h"

void	ft_add_back_raycast(t_ray **ray, float angle, float distance)
{
	t_ray	*tmp;
	t_ray	*new;

	new = malloc(sizeof(t_ray));
	if (!new)
		exit(EXIT_FAILURE);
	new->angle = angle;
	new->hyp = distance;
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

void	printlist(t_ray *node)
{
	while (node != NULL)
	{
		printf("angle: %f | dist: %f\n", node->angle, node->hyp);
		node = node->next;
	}
}

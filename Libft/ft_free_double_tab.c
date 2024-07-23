/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_double_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:52:12 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/07/23 13:58:16 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab && tab[i])
		{
			free (tab[i]);
			i++;
		}
		free (tab);
	}
}

void	ft_free_tab_int(int **tab, int size)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (i < size)
		{
			free (tab[i]);
			i++;
		}
		free (tab);
		tab = NULL;
	}
}

void	ft_free_spec_tab(char **tab, int size)
{
	while (size && tab)
	{
		free(tab[size]);
		tab[size--] = NULL;
	}
}

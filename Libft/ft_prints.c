/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prints.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:43:48 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/02/12 11:58:06 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_prints(char *s)
{
	int		i;

	i = 0;
	if (!s)
	{
		i = ft_prints("(null)");
		return (i);
	}
	while (s[i])
	{
		if (ft_printchar(s[i]) == -1)
			return (-1);
		i++;
	}
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_epur_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:17:28 by amirloup          #+#    #+#             */
/*   Updated: 2024/04/12 14:08:28 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_epur_str(char *s, char c)
{
	int		i;
	int		j;
	int		count;
	char	*new_s;

	i = 0;
	count = 0;
	while (s[i] && s[i + 1])
	{
		if (s[i] == c && s[i + 1] == c)
			count++;
		i++;
	}
	new_s = malloc((i = 0, j = 0, sizeof(char) * (ft_strlen(s) + 1 - count)));
	if (!new_s)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c && s[i + 1] == c)
			i++;
		new_s[j] = s[i];
		i++;
		j++;
	}
	return (new_s[j] = '\0', new_s);
}

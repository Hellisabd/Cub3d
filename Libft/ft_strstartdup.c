/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstartdup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:49:07 by amirloup          #+#    #+#             */
/*   Updated: 2024/03/27 10:49:33 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstartdup(char *s, int start)
{
	int		l;
	int		i;
	char	*dest;

	i = 0;
	if (!s)
		return (NULL);
	l = ft_strlen(s) - start;
	dest = (char *)malloc (sizeof(char) * (l + 1));
	if (!dest)
		return (NULL);
	while (s[start] != '\0')
	{
		dest[i] = s[start];
		start++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:48:51 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/03/28 13:46:46 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *s, int n)
{
	size_t	i;
	char	*dest;

	i = 0;
	if (!s)
		return (NULL);
	dest = (char *)malloc (sizeof(char) * (n + 1));
	if (!dest)
		return (NULL);
	while (s[i] != '\0' && i < (size_t)n)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

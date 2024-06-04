/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:41:59 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/04/03 16:42:46 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_split_join(char *line, char *buff, char *dest)
{
	int		i;
	size_t	j;

	i = -1;
	j = 0;
	if (line)
		while (line[++i] != '\0')
			dest[i] = line[i];
	while (buff[j] != '\0')
		dest[i++] = buff[j++];
	dest[ft_strlen(line) + ft_strlen(buff)] = '\0';
	return (dest);
}

char	*ft_strjoin(char *line, char *buff)
{
	char	*dest;

	if (!line)
	{
		line = (char *)malloc(1 * sizeof(char));
		if (!line)
			return (NULL);
		line[0] = '\0';
	}
	if (!buff)
		return (free(line), NULL);
	dest = malloc(sizeof(char) * ((ft_strlen(buff) + ft_strlen(line)) + 1));
	if (dest == NULL)
		return (free(line), NULL);
	dest = ft_split_join(line, buff, dest);
	free (line);
	return (dest);
}

char	*ft_strjoin_const(const char *line, char *buff)
{
	char	*dest;

	if (!line)
		return (NULL);
	if (!buff)
		return (NULL);
	dest = malloc(sizeof(char) * ((ft_strlen(buff) \
		+ ft_strlen((char *)line)) + 1));
	if (dest == NULL)
		return (NULL);
	dest = ft_split_join((char *)line, buff, dest);
	return (dest);
}

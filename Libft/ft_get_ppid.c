/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_ppid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:37:24 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/03/18 14:18:58 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_getppid(char *path_file)
{
	int		fd;
	char	*line;
	int		ppid;

	fd = open(path_file, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_strncmp(line, "PPid:", 5) == 0)
		{
			ppid = ft_atoi(line + 6);
			return (close(fd), free(line), ppid);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (-1);
}

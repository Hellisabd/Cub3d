#include "../cub3D.h"

void	check_cub(char *s)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	if (s[i - 1] != 'b' || s[i - 2] != 'u' \
		|| s[i - 3] != 'c' || s[i - 4] != '.')
		exit((print_error(CUB), EXIT_FAILURE));
}

// char	*rgb_to_hex(char *rgb)
// {
// 	int		i;
// 	char	hex[10];
// 	char	**r_g_b;
// 	int		tab[3];
// 	char	*base;

// 	i = 0;
// 	hex[0] = '0';
// 	hex[1] = 'x';
// 	base = "0123456789ABCDEF";
// 	r_g_b = ft_split(rgb, ',');
// 	while (i < 3)
// 	{
// 		tab[i] = ft_atoi(rgb[i]);
// 		i++;
// 	}

// 	return (hex);
// }

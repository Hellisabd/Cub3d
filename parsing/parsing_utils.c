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

int	rgb_to_hex(char *rgb)
{
	int		i;
	int		hex;
	char	**r_g_b;
	int		tab[4];

	i = 0;
	r_g_b = ft_split(rgb, ',');
	while (i < 3)
	{
		tab[i] = ft_atoi(r_g_b[i]);
		i++;
	}
	tab[3] = 255;
	hex = (tab[0] << 24) | (tab[1] << 16) | (tab[2] << 8) | tab[3];
	ft_free_tab(r_g_b);
	return (hex);
}

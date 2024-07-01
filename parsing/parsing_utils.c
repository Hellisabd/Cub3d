#include "../cub3D.h"

int	**image_to_tab(mlx_image_t *image)
{
	int i;
	int j;
	unsigned char **tab;
	int tab_color[4];
	int **tab_colonnes;

	tab = malloc(sizeof(unsigned char *) * image->height);
	j = 0;
	i = -1;
	while (++i < (int)image->height)
		tab[i] = malloc(sizeof(unsigned char) * (image->width * 4));
	i = 0;
	while (i < (int)(image->width * image->height * 4))
	{
		tab[j][i % (image->width * 4)] = image->pixels[i];
		i++;
		if (i % (image->width * 4) == 0)
			j++;
	}

	i = -1;
	j = 0;
	int colonne = 0;
	int x = 0;
	int y = 0;
	tab_colonnes = malloc(sizeof(int *) * image->width);
	while (++i < (int)image->width)
		tab_colonnes[i] = malloc(sizeof (int) * image->height);
	while (j <= (int)image->height && i < (int)image->width * 4)
	{
		i = colonne * 4;
		while (1)
		{
			tab_color[i % 4] = (int)tab[j][i];
			i++;
			if (i % 4 == 0)
				break ;
		}
		tab_colonnes[y][x] = (tab_color[0] << 24) | (tab_color[1] << 16) | (tab_color[2] << 8) | tab_color[3];
		if (j == (int)(image->height - 1))
		{
			j = 0;
			y++;
			x = 0;
			colonne++;
		}
		tab_colonnes[y][x] = (tab_color[0] << 24) | (tab_color[1] << 16) | (tab_color[2] << 8) | tab_color[3];
		x++;
		j++;
	}
	ft_free_tab_int((int**)tab);
	return (tab_colonnes);
}

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

#include "../cub3D.h"

int	**image_to_tab(mlx_image_t *image)
{
	t_color	stock;

	stock.tab = malloc(sizeof(unsigned char *) * image->height);
	stock.j = 0;
	stock.i = -1;
	while (++stock.i < (int)image->height)
		stock.tab[stock.i] = malloc(sizeof(unsigned char) * (image->width * 4));
	stock.i = 0;
	while (stock.i < (int)(image->width * image->height * 4))
	{
		stock.tab[stock.j][stock.i % (image->width * 4)] = image->pixels[stock.i];
		stock.i++;
		if (stock.i % (image->width * 4) == 0)
			stock.j++;
	}
	// tab_line_to_tab_col();
	stock.colonne = 0;
	stock.x = 0;
	stock.y = 0;
	stock.i = -1;
	stock.j = 0;
	stock.tab_colonnes = malloc(sizeof(int *) * image->width);
	while (++stock.i < (int)image->width)
		stock.tab_colonnes[stock.i] = malloc(sizeof (int) * image->height);
	while (stock.j <= (int)image->height && stock.i < (int)image->width * 4)
	{
		stock.i = stock.colonne * 4;
		while (1)
		{
			stock.tab_color[stock.i % 4] = (int)stock.tab[stock.j][stock.i];
			stock.i++;
			if (stock.i % 4 == 0)
				break ;
		}
		stock.tab_colonnes[stock.y][stock.x] = (stock.tab_color[0] << 24) | (stock.tab_color[1] << 16) | (stock.tab_color[2] << 8) | stock.tab_color[3];
		if (stock.j == (int)(image->height - 1))
		{
			stock.j = 0;
			stock.y++;
			stock.x = 0;
			stock.colonne++;
		}
		stock.tab_colonnes[stock.y][stock.x] = (stock.tab_color[0] << 24) | (stock.tab_color[1] << 16) | (stock.tab_color[2] << 8) | stock.tab_color[3];
		stock.x++;
		stock.j++;
	}
	ft_free_tab_int((int **)stock.tab);
	return (stock.tab_colonnes);
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

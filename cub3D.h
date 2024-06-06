#ifndef CUB3D_H
# define CUB3D_H

# define NC "\e[0m"
# define RED "\e[1;31m"
# define GREEN "\e[1;32m"
# define YELLOW "\e[1;33m"
# define ORANGE "\e[1;34m"
# define PURPLE "\e[1;35m"
# define BLUE "\e[1;36m"

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# include "Libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"

# define WIDTH 2000
# define HEIGHT 1000

typedef struct s_map
{
	char	**map;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;
	int		rgb_f[3];
	int		rgb_c[3];
	char	**tab_f;
	char	**tab_c;
	int		*length;
	int		height;
	int		i;	
}	t_map;

// PARSING

void	open_map(t_map *map, char **argv);
int		parsing_map(t_map *map);

// FREE AND DESTROY
void	free_and_destroy(t_map *map);

//DEBUG

void    debug_nbr(char *color, char *msg, long long int content);
void    debug_str(char *color, char *msg, char *content);
void    debug_tab_nbr(char *color, char *msg, int *content, int size);
void    debug_char(char *color, char *msg, char content);
void    debug_tab_str(char *color, char *msg, char **content);


#endif

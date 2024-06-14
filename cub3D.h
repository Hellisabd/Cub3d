#ifndef CUB3D_H
# define CUB3D_H

# define NC "\e[0m"
# define RED "\e[1;31m"
# define GREEN "\e[1;32m"
# define YELLOW "\e[1;33m"
# define ORANGE "\e[1;34m"
# define PURPLE "\e[1;35m"
# define BLUE "\e[1;36m"

# define OPEN "Wrong input : map open.\n"
# define PLAYER "Wrong input : too many players.\n"
# define CUB "The map is not a .cub file!\n"
# define MALLOC "Malloc error!\n"
# define RGB "Wrong RGB format!\n"
# define LOAD_MAP "Error while opening the map!\n"
# define TEXTURE "Texture is missing!\n"

# define WALL "assets/red_square.png"
# define BACKGROUND "assets/white_square.png"
# define PLAYER "assets/red_square.png"


# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# include "Libft/libft.h"
# include ".MLX42/include/MLX42/MLX42.h"

# define PI		3.14159265358979323846
# define WIDTH 1000
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
	char	d;
	int		i;
}	t_map;

typedef struct s_map
{
	mlx_texture_t *wall_t;
	mlx_texture_t *background_t;
	mlx_texture_t *wall_i;
	mlx_texture_t *background_i;
}	t_mini_map;

typedef struct s_cub
{
	t_map	*map;
	mlx_t	*mlx;
	float	fov;
	float	angle;
	float	p_x;
	float	p_y;
	float	dir_x;
	float	dir_y;
	t_mini_map	mini_map;
}	t_cub;

// PARSING

void	open_map(t_map *map, char **argv);
int		parsing_map(t_map *map, t_cub *cub);
void	check_cub(char *s);

// GAME
void	open_window(t_cub *cub);
void	raycasting(t_cub *cub);

// FREE AND DESTROY
void	free_and_destroy(t_map *map);

// ERROR
void	print_error(char *msg);

//DEBUG

void	debug_nbr(char *color, char *msg, long long int content);
void	debug_str(char *color, char *msg, char *content);
void	debug_tab_nbr(char *color, char *msg, int *content, int size);
void	debug_char(char *color, char *msg, char content);
void	debug_float(char *color, char *msg, double content);
void	debug_tab_str(char *color, char *msg, char **content);

#endif

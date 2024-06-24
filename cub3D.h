#ifndef CUB3D_H
# define CUB3D_H

# define NC "\e[0m"
# define RED "\e[1;31m"
# define GREEN "\e[1;32m"
# define YELLOW "\e[1;33m"
# define ORANGE "\e[1;34m"
# define PURPLE "\e[1;35m"
# define BLUE "\e[1;36m"

# define H_GREEN 0x00FF00FF

# define OPEN "Wrong input : map open.\n"
# define PLAYER "Wrong input : too many players.\n"
# define CUB "The map is not a .cub file!\n"
# define MALLOC "Malloc error!\n"
# define RGB "Wrong RGB format!\n"
# define LOAD_MAP "Error while opening the map!\n"
# define TEXTURE "Texture is missing!\n"

# define WALL "assets/red_square.png"
# define BACKGROUND "assets/white_square.png"
# define PLAYER_T "assets/blue_circle.png"
# define CURSOR "assets/invisible_pixel.png"


# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# include "Libft/libft.h"
# include ".MLX42/include/MLX42/MLX42.h"

# define PI		3.14159265358979323846
# define WIDTH 3000
# define HEIGHT 1500

# define RIGHT 0
# define LEFT 1
# define UP 2
# define DOWN 3

typedef struct s_player
{
	int pos_x;
	int pos_y;
}	t_player;

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
	char	player_char;
	int		i;
}	t_map;

typedef struct s_ray
{
	float			hyp;
	float			angle;
	float			x;
	float			y;
	struct s_ray	*next;
}	t_ray;

typedef struct s_line
{
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;
}	t_line;

typedef struct s_mini_map
{
	mlx_texture_t	*wall_t;
	mlx_texture_t	*player_t;
	mlx_texture_t	*background_t;
	mlx_image_t		*wall_i;
	mlx_image_t		*background_i;
	mlx_image_t		*player_i;
	int				height;
	int				width;
	int				size_wall_x;
	int				size_wall_y;
}	t_mini_map;

typedef struct s_cub
{
	t_map			*map;
	t_ray			*ray;
	mlx_t			*mlx;
	float			dist_y;
	float			dist_x;
	float			next_x;
	float			next_y;
	float			n;
	float			fov;
	float			p_x;
	float			p_y;
	float			dir_x;
	float			dir_y;
	float			hyp;
	float			angle;
	float			x;
	float			y;
	float			rot;
	mlx_texture_t	*cursor_t;
	t_mini_map		mini_map;
	t_player 		player;
}	t_cub;

// PARSING

void	open_map(t_map *map, char **argv);
int		parsing_map(t_map *map, t_cub *cub);
void	check_cub(char *s);

// GAME
void	open_window(t_cub *cub);
void	raycasting(t_cub *cub);
void	ft_add_back_raycast(t_ray **ray, t_cub *cub, float x, float y);
void	drawline(t_ray *ray, t_mini_map *mini_map, t_player *player, int clor);
void	draw_ray(t_ray **ray, t_mini_map *mini_map, t_cub *cub, int color);
void	set_player_pos(t_cub *cub);
void	printlist(t_ray *node, char *color);

// MINIMAP

int map_to_window(t_cub *cub);
int init_data_mini_map(t_mini_map *minimap, t_map *map);
int init_mini_map(t_cub *cub, t_mini_map *mini_map);

// FREE AND DESTROY
void	free_map_stuff(t_map *map);
void	free_rays(t_ray *ray);
void	free_in_window(t_cub *cub);

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

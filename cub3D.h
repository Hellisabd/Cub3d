/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:41:01 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/07/12 11:40:25 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define H_BLUE 0x0000FFFF
# define H_RED 0xFF0000FF
# define H_BLACK 0x000000FF
# define H_PINK 0xFF33FFFF
# define H_YELLOW 0xF0C127FF

# define OPEN "Wrong input: map open.\n"
# define PLAYER "Wrong input: too many players.\n"
# define CUB "The map is not a .cub file!\n"
# define MALLOC "Malloc error!\n"
# define RGB "Wrong RGB format!\n"
# define LOAD_MAP "Error while opening the map!\n"
# define TEXTURE "Texture is missing!\n"
# define TEXTURE2 "Too many texture inputs!\n"
# define RESIZE "Resizing image!\n"
# define LOADING "Loading texture!\n"
# define WINDOW "Image to window!\n"
# define NONE 0
# define STARTING 1
# define END 2

# define WALL "assets/walls/black.png"
# define BACKGROUND "assets/white_square.png"
# define PLAYER_T "assets/blue_circle.png"
# define CURSOR "assets/invisible_pixel.png"
# define DOOR "assets/key.png"

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

typedef struct s_deplacement
{
	float		deplacement_x;
	float		deplacement_y;
	int			next_pos_x;
	int			next_pos_y;
	int			old_pos_x;
	int			old_pos_y;
	float		e_y;
	float		e_x;
	float		old_dir;
}	t_deplacement;

typedef struct s_draw
{
	int	dy;
	int	dx;
	int	e;
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;
}	t_draw;

typedef struct s_color
{
	int				i;
	int				j;
	unsigned char	**tab;
	int				tab_color[4];
	int				**tab_colonnes;
	int				colonne;
	int				x;
	int				y;
}	t_color;

typedef struct s_player
{
	int			pos_x;
	int			instance_x;
	int			pos_y;
	int			instance_y;
	float		dir_right;
	float		dir_up;
	float		dir_left;
	float		dir_down;
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
	int		f_h;
	int		c_h;
	int		rgb_f[3];
	int		rgb_c[3];
	char	**tab_f;
	char	**tab_c;
	int		*length;
	int		max_length;
	int		height;
	char	player_char;
	int		i;
	int		j;
	int		pos_x;
	int		pos_y;
	int		i_no;
	int		i_so;
	int		i_we;
	int		i_ea;
	int		i_f;
	int		i_c;
}	t_map;

typedef struct s_ray
{
	float			hyp;
	float			angle;
	float			x;
	float			y;
	bool			door;
	bool			enemy;
	float			x_e;
	float			y_e;
	float			hyp_e;
	struct s_ray	*next;
}	t_ray;

typedef struct s_wall
{
	t_ray	*ray;
	int		img_height;
	int		x;
	int		y;
	float	dist_max;
	float	ratio_height;
	float	ratio_width;
	bool	side;
}	t_wall;

typedef struct s_line
{
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;
}	t_line;

typedef struct s_exit
{
	mlx_texture_t	*exit_t;
	mlx_image_t		*exit_i;
	int				**tab_exit;
	mlx_texture_t	*success_t;
	mlx_image_t		*success_i;
	float			e_x;
	float			e_y;
	float			d_x;
	float			d_y;
	float			dist;
	float			angle;
	float			ratio;
	float			theta1;
	float			theta2;
	float			ratio_height;
	float			ratio_width;
	float			line_tab;
	int				start;
	int				max_rays;
	int				n_ray;
}	t_exit;

typedef struct s_anim
{
	double			time;
	int				frame;
	int				i_no;
	int				i_so;
	int				i_we;
	int				i_ea;
	int				i_enemy;
	int				i_light;
	bool			b_no;
	bool			b_so;
	bool			b_we;
	bool			b_ea;
	int				door_count;
	int				door_opening;
	int				door_closing;
	mlx_texture_t	*light_t;
	mlx_image_t		*light_i;
	mlx_texture_t	*death_t;
	mlx_image_t		*death_i;
}	t_anim;

typedef struct s_enemy
{
	mlx_texture_t	*enemy_t[3];
	mlx_image_t		*enemy_i[3];
	mlx_image_t		*enemy_im;
	int				**tab_enemy[3];
	int				**pix_enemy;
	float			d_x;
	float			d_y;
	float			dist;
	float			angle;
	float			ratio;
	float			theta1;
	float			theta2;
	float			ratio_height;
	float			ratio_width;
	float			line_tab;
	int				start;
	int				max_rays;
	float			deplacement_x;
	float			deplacement_y;
	int				next_pos_x;
	int				next_pos_y;
}	t_enemy;

typedef struct s_world
{
	mlx_texture_t	*background_t;
	mlx_texture_t	**door_t;
	mlx_texture_t	*black_t;
	mlx_texture_t	*no_t[4];
	mlx_texture_t	*so_t[4];
	mlx_texture_t	*we_t[4];
	mlx_texture_t	*ea_t[4];
	mlx_image_t		*background_i;
	mlx_image_t		*fog;
	mlx_image_t		*hud;
	mlx_image_t		*npc;
	mlx_image_t		*exit;
	mlx_image_t		*no_i;
	mlx_image_t		*no[4];
	mlx_image_t		*so_i;
	mlx_image_t		*so[4];
	mlx_image_t		*we_i;
	mlx_image_t		*we[4];
	mlx_image_t		*ea_i;
	mlx_image_t		**door_i;
	mlx_image_t		*ea[4];
	int				**tab_ea;
	int				**tab_so;
	int				**tab_no;
	int				**tab_we;
	int				***tab_anim_door;
	int				**tab_tab_no[4];
	int				**tab_tab_so[4];
	int				**tab_tab_ea[4];
	int				**tab_tab_we[4];
}	t_world;

typedef struct s_mini_map
{
	mlx_texture_t	*wall_t;
	mlx_texture_t	*door_t;
	mlx_texture_t	*player_t;
	mlx_texture_t	*background_t;
	mlx_image_t		*wall_i;
	mlx_image_t		*door_i;
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
	float			e_x;
	float			e_y;
	float			dir_x;
	float			dir_y;
	float			hyp;
	float			angle;
	float			x;
	float			y;
	float			rot;
	int				speed;
	int				stamina;
	bool			sprint;
	bool			alive;
	size_t			n_enemy;
	size_t			n_exit;
	int				n_ray;
	mlx_texture_t	*cursor_t;
	t_mini_map		mini_map;
	t_world			world;
	t_player		player;
	t_anim			anim;
	t_enemy			enemy;
	t_deplacement	dep;
	t_exit			exit;
}	t_cub;

// PARSING

void	open_map(t_map *map, char **argv);
int		check_floor_and_ceiling(t_map *map);
void	get_textures(t_map *map, char *line);
int		parsing_map(t_map *map, t_cub *cub);
void	check_cub(char *s);
int		rgb_to_hex(char *rgb);
int		**image_to_tab(mlx_image_t *image);
size_t	count_c(t_map *map, char c);

// RAYCASTING
void	init_raycast(t_cub *cub);
void	raycasting(t_cub *cub);
void	ft_add_back_raycast(t_ray **ray, t_cub *cub, float x, float y);
void	set_player_pos(t_cub *cub);
float	calc_ray_y(float dist_y, t_cub *cub);
float	calc_ray_x(float dist_x, t_cub *cub);
void	draw_ray(t_ray **ray, t_mini_map *mini_map, t_cub *cub, int color);
void	first_quadrant(t_cub *cub, int *i, int *j);
void	second_quadrant(t_cub *cub, int *i, int *j);
void	third_quadrant(t_cub *cub, int *i, int *j);
void	fourth_quadrant(t_cub *cub, int *i, int *j);

// MINIMAP

int		map_to_window(t_cub *cub, bool actualise);
int		init_data_mini_map(t_mini_map *minimap, t_map *map);
int		init_mini_map(t_cub *cub, t_mini_map *mini_map);

// GAME
void	open_window(t_cub *cub);
int		lets_go_3d(t_cub *cub);
int		draw_walls(t_cub *cub, t_ray *ray);
int		init_blink(t_cub *cub);
int		init_enemy(t_cub *cub);
void	stam_handling(t_cub *cub);
void	blink(t_cub *cub);

// MOVEMENT
void	move(t_cub *cub);
void	move_player(t_cub *cub, float dir, t_deplacement *dep);
void	rotations(double xpos, double ypos, void *param);

// DISPLAY
int		init_world(t_cub *cub);
void	fog(t_cub *cub);
void	draw_ray(t_ray **ray, t_mini_map *mini_map, t_cub *cub, int color);
void	drawline(t_ray *ray, t_mini_map *mini_map, t_player *player, int clor);
void	verticality(t_draw *draw, t_mini_map *mini_map, int color);
void	horizontal_right(t_draw draw, t_mini_map *mini_map, int color);
void	second_and_third_quadrant(t_draw draw, t_mini_map *mini_map, int color);
void	first_and_last_quadrant(t_draw draw, t_mini_map *mini_map, int color);
void	last_octan(t_draw draw, t_mini_map *mini_map, int color);
void	seventh_octan(t_draw draw, t_mini_map *mini_map, int color);
void	sixth_octan(t_draw draw, t_mini_map *mini_map, int color);
void	fifth_octan(t_draw draw, t_mini_map *mini_map, int color);
void	fourth_octan(t_draw draw, t_mini_map *mini_map, int color);
void	third_octan(t_draw draw, t_mini_map *mini_map, int color);
void	second_octant(t_draw draw, t_mini_map *mini_map, int color);
void	first_octan(t_draw draw, t_mini_map *mini_map, int color);
int		init_light(t_cub *cub);
void	put_wall_in3d(t_wall *wall, t_cub *cub, mlx_image_t *image, \
		int **pixel_tab);
void	disp_world_2(t_cub *cub, t_ray *ray, t_wall *wall);

// ENEMIES
void	set_enemy_pos(t_cub *cub);
void	put_enemy(t_cub *cub, t_ray *ray, int x);
int		init_death(t_cub *cub);
void	check_death(t_cub *cub);
void	move_enemy(t_cub *cub);

// INTERACTION
void	interaction(mlx_key_data_t key, void *param);
void	put_stamina(t_cub *cub);
int		close_door(t_cub *cub, int player_x, int player_y);
void	check_doors(t_cub *cub);
int		open_door(t_cub *cub, int player_x, int player_y);

// ANIMATION
void	init_anim(t_cub *cub);
void	anim_enemy(t_cub *cub);
void	blink_we(t_cub *cub);
void	blink_ea(t_cub *cub);
void	blink_no(t_cub *cub);
void	blink_so(t_cub *cub);
void	moving_light(t_cub *cub);

// ENEMIES
void	set_enemy_pos(t_cub *cub);
void	put_enemy(t_cub *cub, t_ray *ray, int x);
void	maths_enemy(t_cub *cub);

// EXIT
void	init_exit(t_cub *cub);
void	set_exit_pos(t_cub *cub);
void	maths_exit(t_cub *cub);
void	put_exit(t_cub *cub, t_ray *ray, int x);
void	check_exit(t_cub *cub);

// FREE AND DESTROY
void	free_map_stuff(t_map *map);
void	free_rays(t_ray *ray);
void	free_in_window(t_cub *cub);
void	destroyer(t_mini_map *mini, mlx_t *mlx, t_cub *cub);

// ERROR
void	print_error(char *msg);

// DEBUG

void	debug_nbr(char *color, char *msg, long long int content);
void	debug_str(char *color, char *msg, char *content);
void	debug_tab_nbr(char *color, char *msg, int *content, int size);
void	debug_char(char *color, char *msg, char content);
void	debug_float(char *color, char *msg, double content);
void	debug_tab_str(char *color, char *msg, char **content);

#endif

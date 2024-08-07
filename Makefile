NAME	= cub3D

LIBS	= MLX42/build/libmlx42.a -ldl -lglfw -pthread -lm

MLX_DIRECTORY = ./MLX42

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

SRCS	=	parsing/get_map.c \
			parsing/get_map_utils.c \
			parsing/parsing_map.c \
			parsing/parsing_utils.c \
			free_and_destroy/free_all.c \
			free_and_destroy/destroyer.c \
			game/init_game/open_window.c \
			game/init_game/init_things.c \
			game/display/raycasting_1.c \
			game/display/raycasting_2.c \
			game/display/raycasting_utils.c \
			game/display/drawline/draw_line.c \
			game/display/drawline/octans.c \
			game/display/drawline/utils.c \
			game/display/init_3D_world.c \
			game/display/3D_world_1.c \
			game/display/3D_world_2.c \
			game/display/fog.c \
			game/animation/init_walls_animation.c \
			game/animation/wall_ea_we.c \
			game/animation/wall_no_so.c \
			game/animation/light.c \
			game/animation/death.c \
			game/exit/exit_1.c \
			game/exit/exit_2.c \
			game/enemy/enemy_1.c \
			game/enemy/enemy_2.c \
			game/enemy/move_enemy.c \
			game/player/movement.c \
			game/player/movements_setup.c \
			game/player/interaction.c \
			game/player/stamina.c \
			minimap/minimap.c \
			minimap/init_textures.c \
			parsing/error.c

SRCS_MAIN	= main.c 

OBJS	= $(SRCS_MAIN:.c=.o) $(SRCS:.c=.o)

CC	= @cc

CFLAGS	+= -Wall -Wextra -Werror -g3 #-fsanitize=address

RM	= @rm -rf

CURRENT_DATE	:= $(shell date +"%Y-%m-%d %H:%M:%S")

all	: $(NAME)

$(NAME) : $(OBJS)
	@make --no-print-directory -C Libft
	$(CC) $(CFLAGS)  $(OBJS) Libft/libft.a $(LIBS) -o $(NAME)
	@echo "$(MAGENTA)Make Done$(DEF_COLOR)"

clean : 
	$(RM) $(OBJS) 
	@make --no-print-directory -C Libft clean
	@rm -rf $(LIBMLX)/build
	@echo "$(BLUE)OBJS CLEAR MY FRIEND!$(DEF_COLOR)"

fclean : 
	$(RM) $(NAME) $(OBJS)
	@make --no-print-directory -C Libft fclean
	@echo "$(MAGENTA)¯|_(ツ)_/¯ I'M SO PROUD OF U!$(DEF_COLOR)"

re :	fclean all

ex :	re clean
	@echo "$(GREEN)(•̀ᴗ•́)و ̑̑ALL FINE!(•̀ᴗ•́)و ̑̑$(DEF_COLOR)"

mlx_clean:
	@ rm -rf MLX42

mlx_install:
	@ git clone https://github.com/codam-coding-college/MLX42.git ${MLX_DIRECTORY}

mlx_init:
	@ cd ${MLX_DIRECTORY} && cmake -B build
	@ cd ${MLX_DIRECTORY} && cmake --build build -j4

mlx_re: mlx_clean mlx_install mlx_init

git	:	fclean
	@$(RM) */a.out a.out
	@git add . > /dev/null 2>&1
	@@msg=$${MSG:-"$(CURRENT_DATE)"}; git commit -m "$(USER) $$msg" > /dev/null 2>&1 
	@git push > /dev/null 2>&1
	@echo "$(GREEN)(•̀ᴗ•́)و ̑̑GIT UPDATE!(•̀ᴗ•́)و ̑̑$(DEF_COLOR)"

norm :
	@norminette *.c *.h | grep -i -E 'Error' || norminette *.c *.h 
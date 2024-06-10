NAME	= cub3D

LIBS	= .MLX42/build/libmlx42.a -ldl -lglfw -pthread -lm

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
			parsing/parsing_map.c \
			parsing/parsing_utils.c \
			free_and_destroy/free_all.c \
			game/open_window.c \
			game/raycasting.c \
			error.c

SRCS_MAIN	= main.c debug_stderr.c

OBJS	= $(SRCS_MAIN:.c=.o) $(SRCS:.c=.o)

CC	= @cc

CFLAGS	+= -Wall -Wextra -Werror -g3 -fsanitize=address

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

git	:	fclean
	@$(RM) */a.out a.out
	@git add . > /dev/null 2>&1
	@@msg=$${MSG:-"main $(CURRENT_DATE)"}; git commit -m "$$msg main $(CURRENT_DATE)" > /dev/null 2>&1 
	@git push > /dev/null 2>&1
	@echo "$(GREEN)(•̀ᴗ•́)و ̑̑GIT UPDATE!(•̀ᴗ•́)و ̑̑$(DEF_COLOR)"

norm :
	@norminette *.c *.h | grep -i -E 'Error' || norminette *.c *.h 
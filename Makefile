CC          = /usr/bin/gcc

NAME        = fractol

SRCDIR      = ./

SRC         =	fractol.c	\
		ft_init.c	\
		mandelbrot.c	\
		julia.c  \
		ft_keypress.c 

OBJ         = $(SRC:.c=.o)

LDFLAGS     = -L/usr/X11/lib -lmlx -lX11 -lXext -L libft -lft

CFLAGS      = -Wall -Werror -Wextra

RM          = rm -rf

all:        $(NAME)

$(NAME):    $(OBJ)
			make -C libft
			@echo "\033[1;32m[Linking] \t\033[0m: \033[0;32m" | tr -d '\n'
			$(CC) -o $@ $^ $(LDFLAGS)
			@echo "\033[0m" | tr -d '\n'

clean:
			@echo "\033[1;33m[Cleaning] \t\033[0m: \033[0;31m" | tr -d '\n'
			$(RM) $(OBJ)
			@echo "\033[0m" | tr -d '\n'

fclean:     clean
			make fclean -C libft
			@echo "\033[1;31m[Fcleaning] \t\033[0m: \033[0;31m" | tr -d '\n'
			$(RM) $(NAME)
			@echo "\033[0m" | tr -d '\n'

re:         fclean all

%.o:        %.cpp
			@echo "\033[1;36m[Compiling] \t\033[0m: \033[1;37m" | tr -d '\n'
			$(CC) $(CFLAGS) -c $< -o $@
			@echo "\033[0m" | tr -d '\n'

.PHONY:     all clean re fclean
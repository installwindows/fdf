NAME=fdf
SRC=fdf.c \
	parse.c \
	hook.c \
	world.c \
	graphic.c \
	image.c \
	gnl.c
LIB=-Llibft \
	-Lft_printf \
	-Lmlx
INC=-Ilibft \
	-Ift_printf \
	-I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks/Tk.framework/Versions/8.4/Headers \
	-Imlx

.PHONY: all clean fclean re

all: $(NAME)

$(NAME):
	make -C libft
	make -C ft_printf
	make -C mlx
	gcc -Wall -Werror -Wextra -o $(NAME) $(SRC) $(LIB) $(INC) -framework OpenGL -framework AppKit -lft -lmlx -lftprintf
clean:
	make -C libft clean
	make -C ft_printf clean
	make -C mlx clean

fclean: clean
	rm -rf $(NAME)
	make -C libft fclean
	make -C ft_printf fclean

re: fclean all

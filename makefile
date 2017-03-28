NAME=fdf
SRC=fdf.c \
	hook.c \
	world.c \
	graphic.c \
	gnl.c
LIB=libft.a \
	libftprintf.a \
	libmlx.a

all: $(NAME)

$(NAME):
	gcc -o $(NAME) $(SRC) $(LIB) -g -framework OpenGL -framework AppKit

clean:

fclean: clean
	rm -rf $(NAME)

linux:
	gcc -o $(NAME) $(SRC) $(LIB) -g -lXext -lX11 -lm

re: fclean all

rel: fclean linux

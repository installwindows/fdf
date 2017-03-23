NAME=fdf
SRC=fdf.c \
	get_next_line.c
LIB=libft.a \
	libftprintf.a \
	libmlx.a

all: $(NAME)

$(NAME):
	gcc -o $(NAME) $(SRC) $(LIB) -g -framework OpenGL -framework AppKit

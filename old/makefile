SRC = fdf.c

all: libft
	gcc $(SRC) -L. -Llibft/ -lmlx -framework OpenGL -framework AppKit -lft -Ilibft

linux: libft
	gcc $(SRC) -L. -Llibft/ -lmlx -lXext -lX11 -lft -Ilibft

libft:
	make -C libft/

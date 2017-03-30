NAME=fdf
SRC=fdf.c \
	parse.c \
	hook.c \
	world.c \
	graphic.c \
	image.c \
	gnl.c
LIB=libft.a \
	libftprintf.a \
	libmlx.a

all: $(NAME)

$(NAME):
	gcc -o $(NAME) $(SRC) $(LIB) -g -framework OpenGL -framework AppKit -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks/Tk.framework/Versions/8.4/Headers

clean:

fclean: clean
	rm -rf $(NAME)

linux:
	gcc -o $(NAME) $(SRC) $(LIB) -g -lXext -lX11 -lm

re: fclean all

rel: fclean linux

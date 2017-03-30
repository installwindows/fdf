# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/03 15:46:41 by varnaud           #+#    #+#              #
#    Updated: 2017/03/29 23:05:26 by varnaud          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = ft_printf.c \
	  handle_string.c \
	  handle_wcstr.c \
	  handle_snumber.c \
	  handle_unumber.c \
	  print_arg.c \
	  do_conversion.c \
	  s_conversion.c \
	  ls_conversion.c \
	  p_conversion.c \
	  d_conversion.c \
	  ld_conversion.c \
	  i_conversion.c \
	  o_conversion.c \
	  lo_conversion.c \
	  u_conversion.c \
	  lu_conversion.c \
	  x_conversion.c \
	  cx_conversion.c \
	  c_conversion.c \
	  lc_conversion.c \
	  b_conversion.c \
	  f_conversion.c \
	  bignum.c \
	  floating_point.c \
	  mtp.c \
	  error_conversion.c

OBJ = $(SRC:.c=.o)
OBJLIB = libft/*.o

all: $(NAME)

$(NAME):
	make -C libft/
	gcc -c -Wall -Werror -Wextra  $(SRC) -Ilibft/
	ar rc $(NAME) $(OBJ) $(OBJLIB)
	ranlib $(NAME)

clean:
	make -C libft clean
	rm -rf $(OBJ)

fclean: clean
	make -C libft fclean
	rm -rf $(NAME)

re: fclean all

test:
	gcc basic.c $(SRC) -Ilibft/ -Llibft/ -lft -g

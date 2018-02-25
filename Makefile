# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: earteshc <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/30 14:59:46 by earteshc          #+#    #+#              #
#    Updated: 2018/01/30 15:27:33 by earteshc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
CC = @gcc
CFLAGS = -Wall -Wextra -Werror -Ilib/includes

FT_LS = main.c dir_operation.c flags_operations.c list_output.c sort_args_operation.c sort_operations.c

OBJ = $(FT_LS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Compiling libft wait..."
	@make -C ./lib/
	@echo "Compiling ft_ls wait..."
	@gcc -L ./lib/ -lft $(OBJ) -o $(NAME)
	@echo "Done."

clean:
	@make -C ./lib/ clean
	@/bin/rm -f $(OBJ)

fclean: clean
	@make -C ./lib/ fclean
	@/bin/rm -f $(NAME)

re: fclean all

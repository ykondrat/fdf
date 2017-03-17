# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ykondrat <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/16 13:11:22 by ykondrat          #+#    #+#              #
#    Updated: 2017/02/17 11:07:30 by ykondrat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRC = fdf_additional_func.c\
	  fdf_create_struct.c\
	  fdf_create_win.c\
	  fdf_draw_line.c\
	  fdf_error.c\
	  fdf_key_event.c\
	  fdf_main.c\
	  fdf_start_draw_map.c\
	  fdf_validation.c

LIB = -L libft -lft

SRC_O = $(SRC:.c=.o)

INC = fdf.h

INC_LIB = libft/libft.h

FLAG = -Wall -Werror -Wextra

MLX_FLAG = -lmlx -framework OpenGL -framework AppKit

all: $(NAME)
	
$(NAME): $(SRC_O) $(INC_LIB) $(INC)
	@echo "\033[33mCompiling library..."
	@make -C libft
	@echo "\033[33mCompiling project...\033[0m"
	gcc $(FLAG) $(SRC) $(LIB) $(MLX_FLAG)
	gcc -o $(NAME) $(SRC_O) $(LIB) $(MLX_FLAG)
	@rm -f a.out
	@echo "\033[32mSuccess!!!"
	@echo "\033[32;03mReady to go =)"

clean:
	@echo "\033[31mRemoving objects...\033[0m"
	rm -f $(SRC_O)
	@make clean -C libft

fclean: clean
	@echo "\033[31mRemoving executable\033[0m"
	rm -f $(NAME)
	@make fclean -C libft

re: fclean all

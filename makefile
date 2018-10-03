# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chadams <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/17 05:33:17 by chadams           #+#    #+#              #
#    Updated: 2018/09/17 05:43:14 by chadams          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC = main.c\
	  readline.c\
	  forkloop.c\
	  extras.c\
	  env.c\
	  env_sub.c\
	  cd.c\
	  builtins.c\
	  bonus.c
OBJ = $(SRC:.c=.o)
CC = gcc
FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME):
	@$(CC) -c $(FLAGS) $(addprefix srcs/, $(SRC))
	@$(CC) -o $(NAME) $(OBJ) ./libft/libft.a
	@echo "Minishell bin compiled."

clean:
	@rm -f $(OBJ)
	@echo "Objects removed."

fclean: clean

re: fclean all

norm:
	@norminette srcs/*.c

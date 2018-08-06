#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkellehe <jkellehe@student.42.us.org>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/04 15:54:32 by jkellehe          #+#    #+#              #
#    Updated: 2018/08/06 12:19:32 by jkellehe         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = fillit

SRC = semi.c full.c solve.c resolve.c reprinter.c

HEADER = header.h

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	@gcc -c -Wall -Wextra -Werror $(SRC)
	@gcc $(OBJ) -o $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

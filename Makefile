#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkellehe <jkellehe@student.42.us.org>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/04 15:54:32 by jkellehe          #+#    #+#              #
#    Updated: 2018/08/05 17:24:12 by jkellehe         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = fillit

SRC = *.c

HEADER = header.h

all: $(NAME)

$(NAME):
	@gcc -Wall -Wextra -Werror $(SRC) -o $(NAME)

clean:

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgonor <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/28 17:33:27 by dgonor            #+#    #+#              #
#    Updated: 2019/01/28 17:33:40 by dgonor           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= 	avm

FLAGS	= 	-Wall -Wextra -Werror -std=c++11
SRC		=	ClassAbstractVM.cpp \
			main.cpp \
			ClassFactory.cpp

OBJ		=	$(SRC:.cpp=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
			@clang++ $(FLAGS) $(OBJ) -o $(NAME)
			@echo " \033[1;92mDone!\033[0m"

$(OBJ):
			@clang++ -c $(FLAGS) $(SRC)
			@echo "\033[42m  \033[0m\c"

clean:
			@rm -rf $(OBJ)

fclean:		clean
			@rm -f $(NAME)
			@echo "\033[1;91mFCleaned\033[0m"

re:			fclean all

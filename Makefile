##
## EPITECH PROJECT, 2024
## Arcade
## File description:
## Makefile
##

NAME = arcade

SRC = ./core/core.cpp 		\
	  ./core/Parsing.cpp 	\
	  ./core/GameState.cpp 	\

OTHER_MAKEFILE	=	./graphicals

CFLAGS 	= -std=c++20 -Wall -g3

all: $(NAME)

$(NAME):
	g++ -o $(NAME) $(SRC) $(CFLAGS)
	make -C $(OTHER_MAKEFILE)

valgrind: $(NAME)
	clear
	valgrind ./$(NAME) | cat -e

style:	fclean
	coding-style . .
	clear
	cat coding-style-reports.log
	rm -f coding-style-reports.log

clean :
	find -name "*~" -delete
	find -name "#**#" -delete
	find -name "*.gcno" -delete
	find -name "*.gcda" -delete
	find -name "vgcore.*" -delete
	make -C $(OTHER_MAKEFILE) clean

fclean : clean
	rm -f $(NAME)
	make -C $(OTHER_MAKEFILE) fclean

re : fclean $(NAME)
	make -C $(OTHER_MAKEFILE) re

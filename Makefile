##
## EPITECH PROJECT, 2024
## Arcade
## File description:
## Makefile
##

NAME = arcade

DIR_COMPONENTS = ./src/core/core.cpp 		\
				 ./src/core/IGame.cpp 		\
				 ./src/core/IGraphical.cpp 	\

SRC = $(DIR_COMPONENTS)

CFLAGS 	= -std=c++20 -Wall -g3

all: $(NAME)

$(NAME):
	g++ -o $(NAME) $(SRC) $(CFLAGS)

graphicals:
	g++ -shared -o arcade_sfml.so src/graphicals/arcade_sfml.cpp -fPIC
	mv arcade_sfml.so src/lib/

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

fclean : clean
	rm -f $(NAME)

re : fclean $(NAME)

##
## EPITECH PROJECT, 2024
## Arcade
## File description:
## Makefile
##

NAME = ../../lib/arcade_sfml.so

SRC = arcade_sfml.cpp			\
	  ../../core/GameState.cpp

CFLAGS 	= -std=c++20 -Wall -g3

SFMLFLAGS	=	-lsfml-graphics -lsfml-window -lsfml-system -shared -fPIC

all: $(NAME)

$(NAME):
	g++ -o $(NAME) $(SRC) $(CFLAGS) $(SFMLFLAGS)

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

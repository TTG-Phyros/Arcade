##
## EPITECH PROJECT, 2024
## Arcade
## File description:
## Makefile
##

NAME = ../../lib/arcade_sdl2.so

SRC = arcade_sdl2.cpp			\
	  ../../core/GameState.cpp

CFLAGS 	= -std=c++20 -Wall -g3

SDLFLAGS	=	-lSDL2 -lSDL2_ttf -shared -fPIC

all: $(NAME)

$(NAME):
	g++ -o $(NAME) $(SRC) $(CFLAGS) $(SDLFLAGS)

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

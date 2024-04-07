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

CFLAGS 	= -std=c++20 -Wall -g3 -fno-gnu-unique

all: $(NAME)

$(NAME):
	g++ -o $(NAME) $(SRC) $(CFLAGS)
	make -C ./graphicals re
	make -C ./games re

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
	make -C ./graphicals clean
	make -C ./games clean

fclean : clean
	rm -f $(NAME)
	make -C ./graphicals fclean
	make -C ./games fclean

re : fclean $(NAME)

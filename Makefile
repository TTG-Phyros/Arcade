##
## EPITECH PROJECT, 2024
## teck2
## File description:
## Makefile
##

NAME = arcade

DIR_COMPONENTS = main.cpp \

SRC = $(DIR_COMPONENTS)

CFLAGS 	= -std=c++20 -Wall -g3

all: $(NAME)

$(NAME):
	g++ -o $(NAME) $(SRC) $(CFLAGS)

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

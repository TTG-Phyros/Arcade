/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** testGraphic
*/

#include <cstdlib>
#include <curses.h>
#include <iostream>
#include <unistd.h>

extern "C" void mainMenu ()
{
    std::cout << "Main Menu test" << std::endl;
    initscr();
    raw();
    noecho();


    while (true) {
        std::string games[] = {"arcade_snake.so", "arcade_nibbler.so"};
        std::string graphics[] = {"arcade_ncurses.so", "arcade_sdl2.so", "arcade_sfml.so"};
        wclear(stdscr);
        sleep(1);

        WINDOW *mainMenu = subwin(stdscr, 20, 60, 0, 0);
        box(mainMenu, '|', '-');
        mvwprintw(mainMenu, 0, 26, " Arcade ");
        WINDOW *gameMenu = subwin(mainMenu, 18, 19, 1, 1);
        box(gameMenu, '|', '-');
        mvwprintw(gameMenu, 0, 6, " Games ");
        // for (int i = 0; games[i] != ""; i++)
        //     mvwprintw(gameMenu, (2 * (i + 1)), 2, games[i].c_str());
        WINDOW *graphicMenu = subwin(mainMenu, 18, 19, 1, 20);
        box(graphicMenu, '|', '-');
        mvwprintw(graphicMenu, 0, 4, " Graphics ");
        // for (int i = 0; graphics[i] != ""; i++)
        //     mvwprintw(graphicMenu, (2 * (i + 1)), 2, graphics[i].c_str());
        WINDOW *scoreMenu = subwin(mainMenu, 18, 19, 1, 39);
        box(scoreMenu, '|', '-');
        mvwprintw(scoreMenu, 0, 6, " Score ");
        wrefresh(stdscr);
    }
    endwin();
}

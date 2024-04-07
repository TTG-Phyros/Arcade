/*
** EPITECH PROJECT, 2024
** Untitled (Workspace)
** File description:
** ncursemenu
*/

#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <ncurses.h>
#include <curses.h>
#include <string>
#include <vector>
#include <unistd.h>
#include "../../core/GameState.hpp"
#include "../../core/IGraph.hpp"

class MainMenu : public arcade::IGraph {
public:
    MainMenu();
    ~MainMenu();

    void displayMenu(arcade::GameState &gameState);
    void displayGame(arcade::GameState &gameState);
    arcade::libType getLibType();
    void displayWindow(arcade::GameState &gameState);

private:
    void displayHeader();
    void displayGameMenu(const std::vector<std::string>& games, int selectedGameIndex);
    void displayGraphicMenu(const std::vector<std::string>& graphics, int selectedGraphicIndex, int selectedCategory);
    void displayScoreMenu(std::map<std::string, int> scores);
    void handleInput(int ch, int numGames, int numGraphics, arcade::GameState &gameState);
    void printSelectedGameAndGraphic(const std::string& selectedGame, const std::string& selectedGraphic);
    void drawMap(std::vector<std::string> gamemap);
    void inputHandler(arcade::GameState &gameState);
    int selectedGameIndex = 0;
    int selectedGraphicIndex = 0;
    int selectedCategory = 0; // 0: games, 1: graphics
    WINDOW *gameMenu = subwin(stdscr, 17, 29, 1, 1);
    WINDOW *mainMenu = subwin(stdscr, 21, 90, 0, 0);
    WINDOW *graphicMenu = subwin(stdscr, 17, 29, 1, 30);
    WINDOW *scoreMenu = subwin(stdscr, 17, 29, 1, 59);
    WINDOW *mapgaming = subwin(stdscr, 30, 90, 0, 0);
    std::string username;
};

#endif /* MAIN_HPP */

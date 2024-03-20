/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** core
*/

#include "IGame.hpp"
#include "IGraphical.hpp"
#include <iostream>

int main (int ac, char **av)
{
    try {
        Game::IGame *game = new Game::IGame("./src/lib/testGame.so");
        game->inputHandler();
        game->gameLoop();
        game->display();
    } catch (Game::GameError &error) {
        std::cout << error.what() << std::endl;
    }
    try {
        Graphical::IGraphical *graphical = new Graphical::IGraphical("./src/lib/testGraphic.so");
        graphical->mainMenu();
    } catch (Graphical::GraphicalError &error) {
        std::cout << error.what() << std::endl;
    }
}

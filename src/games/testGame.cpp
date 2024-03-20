/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** testGame
*/

#include <iostream>

extern "C" void gameLoop ()
{
    std::cout << "GameLoop test" << std::endl;
}

extern "C" void inputHandler ()
{
    std::cout << "InputHandler test" << std::endl;
}

extern "C" void display ()
{
    std::cout << "Display test" << std::endl;
}

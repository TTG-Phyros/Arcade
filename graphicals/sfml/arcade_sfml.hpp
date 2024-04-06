/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-arcade
** File description:
** arcade_sfml
*/

#ifndef ARCADE_SFML_HPP_
#define ARCADE_SFML_HPP_

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem> //std::filesystem
#include "../../core/IGraph.hpp"
#include "../../core/ILib.hpp"

#define WINDOW_SIZE_X 1900
#define WINDOW_SIZE_Y 1000

class MenuPrincipal : public arcade::IGraph {
    public:
        MenuPrincipal();
        ~MenuPrincipal();
        arcade::libType getLibType();
        void displayWindow(arcade::GameState &gameState);
        void display(arcade::GameState &gameState);
        void conditionsKey(arcade::GameState &gameState);

        mutable sf::RectangleShape r_graphics;
        mutable sf::Font font;
        mutable sf::Text text;
        mutable std::vector<int> selection;
        sf::RenderWindow wdw;
};

#endif /* !ARCADE_SFML_HPP_ */

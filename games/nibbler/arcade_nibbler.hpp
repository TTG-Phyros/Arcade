/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-arcade
** File description:
** arcade_nibbler
*/

#ifndef ARCADE_NIBBLER_HPP_
#define ARCADE_NIBBLER_HPP_

#include <iostream>
#include <vector>
#include <sstream>
#include <thread>     // Pour std::this_thread
#include <chrono>     // Pour std::chrono
#include "../../core/IGame.hpp"
#include "../../core/ILib.hpp"
#include "../../core/Parsing.hpp"

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

class nibbler : public arcade::IGame {
    public:
        nibbler();
        ~nibbler();

        std::vector<std::string> getMazeUpdated();
        void conditionsKey(arcade::keyPressed key);

        void moveSnakeBody(int saveSnakeX, int saveSnakeY);
        void moveSnakeHead();
        arcade::libType getLibType();
        void updateGameState(arcade::GameState &gameState);

    private:
        // Taille de la grille de jeu
        int width;
        int height;

        // Position de la tête du serpent et de la nourriture
        int snakeX, snakeY, fruitX, fruitY;

        // Direction initiale du serpent
        Direction dir = STOP;

        // Longueur et coordonnées du corps du serpent
        std::vector<int> tailX, tailY;

        // Variable de jeu
        bool gameOver = false;
        int score = 0;
        std::vector<std::string> maze = {
            "XXXXXXXXXXXXXXXXXXX",
            "X   XX   X   XX   X",
            "X X    X X X    X X",
            "X XXXX   X   XXXX X",
            "X                 X",
            "XX  XXX XXX XXX  XX",
            "X    X  XXX  X    X",
            "X                 X",
            "XX XX  X   X  XX XX",
            "XX XX  XX XX  XX XX",
            "XX XX  X   X  XX XX",
            "X                 X",
            "X    X  XXX  X    X",
            "XX  XXX XXX XXX  XX",
            "X                 X",
            "X XXXX   X   XXXX X",
            "X X    X X X    X X",
            "X   XX   X   XX   X",
            "XXXXXXXXXXXXXXXXXXX"
        };
};

#endif /* !ARCADE_NIBBLER_HPP_ */

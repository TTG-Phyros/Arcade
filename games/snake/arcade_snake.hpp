/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-arcade
** File description:
** arcade_snake
*/

#ifndef ARCADE_SNAKE_HPP_
#define ARCADE_SNAKE_HPP_

#include "../../core/IGame.hpp"
#include "../../core/ILib.hpp"
#include <iostream>
#include <vector>
#include <sstream>
#include <thread>     // Pour std::this_thread
#include <chrono>     // Pour std::chrono

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

class snake : public arcade::IGame {
    public:
        snake();
        ~snake();

        void updateGameState(arcade::GameState &gameState);
        void conditionsKey(arcade::keyPressed key);

        bool getGameOver() { return gameOver; }
        arcade::libType getLibType();
        std::vector<std::string> getMazeUpdated();

    private:
        // Taille de la grille de jeu
        const int width = 20;
        const int height = 20;

        // Position de la tête du serpent et de la nourriture
        int snakeX, snakeY, fruitX, fruitY;

        // Direction initiale du serpent
        Direction dir;

        // Longueur et coordonnées du corps du serpent
        int tailX[100], tailY[100];
        int nTail;

        // Variable de jeu
        bool gameOver;
        int score;
        std::vector<std::string> maze;
};

#endif /* !ARCADE_SNAKE_HPP_ */

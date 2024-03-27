/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-arcade
** File description:
** arcade_snake
*/

#ifndef ARCADE_SNAKE_HPP_
#define ARCADE_SNAKE_HPP_

#include <iostream>
#include <vector>
#include <sstream>
#include <thread>     // Pour std::this_thread
#include <chrono>     // Pour std::chrono

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

class snake
{
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

    public:
        snake();
        ~snake();

        void update();
        void display();
        void conditionsKey(int key);

        bool getGameOver() { return gameOver; }
};

#endif /* !ARCADE_SNAKE_HPP_ */

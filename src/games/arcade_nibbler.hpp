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

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

class nibbler
{
    private:
        // Taille de la grille de jeu
        int width;
        int height;

        // Position de la tête du serpent et de la nourriture
        int snakeX, snakeY, fruitX, fruitY;

        // Direction initiale du serpent
        Direction dir;

        // Longueur et coordonnées du corps du serpent
        std::vector<int> tailX, tailY;

        // Variable de jeu
        bool gameOver;
        int score;
        std::vector<std::string> maze;

    public:
        nibbler();
        ~nibbler();

        void update();
        void display();
        void conditionsKey(int key);

        bool getGameOver() { return gameOver; }
};

#endif /* !ARCADE_NIBBLER_HPP_ */

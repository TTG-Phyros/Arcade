/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-arcade
** File description:
** arcade_snake
*/

#include "arcade_snake.hpp"

snake::snake()
{
    // Position initiale du serpent
    snakeX = width / 2;
    snakeY = height / 2;
    nTail = 3;
    for (int i = 0; i < nTail; i++) {
        tailX[i] = snakeX;
        tailY[i] = snakeY - (1 + i);
    }

    // Position initiale de la nourriture
    srand(time(NULL));
    fruitX = rand() % width;
    fruitY = rand() % height;

    // Direction initiale du serpent
    dir = DOWN;

    // Initialisation des variables de jeu
    gameOver = false;
    score = 0;
}

snake::~snake()
{
}

void snake::conditionsKey(arcade::keyPressed key)
{
    switch (key) {
        case arcade::keyPressed::LEFT_KEY: // Flèche gauche
            dir = LEFT;
            break;
        case arcade::keyPressed::RIGHT_KEY: // Flèche droite
            dir = RIGHT;
            break;
        case arcade::keyPressed::UP_KEY: // Flèche haut
            dir = UP;
            break;
        case arcade::keyPressed::DOWN_KEY: // Flèche bas
            dir = DOWN;
            break;
        case arcade::keyPressed::ESC_KEY: // Touche ESC
            gameOver = true;
            break;
        case arcade::keyPressed::SPACE_KEY:
            break;
        case arcade::keyPressed::NOTHING:
            break;
    }
}

void snake::updateGameState(arcade::GameState &gameState)
{
    this->conditionsKey(gameState.getKey());
    // Gestion des collisions avec la nourriture
    if (snakeX == fruitX && snakeY == fruitY) {
        nTail++; // Augmente la taille du serpent
        fruitX = rand() % width;
        fruitY = rand() % height;
        score += 10;
    }

    // Met à jour la position du corps du serpent
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = snakeX;
    tailY[0] = snakeY;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // Met à jour la position de la tête du serpent
    switch (dir) {
        case LEFT:
            snakeX--;
            break;
        case RIGHT:
            snakeX++;
            break;
        case UP:
            snakeY--;
            break;
        case DOWN:
            snakeY++;
            break;
        default:
            break;
    }

    // Gestion des collisions avec les bords de la grille
    if (snakeX >= width)
        snakeX = 0;
    else if (snakeX < 0)
        snakeX = width - 1;
    if (snakeY >= height)
        snakeY = 0;
    else if (snakeY < 0)
        snakeY = height - 1;

    // Gestion des collisions avec le corps du serpent
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == snakeX && tailY[i] == snakeY) {
            gameOver = true;
            gameState.setState(arcade::screenState::GAME_END);
            gameState.setScore(score);
        }
    if (gameOver == false) {
        gameState.setGameArray(this->getMazeUpdated());
    }
}

std::vector<std::string> snake::getMazeUpdated()
{
    std::string temp;
    maze.clear();
    // Dessine la grille
    for (int i = 0; i < width + 2; i++)
        temp += 'X';
    maze.push_back(temp);
    temp.clear();

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                temp += 'X';

            if (i == snakeY && j == snakeX)
                temp += 'O'; // Dessine la tête du serpent
            else if (i == fruitY && j == fruitX)
                temp += 'F'; // Dessine la nourriture
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        temp += 'o'; // Dessine le corps du serpent
                        print = true;
                    }
                }
                if (!print)
                    temp += ' ';
            }

            if (j == width - 1)
                temp += 'X';
        }
        maze.push_back(temp);
        temp.clear();
    }

    for (int i = 0; i < width + 2; i++)
        temp += 'X';
    maze.push_back(temp);
    temp.clear();
    return maze;
}

arcade::libType snake::getLibType()
{
    return arcade::libType::GAME;
}

extern "C" snake *instance(void)
{
    return new snake();
}

/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-arcade
** File description:
** arcade_nibbler
*/

#include "arcade_nibbler.hpp"

nibbler::nibbler()
{
    // Position initiale du serpent
    width = maze[0].size() - 1;
    height = maze.size() - 1;
    snakeX = width / 2;
    snakeY = 10;
    for (int i = 0; i < 3; i++) {
        tailX.push_back(snakeX);
        tailY.push_back(snakeY - (1 + i));
    }

    // Position initiale de la nourriture
    srand(time(NULL));
    fruitX = rand() % width;
    fruitY = rand() % height;
    while (maze[fruitY][fruitX] != ' ') {
        fruitX = rand() % width;
        fruitY = rand() % height;
    }
}

nibbler::~nibbler()
{
}

void nibbler::moveSnakeHead()
{
    maze[snakeY][snakeX] = ' ';
    switch (dir) {
        case LEFT:
            if (maze[snakeY][snakeX - 1] == 'X') {
                dir = STOP;
            } else
                snakeX--;
            break;
        case RIGHT:
            if (maze[snakeY][snakeX + 1] == 'X') {
                dir = STOP;
            } else
                snakeX++;
            break;
        case UP:
            if (maze[snakeY - 1][snakeX] == 'X') {
                dir = STOP;
            } else
                snakeY--;
            break;
        case DOWN:
            if (maze[snakeY + 1][snakeX] == 'X') {
                dir = STOP;
            } else
                snakeY++;
            break;
        default:
            break;
    }
}

void nibbler::moveSnakeBody(int saveSnakeX, int saveSnakeY)
{
    // Met à jour la position du corps du serpent
    if (dir != STOP) {
        int prevX = tailX[0];
        int prevY = tailY[0];
        int prev2X, prev2Y;
        maze[tailY[0]][tailX[0]] = ' ';
        tailX[0] = saveSnakeX;
        tailY[0] = saveSnakeY;
        int size = tailX.size();
        for (int i = 1; i < size; i++) {
            prev2X = tailX[i];
            prev2Y = tailY[i];
            maze[tailY[i]][tailX[i]] = ' ';
            tailX[i] = prevX;
            tailY[i] = prevY;
            prevX = prev2X;
            prevY = prev2Y;
        }
    }
}

void nibbler::updateGameState(arcade::GameState &gameState)
{
    this->conditionsKey(gameState.getKey());
    // Gestion des collisions avec la nourriture
    if (snakeX == fruitX && snakeY == fruitY) {
        tailX.push_back(0);
        tailY.push_back(0); // Augmente la taille du serpent
        fruitX = rand() % width;
        fruitY = rand() % height;
        while (maze[fruitY][fruitX] != ' ') {
        fruitX = rand() % width;
        fruitY = rand() % height;
        }
        score += 10;
    }

    int saveSnakeX = snakeX;
    int saveSnakeY = snakeY;

    moveSnakeHead();

    // Gestion des collisions avec les murs
    if (maze[snakeY][snakeX] == 'X') {
        std::cout << "maze[" << snakeY << "][" << snakeX << "] == 'X'" << std::endl;
        dir = STOP;
    }

    moveSnakeBody(saveSnakeX, saveSnakeY);

    // Gestion des collisions avec le corps du serpent
    int size = tailX.size();
    for (int i = 0; i < size; i++)
        if (tailX[i] == snakeX && tailY[i] == snakeY) {
            gameOver = true;
            gameState.setState(arcade::screenState::GAME_END);
            gameState.setScore(score);
        }
    if (gameOver == false) {
        gameState.setGameArray(this->getMazeUpdated());
    }
}

std::vector<std::string> nibbler::getMazeUpdated()
{
    maze[fruitY][fruitX] = 'F';
    int size = tailX.size();
    for (int i = 0; i < size; i++) {
        maze[tailY[i]][tailX[i]] = 'o';
    }
    maze[snakeY][snakeX] = 'O';
    return maze;
}

void nibbler::conditionsKey(arcade::keyPressed key)
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

arcade::libType nibbler::getLibType()
{
    return arcade::libType::GAME;
}

extern "C" nibbler *instance()
{
    return new nibbler();
}

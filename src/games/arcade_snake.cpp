/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-arcade
** File description:
** arcade_snake
*/

#include "arcade_snake.hpp"
#include <termios.h> // pour tcgetattr, tcsetattr
#include <fcntl.h> // pour fcntl

int kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

int main()
{
    snake game;
    while (game.getGameOver() == false) {
        if (kbhit()) {
            char input = getchar();
            if (input == 'z')
                game.conditionsKey(72);
            if (input == 's')
                game.conditionsKey(80);
            if (input == 'd')
                game.conditionsKey(77);
            if (input == 'q')
                game.conditionsKey(75);
        }
        game.update();
        game.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000/2));
    }
    std::cout << "Game Over" << std::endl;
    return 0;
}

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

void snake::update()
{
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
        if (tailX[i] == snakeX && tailY[i] == snakeY)
            gameOver = true;
}

void snake::display()
{
    // Dessine la grille
    for (int i = 0; i < width + 2; i++)
        maze += '_';
    maze += '\n';

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                maze += '|';

            if (i == snakeY && j == snakeX)
                maze += 'O'; // Dessine la tête du serpent
            else if (i == fruitY && j == fruitX)
                maze += 'F'; // Dessine la nourriture
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        maze += 'o'; // Dessine le corps du serpent
                        print = true;
                    }
                }
                if (!print)
                    maze += ' ';
            }

            if (j == width - 1)
                maze += '|';
        }
        maze += '\n';
    }

    for (int i = 0; i < width + 2; i++)
        maze += '_';
    maze += '\n';

    std::cout << maze << "Score :" << score << std::endl;
}

void snake::conditionsKey(int key)
{
    switch (key) {
        case 75: // Flèche gauche
            dir = LEFT;
            break;
        case 77: // Flèche droite
            dir = RIGHT;
            break;
        case 72: // Flèche haut
            dir = UP;
            break;
        case 80: // Flèche bas
            dir = DOWN;
            break;
        case 36: // Touche ESC
            gameOver = true;
            break;
        }
}

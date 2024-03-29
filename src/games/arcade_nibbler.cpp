/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-arcade
** File description:
** arcade_nibbler
*/

#include "arcade_nibbler.hpp"
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
    nibbler game;
    while (game.getGameOver() == false) {
        std::cout << "___________________________" << std::endl;
        game.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000/2));
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
    }
    std::cout << "Game Over" << std::endl;
    return 0;
}

nibbler::nibbler()
{
    maze.push_back("XXXXXXXXXXXXXXXXXXX");//0
    maze.push_back("X   XX   X   XX   X");
    maze.push_back("X X    X X X    X X");
    maze.push_back("X XXXX   X   XXXX X");
    maze.push_back("X                 X");
    maze.push_back("XX  XXX XXX XXX  XX");
    maze.push_back("X    X  XXX  X    X");
    maze.push_back("X                 X");
    maze.push_back("XX XX  X   X  XX XX");
    maze.push_back("XX XX  XX XX  XX XX");
    maze.push_back("XX XX  X   X  XX XX");
    maze.push_back("X                 X");
    maze.push_back("X    X  XXX  X    X");
    maze.push_back("XX  XXX XXX XXX  XX");
    maze.push_back("X                 X");
    maze.push_back("X XXXX   X   XXXX X");
    maze.push_back("X X    X X X    X X");
    maze.push_back("X   XX   X   XX   X");
    maze.push_back("XXXXXXXXXXXXXXXXXXX");//18

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

    // Direction initiale du serpent
    dir = STOP;

    // Initialisation des variables de jeu
    gameOver = false;
    score = 0;
}

nibbler::~nibbler()
{
}

void nibbler::update()
{
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

    // Met à jour la position de la tête du serpent
    int saveSnakeX = snakeX;
    int saveSnakeY = snakeY;
    maze[snakeY][snakeX] == ' ';
    switch (dir) {
        case LEFT:
            if (maze[snakeY][snakeX - 1] == 'X') {
                dir = STOP;
                break;
            }
            snakeX--;
            break;
        case RIGHT:
            if (maze[snakeY][snakeX + 1] == 'X') {
                dir = STOP;
                break;
            }
            snakeX++;
            break;
        case UP:
            if (maze[snakeY - 1][snakeX] == 'X') {
                dir = STOP;
                break;
            }
            snakeY--;
            break;
        case DOWN:
            if (maze[snakeY + 1][snakeX] == 'X') {
                dir = STOP;
                break;
            }
            snakeY++;
            break;
        default:
            break;
    }

    // Gestion des collisions avec les murs
    if (maze[snakeY][snakeX] == 'X') {
        std::cout << "maze[" << snakeY << "][" << snakeX << "] == 'X'" << std::endl;
        dir = STOP;
    }

    // Met à jour la position du corps du serpent
    if (dir != STOP) {
        int prevX = tailX[0];
        int prevY = tailY[0];
        int prev2X, prev2Y;
        maze[tailY[0]][tailX[0]] = ' ';
        tailX[0] = saveSnakeX;
        tailY[0] = saveSnakeY;
        for (int i = 1; i < tailX.size(); i++) {
            prev2X = tailX[i];
            prev2Y = tailY[i];
            maze[tailY[i]][tailX[i]] = ' ';
            tailX[i] = prevX;
            tailY[i] = prevY;
            prevX = prev2X;
            prevY = prev2Y;
        }
    }

    // Gestion des collisions avec le corps du serpent
    for (int i = 0; i < tailX.size(); i++)
        if (tailX[i] == snakeX && tailY[i] == snakeY)
            gameOver = true;
}

void nibbler::display()
{
    maze[fruitY][fruitX] = 'F';
    for (int i = 0; i < tailX.size(); i++) {
        maze[tailY[i]][tailX[i]] = 'o';
    }
    maze[snakeY][snakeX] = 'O';
    // Dessine la grille
    for (int i = 0; i < maze.size(); i++)
        std::cout << maze[i] << std::endl;
    std::cout << "Score :" << score << std::endl;
}

void nibbler::conditionsKey(int key)
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

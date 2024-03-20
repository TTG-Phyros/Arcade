/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** IGame
*/

#include "IGame.hpp"

Game::IGame::IGame(std::string gameLibrary)
{
    _lib = dlopen(gameLibrary.c_str(), RTLD_LAZY);
    if (!_lib) {
        fprintf(stderr, "%s\n", dlerror());
        exit(84);
    }

    dlerror();
    *(void **)(&_gameLoop) = dlsym(_lib, "gameLoop");

    if ((_error = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", _error);
        exit(84);
    }

    *(void **)(&_inputHandler) = dlsym(_lib, "inputHandler");

    if ((_error = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", _error);
        exit(84);
    }

    *(void **)(&_display) = dlsym(_lib, "display");

    if ((_error = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", _error);
        exit(84);
    }
}

void Game::IGame::gameLoop()
{
    (*_gameLoop)();
}

void Game::IGame::inputHandler()
{
    (*_inputHandler)();
}

void Game::IGame::display()
{
    (*_display)();
}

Game::IGame::~IGame()
{
    dlclose(_lib);
}

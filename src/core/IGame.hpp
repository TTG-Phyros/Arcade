/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** IGame
*/

#ifndef IGAME_HPP_
#define IGAME_HPP_

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

namespace Game {
    class IGame {
        public:
            IGame(std::string gameLibrary);
            void gameLoop();
            void inputHandler();
            void display();
            ~IGame();

        protected:
        private:
            void *_lib;
            double (*_gameLoop)(void);
            double (*_inputHandler)(void);
            double (*_display)(void);
            char *_error;
    };
    class GameError : public std::exception {
        public:
            GameError(std::string error) : _error(error) {};
            const char *what() const noexcept { return _error.c_str(); };
        private:
            const std::string _error;
    };
};

#endif /* !IGAME_HPP_ */

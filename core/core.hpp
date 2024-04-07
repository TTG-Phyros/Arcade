/*
** EPITECH PROJECT, 2024
** TEST
** File description:
** core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include "IGame.hpp"
#include "IGraph.hpp"
#include "Parsing.hpp"
#include <fstream>
#include <iostream>
#include <string.h>

class Core {
    public:
        Core();
        void argumentsGestion(int ac, char **av, arcade::GameState *gameState);
        void printScore(std::map<std::string, std::map<std::string, int>> scores);
        void printMiniScore(std::map<std::string, int> scores);
        arcade::IGraph *initializeGraph(std::string graph);
        arcade::IGame *initializeGame(std::string game);
        void updateScoreFiles(arcade::GameState &gameState);
        void coreLoop(arcade::GameState *gameState);
        ~Core();
    protected:
    private:
};

class ArgumentEror : public std::exception {
    public:
        ArgumentEror(std::string error) : _error(error) {};
        const char *what() const noexcept { return _error.c_str(); };
    private:
        const std::string _error;
};

class DynamicLibError : public std::exception {
    public:
        DynamicLibError(std::string error) : _error(error) {};
        const char *what() const noexcept { return _error.c_str(); };
    private:
        const std::string _error;
};

class GraphInitError : public std::exception {
    public:
        GraphInitError(std::string error) : _error(error) {};
        const char *what() const noexcept { return _error.c_str(); };
    private:
        const std::string _error;
};

#endif /* !CORE_HPP_ */

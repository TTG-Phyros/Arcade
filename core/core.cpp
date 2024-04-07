/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** core
*/

#include "IGame.hpp"
#include "IGraph.hpp"
#include "Parsing.hpp"
#include <iostream>
#include <fstream>
#include <string.h>

void argumentsGestion(int ac, char **av, arcade::GameState *gameState)
{
    if (ac != 2) {
        std::cout << "Not enough arguments, try with -h" << std::endl;
        exit(84);
    }
    if (strcmp(av[1], "-h") == 0) {
        std::cout << "./arcade [graphLib]" << std::endl;
        std::cout << "    graphLib = Name of the graphical lib by default" << std::endl;
        exit(84);
    }
    std::vector<std::string> graphList = gameState->getGraphList();
    if (std::find(graphList.begin(), graphList.end(), av[1]) != graphList.end())
        gameState->setGraphLib(av[1]);
    else {
        std::cout << "Graphical Lib does not exist in lib or is not a graphical lib" << std::endl;
        exit(84);
    }
}

void printScore(std::map<std::string, std::map<std::string, int>> scores)
{
    std::map<std::string, std::map<std::string, int>>::iterator itScore = scores.begin();
    for (; itScore != scores.end(); ++itScore) {
        std::cout << "Game : " << itScore->first << std::endl;
        std::map<std::string, int>::iterator itScore2 = itScore->second.begin();
        for (; itScore2 != itScore->second.end(); ++itScore2) {
            std::cout << "    " << itScore2->first << " : " << itScore2->second << std::endl;
        }
    }
}

void printMiniScore(std::map<std::string, int> scores)
{
    std::cout << "Game : Niggler" << std::endl;
    std::map<std::string, int>::iterator itScore = scores.begin();
    for (; itScore != scores.end(); ++itScore) {
        std::cout << "    " << itScore->first << " : " << itScore->second << std::endl;
    }
}

arcade::IGraph *initializeGraph(std::string graph)
{
    void *graphLib = dlopen(graph.c_str(), RTLD_LAZY);
    if (!graphLib) {
        fprintf(stderr, "%s\n", dlerror());
        exit(84);
    }

    dlerror();
    arcade::IGraph *(*instance)();
    *(void **)(&instance) = dlsym(graphLib, "instance");

    if (!instance) {
        fprintf(stderr, "%s\n", dlerror());
        exit(84);
    }
    dlerror();
    return (*instance)();
}

arcade::IGame *initializeGame(std::string game)
{
    if (strcmp(game.c_str(), "") == 0)
        return nullptr;
    void *graphLib = dlopen(game.c_str(), RTLD_LAZY);
    if (!graphLib) {
        fprintf(stderr, "%s\n", dlerror());
        exit(84);
    }

    dlerror();
    arcade::IGame *(*instance)();
    *(void **)(&instance) = dlsym(graphLib, "instance");

    if (!instance) {
        fprintf(stderr, "%s\n", dlerror());
        exit(84);
    }
    dlerror();
    return (*instance)();
}

void updateScoreFiles(arcade::GameState &gameState)
{
    std::smatch matches;
    std::string temp = gameState.getGameLib();
    std::map<std::string, int> scores = gameState.getGameScores(temp);
    std::regex_search(temp, matches, std::regex(".*arcade_(\\w+).so"));
    std::map<std::string, int>::iterator it = scores.begin();
    if (matches.size() == 2) {
        temp = matches[1];
        std::ofstream scoreFile("./ressources/" + temp + ".scores");
        for (; it != scores.end(); ++it) {
            scoreFile << it->first << ":" << it->second << std::endl;;
        }
        scoreFile << gameState.getUsername() << ":" << gameState.getScore() << std::endl;
        scoreFile.close();
    }
    gameState.updateScores();
}

int main (int ac, char **av)
{
    arcade::GameState *gameState = new arcade::GameState();
    argumentsGestion(ac, av, gameState);
    std::string currentGraphLib = gameState->getGraphLib();
    std::string currentGameLib = gameState->getGameLib();
    arcade::IGraph *graphLib = initializeGraph(gameState->getGraphLib());
    arcade::IGame *gameLib = initializeGame(gameState->getGameLib());
    while (gameState->getState() != arcade::screenState::STOP) {
        if (strcmp(currentGraphLib.c_str(), gameState->getGraphLib().c_str()) != 0) {
            delete graphLib;
            graphLib = initializeGraph(gameState->getGraphLib());
            currentGraphLib = gameState->getGraphLib();
        }
        if (strcmp(currentGameLib.c_str(), gameState->getGameLib().c_str()) != 0) {
            delete gameLib;
            gameLib = initializeGame(gameState->getGameLib());
            currentGameLib = gameState->getGameLib();
        }
        graphLib->displayWindow(*gameState);
        if (gameState->getState() == arcade::screenState::IN_GAME && gameLib) {
            gameLib->updateGameState(*gameState);
        }
        if (gameState->getState() == arcade::screenState::GAME_END) {
            updateScoreFiles(*gameState);
            currentGameLib = "";
            currentGraphLib = "";
            gameState->setState(arcade::screenState::ARCADE_MENU);
            gameState->setKey(arcade::keyPressed::NOTHING);
        }
    }
}

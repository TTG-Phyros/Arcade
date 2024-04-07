/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** core
*/

#include "core.hpp"

Core::Core()
{
}

Core::~Core()
{
}

void Core::argumentsGestion(int ac, char **av, arcade::GameState *gameState)
{
    if (ac != 2)
        throw ArgumentEror("Not enough arguments, try with -h");
    if (strcmp(av[1], "-h") == 0)
        throw ArgumentEror("./arcade [graphLib]\n    graphLib = Name of the graphical lib by default");
    std::vector<std::string> graphList = gameState->getGraphList();
    if (std::find(graphList.begin(), graphList.end(), av[1]) != graphList.end())
        gameState->setGraphLib(av[1]);
    else
        throw ArgumentEror("Graphical Lib does not exist in lib or is not a graphical lib");
}

void Core::printScore(std::map<std::string, std::map<std::string, int>> scores)
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

void Core::printMiniScore(std::map<std::string, int> scores)
{
    std::cout << "Scores" << std::endl;
    std::map<std::string, int>::iterator itScore = scores.begin();
    for (; itScore != scores.end(); ++itScore) {
        std::cout << "    " << itScore->first << " : " << itScore->second << std::endl;
    }
}

arcade::IGraph *Core::initializeGraph(std::string graph)
{
    void *graphLib = dlopen(graph.c_str(), RTLD_LAZY);
    if (!graphLib)
        throw DynamicLibError(dlerror());

    dlerror();
    arcade::IGraph *(*instance)();
    *(void **)(&instance) = dlsym(graphLib, "instance");

    if (!instance)
        throw DynamicLibError(dlerror());
    dlerror();
    return (*instance)();
}

arcade::IGame *Core::initializeGame(std::string game)
{
    if (strcmp(game.c_str(), "") == 0)
        return nullptr;
    void *graphLib = dlopen(game.c_str(), RTLD_LAZY);
    if (!graphLib)
        throw DynamicLibError(dlerror());

    dlerror();
    arcade::IGame *(*instance)();
    *(void **)(&instance) = dlsym(graphLib, "instance");

    if (!instance)
        throw DynamicLibError(dlerror());

    dlerror();
    return (*instance)();
}

void Core::updateScoreFiles(arcade::GameState &gameState)
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

void Core::coreLoop(arcade::GameState *gameState)
{
    std::string currentGraphLib = gameState->getGraphLib();
    std::string currentGameLib = gameState->getGameLib();
    arcade::IGraph *graphLib = this->initializeGraph(gameState->getGraphLib());
    arcade::IGame *gameLib = this->initializeGame(gameState->getGameLib());
    while (gameState->getState() != arcade::screenState::STOP) {
        if (strcmp(currentGraphLib.c_str(), gameState->getGraphLib().c_str()) != 0) {
            delete graphLib;
            graphLib = this->initializeGraph(gameState->getGraphLib());
            currentGraphLib = gameState->getGraphLib();
        }
        if (strcmp(currentGameLib.c_str(), gameState->getGameLib().c_str()) != 0) {
            delete gameLib;
            gameLib = this->initializeGame(gameState->getGameLib());
            currentGameLib = gameState->getGameLib();
        }
        graphLib->displayWindow(*gameState);
        if (gameState->getState() == arcade::screenState::IN_GAME && gameLib) {
            gameLib->updateGameState(*gameState);
        }
        if (gameState->getState() == arcade::screenState::GAME_END) {
            this->updateScoreFiles(*gameState);
            currentGameLib = "";
            currentGraphLib = "";
            gameState->setState(arcade::screenState::ARCADE_MENU);
            gameState->setKey(arcade::keyPressed::NOTHING);
        }
    }
}

int main (int ac, char **av)
{
    Core *core = new Core();
    try {
        arcade::GameState *gameState = new arcade::GameState();
        core->argumentsGestion(ac, av, gameState);
        core->coreLoop(gameState);
    } catch (DynamicLibError &error) {
        std::cout << error.what() << std::endl;
        return 84;
    } catch (ArgumentEror &error) {
        std::cout << error.what() << std::endl;
        return 84;
    } catch (GraphInitError &error) {
        std::cout << error.what() << std::endl;
        return 84;
    }
    return 0;
}

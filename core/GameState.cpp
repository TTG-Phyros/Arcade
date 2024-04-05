/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** GameState
*/

#include "GameState.hpp"
#include "Parsing.hpp"

arcade::GameState::GameState()
{
    this->_scores = arcade::Parsing::parseScoresFromFile(SCORES_FILE);
    this->_libsList = arcade::Parsing::getLibsFromPath(LIB_PATH);
    this->_graphList = arcade::Parsing::getGraphFromLibs(this->_libsList);
    this->_gamesList = arcade::Parsing::getGamesFromLibs(this->_libsList, this->_graphList);
}

arcade::GameState::~GameState()
{

}

std::map<std::string, std::map<std::string, int>> arcade::GameState::getScores()
{
    return this->_scores;
}

std::vector<std::string> arcade::GameState::getLibsList()
{
    return this->_libsList;
}

std::vector<std::string> arcade::GameState::getGraphList()
{
    return this->_graphList;
}

std::vector<std::string> arcade::GameState::getGamesList()
{
    return this->_gamesList;
}

std::string arcade::GameState::getUsername()
{
    return this->_username;
}

void arcade::GameState::displayLibs(std::vector<std::string> libs)
{
    size_t i = 0, size = libs.size();

    while (i < size) {
        std::cout << libs[i] << std::endl;
        i++;
    }
}

arcade::screenState arcade::GameState::getState()
{
    return this->_state;
}

void arcade::GameState::setState(arcade::screenState state)
{
    this->_state = state;
}

void arcade::GameState::setUsername(std::string username)
{
    this->_username = username;
}

std::string arcade::GameState::getGameLib()
{
    return this->_gameLib;
}

std::string arcade::GameState::getGraphLib()
{
    return this->_graphLib;
}

void arcade::GameState::setGameLib(std::string libName)
{
    this->_gameLib = libName;
}

void arcade::GameState::setGraphLib(std::string libName)
{
    this->_graphLib = libName;
}

void arcade::GameState::setGameArray(std::vector<std::string> gameArray)
{
    int i = 0, len = gameArray.size();

    this->_gameArray.clear();
    this->_gameArray.resize(len);

    while (i < len) {
        this->_gameArray[i] = gameArray[i];
        i++;
    }
}

std::vector<std::string> arcade::GameState::getGameArray()
{
    return this->_gameArray;
}
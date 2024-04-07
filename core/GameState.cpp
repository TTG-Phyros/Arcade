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

int arcade::GameState::getScore()
{
    return this->_score;
}

void arcade::GameState::setScore(int score)
{
    this->_score = score;
}

arcade::keyPressed arcade::GameState::getKey()
{
    return this->_key;
}

void arcade::GameState::setKey(arcade::keyPressed key)
{
    this->_key = key;
}

std::map<std::string, int> arcade::GameState::getGameScores(std::string gameName)
{
    std::smatch matches;
    std::regex_search(gameName, matches, std::regex(".*arcade_(\\w+).so"));
    if (matches.size() == 2)
        if (_scores.find(std::string(matches[1])) != _scores.end())
            return _scores[std::string(matches[1])];
    return {};
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
    this->_gameArray = gameArray;
}

std::vector<std::string> arcade::GameState::getGameArray()
{
    return this->_gameArray;
}

void arcade::GameState::updateScores()
{
    this->_scores = arcade::Parsing::parseScoresFromFile(SCORES_FILE);
}
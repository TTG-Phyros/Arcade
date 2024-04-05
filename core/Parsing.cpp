/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Parsing
*/

#include "GameState.hpp"
#include "Parsing.hpp"
#include "IGame.hpp"
#include "IGraphical.hpp"

arcade::Parsing::Parsing()
{
}

std::map<std::string, int> arcade::Parsing::parseOneScoreFile(std::string scoreFilePath)
{
    std::ifstream file(scoreFilePath);
    std::string line;
    std::map<std::string, int> scores;
    if (file.is_open()) {
        while (std::getline(file, line)) {
            std::smatch matches;
            std::regex_search(line, matches, std::regex("(\\w+):([0-9]+)"));
            if (matches.size() == 3)
                scores.insert({matches[1], stoi(matches[2])});
        }
    }
    return scores;
}

std::map<std::string, std::map<std::string, int>> arcade::Parsing::parseScoresFromFile(std::string scoresPath)
{
    std::map<std::string, std::map<std::string, int>> scores;
    for (const auto &entry : std::filesystem::directory_iterator(scoresPath)) {
        std::string temp = entry.path();
        std::smatch matches;
        std::regex_search(temp, matches, std::regex(".*/(\\w+).scores"));
        if (matches.size() == 2)
            scores.insert({matches[1], parseOneScoreFile(matches[0])});
    }
    return scores;
}

std::vector<std::string> arcade::Parsing::getLibsFromPath(std::string libsPath)
{
    std::vector<std::string> libs;
    for (const auto &entry : std::filesystem::directory_iterator(libsPath)) {
        std::string temp = entry.path();
        if (std::regex_match(temp, std::regex(".*arcade_(\\w+).so")))
            libs.push_back(temp);
    }
    return libs;
}

std::vector<std::string> arcade::Parsing::getGamesFromLibs(std::vector<std::string> allLibs, std::vector<std::string> graphLibs)
{
    std::vector<std::string> gameLibs = {"TEST", "pasla"};
    int size = allLibs.size();
    for (int i = 0; i < size; i++)
        if (std::find(graphLibs.begin(), graphLibs.end(), allLibs[i]) == graphLibs.end())
            gameLibs.push_back(allLibs[i]);
    return gameLibs;
}

std::vector<std::string> arcade::Parsing::getGraphFromLibs(std::vector<std::string> allLibs)
{
    std::vector<std::string> graphLibs = {"TEST", "pasla"};
    IGraph *(*_getLibType)(void);
    void *_lib;
    for (const auto &lib : allLibs) {
        _lib = dlopen(lib.c_str(), RTLD_LAZY);
        if (!_lib) {
            fprintf(stderr, "%s\n", dlerror());
            exit(84);
        }

        dlerror();
        *(void **)(&_getLibType) = dlsym(_lib, "instance");

        if (!_getLibType) {
            fprintf(stderr, "%s\n", dlerror());
            exit(84);
        }

        if ((*_getLibType)()->getLibType() == arcade::libType::GRAPHICALS)
            graphLibs.push_back(lib);
    }
    return graphLibs;
}

arcade::Parsing::~Parsing()
{

}
